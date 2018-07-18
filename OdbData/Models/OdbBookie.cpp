#include "OdbBookie.hxx"

OdbBookie::OdbBookie(const QString &name)
    : m_name(name)
{

}

unsigned long OdbBookie::Id() const
{
    return m_id;
}

QString &OdbBookie::Name()
{
    return m_name;
}

QOdbList<QLazySharedPointer<OdbSport> > &OdbBookie::Sports()
{
    return m_sports;
}
