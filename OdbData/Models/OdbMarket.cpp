#include "OdbMarket.hxx"

OdbMarket::OdbMarket(const QString &idInBookie, const QString &name)
    :m_idInBookie(idInBookie), m_name(name)
{

}

unsigned long OdbMarket::Id() const
{
    return m_id;
}

const QString &OdbMarket::IdInBookie() const
{
    return m_idInBookie;
}

QString &OdbMarket::Name()
{
    return m_name;
}

QOdbList<QLazyWeakPointer<OdbMarketEvents> > &OdbMarket::MarketEvents()
{
    return m_marketEvents;
}
