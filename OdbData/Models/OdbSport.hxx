#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/qt/list.hxx>
#include <odb/callback.hxx>

class OdbBookie;
class OdbMarket;

#pragma db object
class OdbSport
{
public:
    OdbSport(const QString &idInBookie, const QString &name);

    unsigned long Id() const;

    const QString &IdInBookie() const;

    QString &Name();

    QLazySharedPointer<OdbBookie> &Booky();

    QOdbList<QLazyWeakPointer<OdbMarket>> &Markets();

private:
    friend class odb::access;

    OdbSport () = default;

    #pragma db id auto
    unsigned long m_id;

    #pragma db index not_null
    QString m_idInBookie;

    #pragma db not_null
    QString m_name;

    #pragma db not_null
    QLazySharedPointer<OdbBookie> m_booky;

    #pragma db value_not_null inverse(m_sport)
    QOdbList<QLazyWeakPointer<OdbMarket>> m_markets;
};

#ifdef ODB_COMPILER
#include "OdbBookie.hxx"
#include "OdbMarket.hxx"
#endif
