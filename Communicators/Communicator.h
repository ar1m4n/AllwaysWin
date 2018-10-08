#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QSharedPointer>
#include <QJsonDocument>
#include <QUrl>
#include <map>

class QNetworkAccessManager;
class QNetworkReply;
class OdbBookie;
class OdbPrice;
class OdbEventParticipant;

class Communicator : public QObject
{
    Q_OBJECT
public:
    explicit Communicator(const QString &protocol, const QString & url,
                          uint64_t bookieId, const QString & bookieName);

protected:
    QUrl m_apiUrl;
    QNetworkAccessManager *m_restClient = nullptr;
    uint64_t m_bookieId = 0;
    QString m_bookieName;
    QSharedPointer<OdbBookie> m_bookie;
    QList<QSharedPointer<OdbPrice>> m_prices;
    using ParticipantsCollectionValue = std::map<QString, QSharedPointer<OdbEventParticipant>>;
    using ParticipantsCollection = std::map<QString, ParticipantsCollectionValue>;
    ParticipantsCollection m_participants;

Q_SIGNALS:
    void DataReady(QJsonDocument);
    void LoginComplete(bool);

public slots:
    virtual void OnLoginButtonClicked(const QString &userName, const QString &password) = 0;
    virtual void OnCollectDataButtonClicked() = 0;
    virtual void OnRequestComplete(QNetworkReply*) = 0;

    QString ApiPath() const;
};

#endif // COMMUNICATOR_H
