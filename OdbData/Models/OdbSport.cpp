#include "OdbSport.hxx"
#include "OdbBookie.hxx"

OdbSport::OdbSport(const QString &idInBookie, const QString &name)
    : m_idInBookie(idInBookie), m_name(name)
{

}

unsigned long OdbSport::Id() const
{
    return m_id;
}

const QString &OdbSport::IdInBookie() const
{
    return m_idInBookie;
}

const QString &OdbSport::Name() const
{
    return m_name;
}

const QLazySharedPointer<OdbBookie> &OdbSport::Booky() const
{
    return m_booky;
}

const QOdbList<QLazyWeakPointer<OdbMarket> > &OdbSport::Markets() const
{
    return m_markets;
}
