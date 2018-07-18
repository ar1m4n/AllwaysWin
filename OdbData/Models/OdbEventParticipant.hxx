#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/qt/list.hxx>

class OdbEvent;

#pragma db object
class OdbEventParticipant
{
public:
    OdbEventParticipant(const QString &idInBookie, const QString &name);

    unsigned long Id() const;

    const QString &IdInBookie() const;

    QString &Name();

    QOdbList<QLazyWeakPointer<OdbEvent>> &Events();

private:
    friend class odb::access;

    OdbEventParticipant() = default;

    #pragma db id auto
    unsigned long m_id;

    #pragma db index not_null
    QString m_idInBookie;

    #pragma db not_null
    QString m_name;

    #pragma db value_not_null inverse(m_participants)
    QOdbList<QLazyWeakPointer<OdbEvent>> m_events;
};

#ifdef ODB_COMPILER
#include "OdbEvent.hxx"
#endif
