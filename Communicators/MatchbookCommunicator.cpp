#include "MatchbookCommunicator.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
#include <QTimer>
#include <QDebug>
#include <QSharedPointer>
#include "OdbData/OdbContext.h"
#include "OdbData/Models/OdbBookie-odb.hxx"
#include "OdbData/Models/OdbSport-odb.hxx"
#include "OdbData/Models/OdbEvent-odb.hxx"
#include "OdbData/Models/OdbEventParticipant-odb.hxx"
#include "OdbData/Models/OdbMarket-odb.hxx"
#include "OdbData/Models/OdbRunner-odb.hxx"
#include "OdbData/Models/OdbPrice-odb.hxx"

const uint64_t MatchbookCommunicator::BOOKIE_ID = 1;
const QString MatchbookCommunicator::BOOKIE_NAME = "Matchbook";

MatchbookCommunicator::MatchbookCommunicator()
    : Communicator("https", "api.matchbook.com", BOOKIE_ID, BOOKIE_NAME)
{
}

void MatchbookCommunicator::OnLoginButtonClicked(const QString &userName, const QString &password)
{
    m_userName = userName;
    m_password = password;
    m_apiUrl.setPath("/bpapi/rest/security/session");
    QVariantMap feed;
    feed.insert("username", m_userName);
    feed.insert("password", m_password);
    QByteArray payload = QJsonDocument::fromVariant(feed).toJson();
    QNetworkRequest request(m_apiUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    m_restClient->post(request, payload);
    m_onRequestOk = [this](QNetworkReply *reply) {
        m_sessionToken.clear();
        QString data = reply->readAll();
        data.replace("0E-8", "0.00");
        QJsonObject object = QJsonDocument::fromJson(data.toLatin1()).object();
        auto sessionTokenFound = object.find("session-token");
        if (sessionTokenFound != object.end())
        {
            m_sessionToken = sessionTokenFound.value().toString();
        }
        emit LoginComplete(!m_sessionToken.isEmpty());
    };
}

void MatchbookCommunicator::OnCollectDataButtonClicked()
{
    m_apiUrl.setPath("/edge/rest/events");
    QUrlQuery query;
    query.addQueryItem("offset", QString::number(m_currentOffset));
    query.addQueryItem("states", "open");
//    query.addQueryItem("sport-ids", "15");
    m_apiUrl.setQuery(query);
    QNetworkRequest request(m_apiUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("session-token", m_sessionToken.toLatin1());
    m_restClient->get(request);
    m_onRequestOk = [this](QNetworkReply *reply) {
        QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
        auto eventsFound = json.find("events");
        if(eventsFound != json.end())
        {
            auto eventsArray = eventsFound.value().toArray();
            for(auto event : eventsArray)
            {
                m_eventsResponse.push_back(event);
            }
        }

        auto offsetFound = json.find("offset");
        if (offsetFound != json.end())
        {
            auto totalFound = json.find("total");
            if (totalFound != json.end())
            {
                m_currentOffset = offsetFound.value().toInt() + m_perPage;
                int total = totalFound.value().toInt();
                if (m_currentOffset < total)
                {
                    OnCollectDataButtonClicked();
                }
                else
                {
                    emit DataReady(QJsonDocument(QJsonObject({{"events", m_eventsResponse}})));
//                    ParseBookie();
                    m_eventsResponse = QJsonArray();
                    m_currentOffset = 0;
                }
            }
        }
    };
}

void MatchbookCommunicator::OnRequestComplete(QNetworkReply * reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        if(m_onRequestOk)
            m_onRequestOk(reply);
    }
    else
    {
        qDebug() << reply->errorString();
        if(reply->error() == QNetworkReply::InternalServerError)
        {
            OnLoginButtonClicked(m_userName, m_password);
        }
    }

    reply->deleteLater();
}

void MatchbookCommunicator::ParseBookie()
{
    m_bookie.reset(new OdbBookie(m_bookieId, m_bookieName));
    m_prices.clear();
    m_participants.clear();
    ParseEvents(m_bookie, m_eventsResponse);
}

void MatchbookCommunicator::ParseEvents(QSharedPointer<OdbBookie> &bookie,
                                        const QJsonArray &eventsArray)
{
    std::map<QString, QSharedPointer<OdbSport>> sports;
    for(auto event : eventsArray)
    {
        auto eventObj = event.toObject();
        auto metaTags = eventObj.find("meta-tags").value().toArray();
        QPair<QJsonObject, QJsonObject> sportTags;
        for(auto v : metaTags) {
            auto current = v.toObject();
            auto type = current.find("type").value().toString();

            if(type == "SPORT")
                sportTags.first = current;
            else if(type == "COUNTRY")
                sportTags.second = current;

            if(!sportTags.first.empty() && !sportTags.second.empty())
                break;
        }

        if(!sportTags.first.empty())
        {
            auto sportName = sportTags.first.find("name").value().toString();
            auto sportIdInBookie = sportTags.first.find("id").value().toVariant().toString();
            auto eventPlace = sportTags.second.find("name").value().toString();
            auto sportIt = sports.emplace(sportName, nullptr);
            if(sportIt.second)
            {
                sportIt.first->second = QSharedPointer<OdbSport>::create(sportIdInBookie, sportName);
                sportIt.first->second->Booky() = bookie;
                bookie->Sports().emplace(sportIt.first->second);
            }

            auto eventPtr = QSharedPointer<OdbEvent>::create(
                eventObj.find("id").value().toVariant().toString(),
                eventObj.find("name").value().toString(),
                QDateTime::fromString(eventObj.find("start").value().toString(), Qt::ISODateWithMs),
                eventPlace
            );

            eventPtr->Sport() = sportIt.first->second;
            eventPtr->Sport()->Events().emplace(eventPtr);

            ParseMarkets(eventPtr, eventObj);
        }
    }
}

void MatchbookCommunicator::ParseMarkets(QSharedPointer<OdbEvent> &event, const QJsonObject &eventObj)
{
    auto found = m_participants.emplace(event->IdInBookie(), Communicator::ParticipantsCollectionValue());
    auto markets = eventObj.find("markets").value().toArray();
    for(auto market: markets)
    {
        auto marketObj = market.toObject();
        auto marketPtr = QSharedPointer<OdbMarket>::create(
            marketObj.find("id").value().toVariant().toString(),
            marketObj.find("name").value().toString()
        );

        marketPtr->Event() = event;
        event->Markets().emplace(marketPtr);

        ParseRunners(marketPtr, marketObj, found.first->second);
    }

    for(auto &evP : found.first->second)
    {
        evP.second->Event() = event;
        event->Participants().emplace(evP.second);
    }
}

void MatchbookCommunicator::ParseRunners(QSharedPointer<OdbMarket> &market, const QJsonObject &marketObj,
                                         std::map<QString, QSharedPointer<OdbEventParticipant>> &eventParticipents)
{
    auto runners = marketObj.find("runners").value().toArray();
    for(auto runner: runners)
    {
        auto runnerObj = runner.toObject();
        auto eventParticipentId = runnerObj.find("event-participant-id").value().toVariant().toString();
        auto runnerPtr = QSharedPointer<OdbRunner>::create(
            runnerObj.find("id").value().toVariant().toString(),
            runnerObj.find("name").value().toString()
        );

        runnerPtr->Market() = market;
        market->Runners().emplace(runnerPtr);

        if(!eventParticipentId.isEmpty() && eventParticipentId != "0")
        {
            auto eventParticipentFound = eventParticipents.emplace(eventParticipentId, nullptr);
            if(eventParticipentFound.second)
                eventParticipentFound.first->second = QSharedPointer<OdbEventParticipant>::create(eventParticipentId, runnerPtr->Name());
        }

        ParsePrices(runnerPtr, runnerObj);
    }
}

void MatchbookCommunicator::ParsePrices(QSharedPointer<OdbRunner> &runner, const QJsonObject &runnerObj)
{
    auto prices = runnerObj.find("prices").value().toArray();
    for(auto price : prices)
    {
        auto priceObj = price.toObject();
        auto pricePtr = QSharedPointer<OdbPrice>::create(
            priceObj.find("decimal-odds").value().toDouble(),
            priceObj.find("available-amount").value().toDouble(),
            priceObj.find("side").value().toString().toLower() == "back" ? OdbPriceType::Back : OdbPriceType::Lay
        );
        m_prices.append(pricePtr);

        pricePtr->Runner() = runner;
        runner->Prices().append(pricePtr);
    }
}
