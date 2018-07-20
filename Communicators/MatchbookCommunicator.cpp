#include "MatchbookCommunicator.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QUrlQuery>
#include <QTimer>
#include <QDebug>

MatchbookCommunicator::MatchbookCommunicator(QObject *parent)
    : Communicator("https", "api.matchbook.com", parent)
{
    connect(this, &MatchbookCommunicator::DataReady, [this](){
        QTimer::singleShot(10 * 1000, this, &MatchbookCommunicator::SheduleGetData);
    });
}

void MatchbookCommunicator::OnLoginButtonClicked(const QString &userName, const QString &password)
{
    m_userName = userName;
    m_password = password;
    SheduleLogin();
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
    }

    reply->deleteLater();
}

void MatchbookCommunicator::SheduleLogin()
{
    m_apiUrl.setPath("/bpapi/rest/security/session");
    QVariantMap feed;
    feed.insert("username", m_userName);
    feed.insert("password", m_password);
    QByteArray payload = QJsonDocument::fromVariant(feed).toJson();
    QNetworkRequest request(m_apiUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    m_restClient->post(request, payload);
    m_onRequestOk = [this](QNetworkReply *reply) {
        QString data = reply->readAll();
        data.replace("0E-8", "0.00");
        QJsonObject object = QJsonDocument::fromJson(data.toLatin1()).object();
        auto sessionTokenFound = object.find("session-token");
        if (sessionTokenFound != object.end())
        {
            m_sessionToken = sessionTokenFound.value().toString();
            SheduleGetData();
        }
    };
}

void MatchbookCommunicator::SheduleGetData()
{
    m_apiUrl.setPath("/edge/rest/events");
    QUrlQuery query;
    query.addQueryItem("offset", QString::number(m_currentOffset));
    query.addQueryItem("states", "open");
    query.addQueryItem("sport-ids", "15");
    m_apiUrl.setQuery(query);
    QNetworkRequest request(m_apiUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("session-token", m_sessionToken.toLatin1());
    m_restClient->get(request);
    m_onRequestOk = [this](QNetworkReply *reply) {
        QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
        m_eventsResponse.insert(QString::number(m_currentOffset), json);
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
                    SheduleGetData();
                }
                else
                {
                    QJsonObject maxObj;
                    std::map<QString, std::map<QString, QJsonObject>> runnersByMarket;
                    for (auto it : m_eventsResponse)
                    {
                        auto eventsFound = it.toObject().value("events");
                        if (eventsFound.isArray())
                        {
                            auto eventsArray = eventsFound.toArray();
                            for (auto event : eventsArray)
                            {
                                auto eventName = event.toObject().value("name").toString();
                                auto foundMarkets = event.toObject().value("markets");
                                if (foundMarkets.isArray())
                                {
                                    auto marketsArray = foundMarkets.toArray();
                                    for(auto market : marketsArray)
                                    {
                                        auto marketObj = market.toObject();
                                        auto marketType = marketObj.value("name").toString();
                                        auto marketRunners = runnersByMarket.emplace(marketType, std::map<QString, QJsonObject>());
                                        auto allRunners = marketRunners.first->second.emplace(eventName, QJsonObject());
                                        auto newRunners = marketObj.value("runners").toArray();
                                        for(auto runner : newRunners)
                                        {
                                            auto runnerObj = runner.toObject();
                                            if(!runnerObj.value("prices").toArray().empty())
                                            {
                                                allRunners.first->second.insert(runnerObj.value("name").toString(), runnerObj);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    for(auto val : runnersByMarket)
                    {
                        QJsonObject eventData;
                        for(auto evVal : val.second)
                        {
                            eventData.insert(evVal.first, evVal.second);
                        }

                        maxObj.insert(val.first, eventData);
                    }

                    emit DataReady(maxObj);
                    m_eventsResponse = QJsonObject();
                    m_currentOffset = 0;
                }
            }
        }
    };
}
