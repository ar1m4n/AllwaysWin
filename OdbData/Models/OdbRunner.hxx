#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/qt/list.hxx>

class OdbMarketEvents;
class OdbPrice;

#ifdef ODB_COMPILER
#include "OdbMarketEvents.hxx"
#endif

#pragma db object
class OdbRunner
{
public:
    OdbRunner(const QString &idInBookie, const QString &name);

    unsigned long Id() const;

    const QString &IdInBookie() const;

    QString &Name();

    QLazyWeakPointer<OdbMarketEvents> &MarketEvent();

    QOdbList<QLazySharedPointer<OdbPrice>> &Prices();

private:
    friend class odb::access;
    OdbRunner() = default;

    #pragma db id auto
    unsigned long m_id;

    #pragma db index not_null
    QString m_idInBookie;

    #pragma db not_null
    QString m_name;

    #pragma db not_null inverse (m_runners)
    QLazyWeakPointer<OdbMarketEvents> m_marketEvent;

    QOdbList<QLazySharedPointer<OdbPrice>> m_prices;
};

#ifdef ODB_COMPILER
#include "OdbPrice.hxx"
#endif
