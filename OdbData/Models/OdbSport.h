#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>

class OdbSportIdent;

#pragma db object
class OdbSport
{
public:
    unsigned long Id() const;
    const QLazySharedPointer<OdbSportIdent> &SportIdent() const;

private:
    friend class odb::access;
    OdbSport () = default;

    #pragma db id auto
    unsigned long m_id;

    #pragma db not_null
    QLazySharedPointer<OdbSportIdent> m_sportIdent;
};
