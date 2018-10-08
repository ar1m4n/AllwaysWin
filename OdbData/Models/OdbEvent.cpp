#include "OdbEvent.txx"

OdbEvent::OdbEvent(const QString &idInBookine, const QString &name, const QDateTime &date, const QString &place)
    : OdbBookieEntity(idInBookine), m_name(name), m_date(date), m_place(place)
{

}

unsigned long OdbEvent::Id() const
{
    return m_id;
}

QString &OdbEvent::Name()
{
    return m_name;
}

QDateTime &OdbEvent::Date()
{
    return m_date;
}

QString &OdbEvent::Place()
{
    return m_place;
}

QLazySharedPointer<OdbSport> &OdbEvent::Sport()
{
    return m_sport;
}

std::set<QLazyWeakPointer<OdbMarket>> &OdbEvent::Markets()
{
    return m_markets;
}

std::set<QLazyWeakPointer<OdbEventParticipant> > &OdbEvent::Participants()
{
    return m_participants;
}
