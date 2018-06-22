#include "OdbBookie.hxx"

unsigned long OdbBookie::Id() const
{
    return m_id;
}

const QList<QLazySharedPointer<OdbSport> > &OdbBookie::Sports() const
{
    return m_sports;
}

const QString &OdbBookie::Name() const
{
    return m_name;
}
