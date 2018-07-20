#include "Communicator.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "Widgets/BookieWidget.h"

Communicator::Communicator(const QString &protocol, const QString &url, QObject *parent)
    : QObject(parent)
{
    m_apiUrl.setScheme(protocol);
    m_apiUrl.setHost(url);
    m_restClient = new QNetworkAccessManager(this);

    connect(m_restClient, &QNetworkAccessManager::finished,
            this, &Communicator::OnRequestComplete);
}
