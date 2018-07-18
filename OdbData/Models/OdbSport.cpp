#include "OdbSport.hxx"

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

QLazyWeakPointer<OdbBookie> &OdbSport::Booky()
{
    return m_booky;
}

QOdbList<QLazySharedPointer<OdbEvent> > &OdbSport::Events()
{
    return m_events;
}
