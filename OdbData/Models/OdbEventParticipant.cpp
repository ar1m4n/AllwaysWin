#include "OdbEventParticipant.hxx"

OdbEventParticipant::OdbEventParticipant(const QString &idInBookie, const QString &name)
    :m_idInBookie(idInBookie), m_name(name)
{

}

unsigned long OdbEventParticipant::Id() const
{
    return m_id;
}

const QString &OdbEventParticipant::IdInBookie() const
{
    return m_idInBookie;
}

QString &OdbEventParticipant::Name()
{
    return m_name;
}

QOdbList<QLazyWeakPointer<OdbEvent> > &OdbEventParticipant::Events()
{
    return m_events;
}
