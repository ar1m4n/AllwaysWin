#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>

class OdbMarket;

#pragma db object
class OdbRunner
{
public:
    OdbRunner(const QString &idInBookie, const QString &name);

    unsigned long Id() const;

    const QString &IdInBookie() const;

    QString &Name();

    QLazySharedPointer<OdbMarket> &Market();

private:
    friend class odb::access;
    OdbRunner() = default;

    #pragma db id auto
    unsigned long m_id;

    #pragma db index not_null
    QString m_idInBookie;

    #pragma db not_null
    QString m_name;

    #pragma db not_null
    QLazySharedPointer<OdbMarket> m_market;
};

#ifdef ODB_COMPILER
#include "OdbMarket.hxx"
#endif
