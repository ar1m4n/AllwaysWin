#include "OdbMarket.txx"

OdbMarket::OdbMarket(const QString &idInBookie, const QString &name)
    :OdbBookieEntity(idInBookie), m_name(name)
{

}

unsigned long OdbMarket::Id() const
{
    return m_id;
}

QString &OdbMarket::Name()
{
    return m_name;
}

QLazySharedPointer<OdbEvent> &OdbMarket::Event()
{
    return m_event;
}

std::set<QLazyWeakPointer<OdbRunner> > &OdbMarket::Runners()
{
    return m_runners;
}
