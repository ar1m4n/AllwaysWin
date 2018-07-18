#include "OdbRunner.hxx"

OdbRunner::OdbRunner(const QString &idInBookie, const QString &name)
    :m_idInBookie(idInBookie), m_name(name)
{

}

unsigned long OdbRunner::Id() const
{
    return m_id;
}

const QString &OdbRunner::IdInBookie() const
{
    return m_idInBookie;
}

QString &OdbRunner::Name()
{
    return m_name;
}

QLazyWeakPointer<OdbMarketEvents> &OdbRunner::MarketEvent()
{
    return m_marketEvent;
}

QOdbList<QLazySharedPointer<OdbPrice>> &OdbRunner::Prices()
{
    return m_prices;
}
