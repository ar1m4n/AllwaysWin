#include "PinnacleCommunicator.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>

const uint64_t PinnacleCommunicator::BOOKIE_ID = 2;
const QString PinnacleCommunicator::BOOKIE_NAME = "Pinnacle";

PinnacleCommunicator::PinnacleCommunicator()
    : Communicator("https", "api.pinnacle.com", BOOKIE_ID, BOOKIE_NAME)
{
}

void PinnacleCommunicator::OnLoginButtonClicked(const QString &userName, const QString &password)
{
    QString result = QString(userName).append(":").append(password).toUtf8().toBase64();
    m_baseAuthenticate = QString("Basic %1").arg(result);
    emit LoginComplete(true);
}

void PinnacleCommunicator::OnCollectDataButtonClicked()
{
    m_apiUrl.setPath("/v1/sports");
    QNetworkRequest request(m_apiUrl);
    request.setRawHeader("Authorization", m_baseAuthenticate.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    m_restClient->get(request);
    m_onRequestOk = [this](QNetworkReply *reply) {
        QString a = reply->readAll();
        qDebug() << a << endl;
        emit DataReady(QJsonDocument::fromJson(a.toUtf8()));

        reply->deleteLater();
    };
}

void PinnacleCommunicator::OnRequestComplete(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        connect(reply, &QNetworkReply::readyRead, this, &PinnacleCommunicator::OnReadyRead);
    }
    else
    {
        qDebug() << reply->errorString();
    }
}

void PinnacleCommunicator::OnReadyRead()
{
    if(m_onRequestOk)
        m_onRequestOk(qobject_cast<QNetworkReply*>(sender()));
}
