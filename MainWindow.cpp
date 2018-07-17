#include "MainWindow.h"
#include "JsonModel.h"
#include "ui_MainWindow.h"
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    jsonModel = new JsonModel(this);
    ui->treeView->setModel(jsonModel);
    apiUrl.setScheme("https");
    apiUrl.setHost("api.matchbook.com");
    restClient = new QNetworkAccessManager(this);
    connect(restClient, SIGNAL(finished(QNetworkReply*)), this,
            SLOT(on_request_complete(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginBtn_clicked()
{
    apiUrl.setPath("/bpapi/rest/security/session");
    QVariantMap feed;
    feed.insert("username", ui->usrEdit->text());
    feed.insert("password", ui->pwdEdit->text());
    QByteArray payload = QJsonDocument::fromVariant(feed).toJson();
    QNetworkRequest request(apiUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto reply = restClient->post(request, payload);
    onRequestOk[reply] = [this, reply]() {
        QString data = reply->readAll();
        data.replace("0E-8", "0.00");
        auto responseData = jsonModel->parse(data.toLatin1());
        ui->treeView->expandAll();
        auto sessionTokenFound = responseData.find("session-token");
        if (sessionTokenFound != responseData.end())
        {
            sessionToken = sessionTokenFound.value().toString();
            ui->eventBtn->setEnabled(true);
            ui->sportsBtn->setEnabled(true);
        }
    };
}

void MainWindow::on_request_complete(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        auto onRequestOkFound = onRequestOk.find(reply);
        if (onRequestOkFound != onRequestOk.end())
        {
            onRequestOkFound.value()();
            onRequestOk.erase(onRequestOkFound);
        }
    }

    reply->deleteLater();
}

void MainWindow::on_eventBtn_clicked()
{
    apiUrl.setPath("/edge/rest/events");
    QUrlQuery query;
    query.addQueryItem("offset", QString::number(currentOffset));
    query.addQueryItem("states", "open");
    query.addQueryItem("sport-ids", "15");
    apiUrl.setQuery(query);
    QNetworkRequest request(apiUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("session-token", sessionToken.toLatin1());
    auto reply = restClient->get(request);
    onRequestOk[reply] = [this, reply]() {
        QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
        eventsResponse.insert(QString::number(currentOffset), json);
        auto offsetFound = json.find("offset");
        if (offsetFound != json.end())
        {
            auto totalFound = json.find("total");
            if (totalFound != json.end())
            {
                currentOffset = offsetFound.value().toInt() + perPage;
                int total = totalFound.value().toInt();
                if (currentOffset < total)
                {
                    on_eventBtn_clicked();
                }
                else
                {
                    QJsonObject maxObj;
                    std::map<QString, std::map<QString, QJsonObject>> runnersByMarket;
                    for (auto it : eventsResponse)
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

                    jsonModel->parse(QJsonDocument(maxObj));
                    eventsResponse = QJsonObject();
//                    ui->treeView->expand(ui->treeView->model()->index(0, 0));
                    currentOffset = 0;
                }
            }
        }
    };
}

void MainWindow::on_sportsBtn_clicked()
{
    apiUrl.setPath("/edge/rest/lookups/sports");
    QUrlQuery query;
    query.addQueryItem("offset", QString::number(currentOffset));
    query.addQueryItem("states", "open");
    apiUrl.setQuery(query);
    QNetworkRequest request(apiUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("session-token", sessionToken.toLatin1());
    auto reply = restClient->get(request);
    onRequestOk[reply] = [this, reply]() {
        QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
        eventsResponse.insert(QString::number(currentOffset), json);
        auto offsetFound = json.find("offset");
        if (offsetFound != json.end())
        {
            auto totalFound = json.find("total");
            if (totalFound != json.end())
            {
                currentOffset = offsetFound.value().toInt() + perPage;
                int total = totalFound.value().toInt();
                if (currentOffset < total)
                {
                    on_sportsBtn_clicked();
                }
                else
                {
                    jsonModel->parse(QJsonDocument(eventsResponse));
                    ui->treeView->expandAll();
                    eventsResponse = QJsonObject();
                    currentOffset = 0;
                }
            }
        }
    };
}
