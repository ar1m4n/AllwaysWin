#include "OdbSport.txx"

OdbSport::OdbSport(const QString &idInBookie, const QString &name)
    : OdbBookieEntity(idInBookie), m_name(name)
{

}

unsigned long OdbSport::Id() const
{
    return m_id;
}

QString &OdbSport::Name()
{
    return m_name;
}

QLazySharedPointer<OdbBookie> &OdbSport::Booky()
{
    return m_booky;
}

std::set<QLazyWeakPointer<OdbEvent> > &OdbSport::Events()
{
    return m_events;
}
