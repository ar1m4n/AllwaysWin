#include "Communicator.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "OdbData/Models/OdbBookie-odb.hxx"

Communicator::Communicator(const QString &protocol, const QString &url,
                           uint64_t bookieId, const QString &bookieName)
    : QObject(nullptr), m_bookieId(bookieId), m_bookieName(bookieName)
{
    m_apiUrl.setScheme(protocol);
    m_apiUrl.setHost(url);
    m_restClient = new QNetworkAccessManager(this);

    connect(m_restClient, &QNetworkAccessManager::finished,
            this, &Communicator::OnRequestComplete);
}

QString Communicator::ApiPath() const
{
    return m_apiUrl.host();
}
