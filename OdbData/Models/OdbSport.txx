#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/qt/list.hxx>
#include <odb/callback.hxx>
#include "OdbData/Models/OdbBookieEntity.txx"

class OdbBookie;
class OdbEvent;

#pragma db object
class OdbSport : public OdbBookieEntity
{
public:
    OdbSport(const QString &idInBookie, const QString &name);

    unsigned long Id() const;

    QString &Name();

    QLazySharedPointer<OdbBookie> &Booky();

    std::set<QLazyWeakPointer<OdbEvent>> &Events();

private:
    friend class odb::access;

    OdbSport () = default;

    #pragma db id auto
    unsigned long m_id;

    #pragma db not_null
    QString m_name;

    #pragma db not_null
    QLazySharedPointer<OdbBookie> m_booky;

    #pragma db value_not_null inverse(m_sport)
    std::set<QLazyWeakPointer<OdbEvent>> m_events;
};

#ifdef ODB_COMPILER
#include "OdbData/Models/OdbBookie.txx"
#include "OdbData/Models/OdbEvent.txx"
#endif
