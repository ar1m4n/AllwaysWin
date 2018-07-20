#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QJsonObject>
#include <QUrl>

class QNetworkAccessManager;
class QNetworkReply;
class BookieWidget;

class Communicator : public QObject
{
    Q_OBJECT
public:
    explicit Communicator(const QString &protocol, const QString & url, QObject *parent);

protected:
    QUrl m_apiUrl;
    QNetworkAccessManager *m_restClient = nullptr;

Q_SIGNALS:
    void DataReady(QJsonObject);

public slots:
    virtual void OnLoginButtonClicked(const QString &userName, const QString &password) = 0;
    virtual void OnRequestComplete(QNetworkReply*) = 0;
};

#endif // COMMUNICATOR_H
