#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>

class OdbSport;

#pragma db value
struct OdbSportIdentId
{
    QString moneybooksID, pinnacleID, smarketsID, betdaqID;
    bool operator <(const OdbSportIdentId &other) const;
};

#pragma db object
class OdbSportIdent
{
public:
    OdbSportIdentId Id() const;
    const QLazyWeakPointer<OdbSport> &Sport() const;

private:
    friend class odb::access;

    #pragma db id
    OdbSportIdentId m_id;

    #pragma db inverse(m_sportIdent)
    QLazyWeakPointer<OdbSport> m_sport;
};
