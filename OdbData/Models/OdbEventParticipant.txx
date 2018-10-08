#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/qt/list.hxx>
#include "OdbData/Models/OdbBookieEntity.txx"

class OdbEvent;

#pragma db object
class OdbEventParticipant : public OdbBookieEntity
{
public:
    OdbEventParticipant(const QString &idInBookie, const QString &name);

    unsigned long Id() const;

    QString &Name();

    QLazySharedPointer<OdbEvent> &Event();

private:
    friend class odb::access;

    OdbEventParticipant() = default;

    #pragma db id auto
    unsigned long m_id;

    #pragma db not_null
    QString m_name;

    #pragma db not_null
    QLazySharedPointer<OdbEvent> m_event;
};

#ifdef ODB_COMPILER
#include "OdbData/Models/OdbEvent.txx"
#endif
