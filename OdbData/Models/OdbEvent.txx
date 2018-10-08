#pragma once

#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/qt/list.hxx>
#include "OdbData/Models/OdbBookieEntity.txx"

class OdbSport;
class OdbMarket;
class OdbEventParticipant;

#pragma db object
class OdbEvent : public OdbBookieEntity
{
public:
    OdbEvent(const QString &idInBookine, const QString &name, const QDateTime &date, const QString &place);

    unsigned long Id() const;

    QString &Name();

    QDateTime &Date();

    QString &Place();

    QLazySharedPointer<OdbSport> &Sport();

    std::set<QLazyWeakPointer<OdbMarket>> &Markets();

    std::set<QLazyWeakPointer<OdbEventParticipant>> &Participants();

private:
    friend class odb::access;

    OdbEvent() = default;

    #pragma db id auto
    unsigned long m_id;

    #pragma db not_null
    QString m_name;

    #pragma db type("INTEGER")
    QDateTime m_date;

    #pragma db not_null
    QString m_place;

    #pragma db not_null
    QLazySharedPointer<OdbSport> m_sport;

    #pragma db value_not_null inverse(m_event)
    std::set<QLazyWeakPointer<OdbMarket>> m_markets;

    #pragma db value_not_null inverse(m_event)
    std::set<QLazyWeakPointer<OdbEventParticipant>> m_participants;
};

#ifdef ODB_COMPILER
#include "OdbData/Models/OdbMarket.txx"
#include "OdbData/Models/OdbSport.txx"
#include "OdbData/Models/OdbEventParticipant.txx"
#endif
