#include "OdbBookie.txx"

OdbBookie::OdbBookie(unsigned long id, const QString &name)
    : m_id(id), m_name(name)
{
}

unsigned long OdbBookie::Id() const
{
    return m_id;
}

const QString &OdbBookie::Name() const
{
    return m_name;
}

std::set<QLazyWeakPointer<OdbSport> > &OdbBookie::Sports()
{
    return m_sports;
}
