#include "OdbMarketEvents.hxx"
#include "OdbEvent-odb.hxx"
#include "OdbMarket-odb.hxx"

bool OdbMarketEventsID::operator <(const OdbMarketEventsID &other) const
{
    if(m_eventId == other.m_eventId)
        return m_marketId < other.m_marketId;

    return m_eventId < other.m_eventId;
}

const OdbMarketEventsID &OdbMarketEvents::Id() const
{
    return m_id;
}

QLazySharedPointer<OdbMarket> &OdbMarketEvents::Market()
{
    return m_market;
}

QLazySharedPointer<OdbEvent> &OdbMarketEvents::Event()
{
    return m_event;
}

void OdbMarketEvents::Init(odb::callback_event e, odb::database &)
{
    if ( e == odb::callback_event::pre_erase   ||
         e == odb::callback_event::pre_persist ||
         e == odb::callback_event::pre_update   )
    {
        m_id.m_eventId = Event().objectId();
        m_id.m_marketId = Market().objectId();
    }
}
