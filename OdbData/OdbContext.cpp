#include "OdbContext.hpp"
#include <odb/transaction.hxx>

OdbContext::OdbContext(const QString &connectionStr)
{
    db.reset(new odb::sqlite::database(connectionStr.toStdString()));
    RegisterListForTracking(m_bookies, m_events, m_eventParticipants, m_markets,
                            m_marketEvents, m_prices, m_runners, m_sports);
}

void OdbContext::SaveChanges()
{
    auto tr = db->begin();

    for(auto &tracker : m_changeTracker)
    {
        tracker();
    }

    tr->commit();
}

void OdbContext::RegisterListForTracking() { }
