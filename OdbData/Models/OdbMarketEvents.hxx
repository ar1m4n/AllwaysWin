#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/qt/list.hxx>
#include <odb/callback.hxx>

class OdbMarket;
class OdbEvent;
class OdbRunner;

#pragma db value
class OdbMarketEventsID
{
public:
    unsigned long m_marketId;
    unsigned long m_eventId;

    bool operator < (const OdbMarketEventsID& other) const;
};

#pragma db object callback(Init)
class OdbMarketEvents
{
public:
    const OdbMarketEventsID &Id() const;

    QLazySharedPointer<OdbMarket> &Market();

    QLazySharedPointer<OdbEvent> &Event();

private:
    friend class odb::access;
    OdbMarketEvents() = default;

    #pragma db id
    OdbMarketEventsID m_id;

    #pragma db value_not_null
    QLazySharedPointer<OdbMarket> m_market;

    #pragma db value_not_null
    QLazySharedPointer<OdbEvent> m_event;

    QOdbList<QLazySharedPointer<OdbRunner>> m_runners;

    void Init(odb::callback_event e, odb::database& db);
};

#ifdef ODB_COMPILER
#include "OdbMarket.hxx"
#include "OdbEvent.hxx"
#include "OdbRunner.hxx"
#endif
