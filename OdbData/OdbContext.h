#pragma once

#include <QScopedPointer>
#include <odb/qt/list.hxx>
#include "OdbBookie-odb.hxx"
#include "OdbEvent-odb.hxx"
#include "OdbEventParticipant.hxx"
#include "OdbMarket-odb.hxx"
#include "OdbMarketEvents-odb.hxx"
#include "OdbPrice-odb.hxx"
#include "OdbRunner-odb.hxx"
#include "OdbSport-odb.hxx"
#include <odb/sqlite/database.hxx>
#include <functional>

class OdbContext
{
public:
    OdbContext(const QString &connectionStr);

    QOdbList<QLazySharedPointer<OdbBookie>>             m_bookies;
    QOdbList<QLazySharedPointer<OdbEvent>>              m_events;
    QOdbList<QLazySharedPointer<OdbEventParticipant>>   m_eventParticipants;
    QOdbList<QLazySharedPointer<OdbMarket>>             m_markets;
    QOdbList<QLazySharedPointer<OdbMarketEvents>>       m_marketEvents;
    QOdbList<QLazySharedPointer<OdbPrice>>              m_prices;
    QOdbList<QLazySharedPointer<OdbRunner>>             m_runners;
    QOdbList<QLazySharedPointer<OdbSport>>              m_sports;

    void SaveChanges();

private:

    QScopedPointer<odb::sqlite::database> db;

    QList<std::function<void()>> m_changeTracker;

    template<class Entity, template <class Other> class PtrType, typename ... OtherLists>
    void RegisterListForTracking(QOdbList<PtrType<Entity>> &entityList, OtherLists & ... otherLists);

    void RegisterListForTracking();
};
