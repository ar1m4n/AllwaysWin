#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/qt/list.hxx>

class OdbMarketEvents;

#ifdef ODB_COMPILER
#include "OdbMarketEvents.hxx"
#endif

#pragma db object
class OdbMarket
{
public:
    OdbMarket(const QString & idInBookie, const QString &name);

    unsigned long Id() const;

    const QString &IdInBookie() const;

    QString &Name();

    QOdbList<QLazyWeakPointer<OdbMarketEvents>> &MarketEvents();

private:
    friend class odb::access;
    OdbMarket() = default;

    #pragma db id auto
    unsigned long m_id;

    #pragma db index not_null
    QString m_idInBookie;

    #pragma db not_null
    QString m_name;

    #pragma db inverse(m_market)
    QOdbList<QLazyWeakPointer<OdbMarketEvents>> m_marketEvents;
};
