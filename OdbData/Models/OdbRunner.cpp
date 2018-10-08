#include "OdbRunner.txx"

OdbRunner::OdbRunner(const QString &idInBookie, const QString &name)
    :OdbBookieEntity(idInBookie), m_name(name)
{

}

unsigned long OdbRunner::Id() const
{
    return m_id;
}

QString &OdbRunner::Name()
{
    return m_name;
}

QLazySharedPointer<OdbMarket> &OdbRunner::Market()
{
    return m_market;
}

QOdbList<QLazyWeakPointer<OdbPrice> > &OdbRunner::Prices()
{
    return m_prices;
}
