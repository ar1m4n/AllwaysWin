#include "Communicator.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>

Communicator::Communicator(const QString &protocol, const QString &url)
    : QObject(nullptr)
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
