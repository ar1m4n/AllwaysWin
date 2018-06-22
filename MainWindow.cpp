#include "MainWindow.h"
#include "jsonmodel.h"
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
        auto responseData = jsonModel->parse(reply->readAll());
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
                                        auto allRunners = maxObj.value(marketType).toObject();
                                        auto newRunners = marketObj.value("runners").toArray();
                                        for(auto runner : newRunners)
                                        {
                                            allRunners.insert(eventName, runner);
                                        }
                                        maxObj.insert(marketType, allRunners);
                                    }
                                }
                            }
                        }
                    }
                    jsonModel->parse(QJsonDocument(maxObj));
                    eventsResponse = QJsonObject();
                    ui->treeView->expandAll();
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
