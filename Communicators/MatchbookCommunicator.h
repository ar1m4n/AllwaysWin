#ifndef MATCHBOOKCOMMUNICATOR_H
#define MATCHBOOKCOMMUNICATOR_H

#include "Communicator.h"
#include <QJsonArray>
#include <functional>
#include <QMap>
#include <map>

class QNetworkReply;
class OdbSport;
class OdbEvent;
class OdbRunner;
class OdbMarket;
class OdbEventParticipant;

class MatchbookCommunicator : public Communicator
{
    Q_OBJECT
public:
    static const uint64_t BOOKIE_ID;
    static const QString BOOKIE_NAME;
    explicit MatchbookCommunicator();

Q_SIGNALS:

public slots:
    void OnLoginButtonClicked(const QString &userName, const QString &password) override;
    void OnCollectDataButtonClicked() override;
    void OnRequestComplete(QNetworkReply *reply) override;

private:
    QString m_sessionToken, m_userName, m_password;
    std::function<void(QNetworkReply*)> m_onRequestOk = nullptr;
    int m_currentOffset = 0, m_perPage = 20;
    QJsonArray m_eventsResponse;
    void ParseBookie();
    void ParseEvents(QSharedPointer<OdbBookie> &bookie, const QJsonArray &eventsArray);
    void ParseMarkets(QSharedPointer<OdbEvent> &event, const QJsonObject &eventObj);
    void ParseRunners(QSharedPointer<OdbMarket> &market, const QJsonObject &marketObj,
                      std::map<QString, QSharedPointer<OdbEventParticipant> > &eventParticipents);
    void ParsePrices(QSharedPointer<OdbRunner> &runner, const QJsonObject &runnerObj);
};

#endif // MATCHBOOKCOMMUNICATOR_H
