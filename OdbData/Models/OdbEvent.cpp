#include "OdbEvent.hxx"

OdbEvent::OdbEvent(const QString &idInBookine, const QString &name)
    : m_idInBookie(idInBookine), m_name(name)
{

}

unsigned long OdbEvent::Id() const
{
    return m_id;
}

const QString &OdbEvent::IdInBookie() const
{
    return m_idInBookie;
}

QString &OdbEvent::Name()
{
    return m_name;
}

QLazyWeakPointer<OdbSport> &OdbEvent::Sport()
{
    return m_sport;
}

QLazyWeakPointer<OdbMarketEvents> &OdbEvent::EventMarkets()
{
    return m_eventMarkets;
}

QOdbList<QLazySharedPointer<OdbEventParticipant> > &OdbEvent::Participants()
{
    return m_participants;
}
