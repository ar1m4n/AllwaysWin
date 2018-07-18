#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/qt/list.hxx>

class OdbSport;
class OdbMarketEvents;
class OdbEventParticipant;

#ifdef ODB_COMPILER
#include "OdbMarketEvents.hxx"
#endif

#pragma db object
class OdbEvent
{
public:
    OdbEvent(const QString &idInBookine, const QString &name);

    unsigned long Id() const;

    const QString &IdInBookie() const;

    QString &Name();

    QLazyWeakPointer<OdbSport> &Sport();

    QLazyWeakPointer<OdbMarketEvents> &EventMarkets();

    QOdbList<QLazySharedPointer<OdbEventParticipant>> &Participants();

private:
    friend class odb::access;

    OdbEvent() = default;

    #pragma db id auto
    unsigned long m_id;

    #pragma db index not_null
    QString m_idInBookie;

    #pragma db not_null
    QString m_name;

    #pragma db value_not_null inverse(m_events)
    QLazyWeakPointer<OdbSport> m_sport;

    #pragma db inverse(m_event)
    QLazyWeakPointer<OdbMarketEvents> m_eventMarkets;

    #pragma db value_not_null
    QOdbList<QLazySharedPointer<OdbEventParticipant>> m_participants;
};

#ifdef ODB_COMPILER
#include "OdbSport.hxx"
#include "OdbEventParticipant.hxx"
#endif
