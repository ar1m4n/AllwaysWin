#ifndef MATCHBOOKCOMMUNICATOR_H
#define MATCHBOOKCOMMUNICATOR_H

#include "Communicator.h"
#include <QJsonObject>
#include <functional>
#include <QMap>

class QNetworkReply;

class MatchbookCommunicator : public Communicator
{
    Q_OBJECT
public:
    explicit MatchbookCommunicator();

Q_SIGNALS:

public slots:
    void OnLoginButtonClicked(const QString &userName, const QString &password) override;
    void OnRequestComplete(QNetworkReply *reply) override;

private:
    QString m_sessionToken, m_userName, m_password;
    std::function<void(QNetworkReply*)> m_onRequestOk = nullptr;
    int m_currentOffset = 0, m_perPage = 20;
    QJsonObject m_eventsResponse;

    void SheduleLogin();
    void SheduleGetData();
};

#endif // MATCHBOOKCOMMUNICATOR_H
