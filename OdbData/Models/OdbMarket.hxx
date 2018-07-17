#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/qt/list.hxx>

class OdbSport;
class OdbRunner;

#pragma db object
class OdbMarket
{
public:
    OdbMarket(const QString & idInBookie, const QString &name);

    unsigned long Id() const;

    const QString &IdInBookie() const;

    QString &Name();

    QLazySharedPointer<OdbSport> &Sport();

    QOdbList<QLazyWeakPointer<OdbRunner>> &Runners();

private:
    friend class odb::access;
    OdbMarket() = default;

    #pragma db id auto
    unsigned long m_id;

    #pragma db index not_null
    QString m_idInBookie;

    #pragma db not_null
    QString m_name;

    #pragma db not_null
    QLazySharedPointer<OdbSport> m_sport;

    #pragma db value_not_null inverse(m_market)
    QOdbList<QLazyWeakPointer<OdbRunner>> m_runners;
};

#ifdef ODB_COMPILER
#include "OdbSport.hxx"
#include "OdbRunner.hxx"
#endif
