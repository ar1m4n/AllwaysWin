#include "OdbBookie.hxx"

OdbBookie::OdbBookie(const QString &name)
    : m_name(name)
{

}

unsigned long OdbBookie::Id() const
{
    return m_id;
}

const QOdbList<QLazyWeakPointer<OdbSport> > &OdbBookie::Sports() const
{
    return m_sports;
}

const QString &OdbBookie::Name() const
{
    return m_name;
}
