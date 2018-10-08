#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/qt/list.hxx>
#include "OdbData/Models/OdbBookieEntity.txx"

class OdbMarket;
class OdbPrice;

#pragma db object
class OdbRunner : public OdbBookieEntity
{
public:
    OdbRunner(const QString &idInBookie, const QString &name);

    unsigned long Id() const;

    QString &Name();

    QLazySharedPointer<OdbMarket> &Market();

    QOdbList<QLazyWeakPointer<OdbPrice>> &Prices();

private:
    friend class odb::access;
    OdbRunner() = default;

    #pragma db id auto
    unsigned long m_id;

    #pragma db not_null
    QString m_name;

    #pragma db not_null
    QLazySharedPointer<OdbMarket> m_market;

    #pragma db value_not_null inverse(m_runner)
    QOdbList<QLazyWeakPointer<OdbPrice>> m_prices;
};

#ifdef ODB_COMPILER
#include "OdbData/Models/OdbMarket.txx"
#include "OdbData/Models/OdbPrice.txx"
#endif
