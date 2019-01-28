#pragma once

#include "Communicator.h"
#include <functional>
#include <QJsonArray>

class PinnacleCommunicator : public Communicator
{
    Q_OBJECT
    std::function<void(QNetworkReply*)> m_onRequestOk = nullptr;
    QString m_baseAuthenticate;
    QJsonArray m_eventsResponse;

public:
    static const uint64_t BOOKIE_ID;
    static const QString BOOKIE_NAME;
    explicit PinnacleCommunicator();

public slots:
    void OnLoginButtonClicked(const QString &userName, const QString &password) override;
    void OnCollectDataButtonClicked() override;
    void OnRequestComplete(QNetworkReply *reply) override;
    void OnReadyRead();
};
