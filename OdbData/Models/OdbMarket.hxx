#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/qt/list.hxx>
#include <odb/callback.hxx>

class OdbSport;

#pragma db object callback(UpdateSame)
class OdbMarket
{
public:
    OdbMarket(const QString &name);

    unsigned long Id() const;

    const QString &Name() const;

    const QLazySharedPointer<OdbSport> &Sport() const;

    const QOdbList<QLazySharedPointer<OdbMarket>> &SameAs() const;

private:
    friend class odb::access;
    OdbMarket() = default;

    #pragma db id auto
    unsigned long m_id;

    #pragma db not_null
    QString m_name;

    #pragma db not_null
    QLazySharedPointer<OdbSport> m_sport;

    #pragma db value_not_null
    mutable QOdbList<QLazySharedPointer<OdbMarket>> m_sameAs;

    #pragma db value_not_null inverse(m_sameAs)
    QOdbList<QLazyWeakPointer<OdbMarket>> m_asSame;

    void UpdateSame (odb::callback_event, odb::database&) const;
};

#ifdef ODB_COMPILER
#include "OdbSport.hxx"
#endif
