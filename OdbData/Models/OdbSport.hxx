#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/qt/list.hxx>
#include <odb/callback.hxx>

class OdbBookie;
class OdbEvent;

#pragma db object
class OdbSport
{
public:
    OdbSport(const QString &idInBookie, const QString &name);

    unsigned long Id() const;

    const QString &IdInBookie() const;

    QString &Name();

    QLazyWeakPointer<OdbBookie> &Booky();

    QOdbList<QLazySharedPointer<OdbEvent>> &Events();

private:
    friend class odb::access;

    OdbSport () = default;

    #pragma db id auto
    unsigned long m_id;

    #pragma db index not_null
    QString m_idInBookie;

    #pragma db not_null
    QString m_name;

    #pragma db not_null inverse(m_sports)
    QLazyWeakPointer<OdbBookie> m_booky;

    QOdbList<QLazySharedPointer<OdbEvent>> m_events;
};

#ifdef ODB_COMPILER
#include "OdbBookie.hxx"
#include "OdbEvent.hxx"
#endif
