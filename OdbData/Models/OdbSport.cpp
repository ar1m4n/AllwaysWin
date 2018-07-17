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

QString &OdbSport::Name()
{
    return m_name;
}

QLazySharedPointer<OdbBookie> &OdbSport::Booky()
{
    return m_booky;
}

QOdbList<QLazyWeakPointer<OdbMarket> > &OdbSport::Markets()
{
    return m_markets;
}
