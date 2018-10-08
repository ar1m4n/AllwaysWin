#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/qt/list.hxx>
#include "OdbData/Models/OdbBookieEntity.txx"

class OdbRunner;
class OdbEvent;

#pragma db object
class OdbMarket : public OdbBookieEntity
{
public:
    OdbMarket(const QString & idInBookie, const QString &name);

    unsigned long Id() const;

    QString &Name();

    QLazySharedPointer<OdbEvent> &Event();

    std::set<QLazyWeakPointer<OdbRunner>> &Runners();

private:
    friend class odb::access;
    OdbMarket() = default;

    #pragma db id auto
    unsigned long m_id;

    #pragma db not_null
    QString m_name;

    #pragma db not_null
    QLazySharedPointer<OdbEvent> m_event;

    #pragma db value_not_null inverse(m_market)
    std::set<QLazyWeakPointer<OdbRunner>> m_runners;
};

#ifdef ODB_COMPILER
#include "OdbData/Models/OdbRunner.txx"
#include "OdbData/Models/OdbEvent.txx"
#endif
