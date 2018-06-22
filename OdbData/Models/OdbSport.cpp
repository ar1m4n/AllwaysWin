#include "OdbSport.hxx"

OdbSport::OdbSport(const QString &id)
    :m_id(id)
{

}

const QString &OdbSport::Id() const
{
    return m_id;
}

const QList<QLazyWeakPointer<OdbBookie> > &OdbSport::Bookies() const
{
    return m_bookies;
}

const QString &OdbSport::Name() const
{
    return m_name;
}
