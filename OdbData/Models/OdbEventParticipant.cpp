#include "OdbEventParticipant.txx"

OdbEventParticipant::OdbEventParticipant(const QString &idInBookie, const QString &name)
    :OdbBookieEntity(idInBookie), m_name(name)
{

}

unsigned long OdbEventParticipant::Id() const
{
    return m_id;
}

QString &OdbEventParticipant::Name()
{
    return m_name;
}

QLazySharedPointer<OdbEvent> &OdbEventParticipant::Event()
{
    return m_event;
}
