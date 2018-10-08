#pragma once

#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/qt/list.hxx>

class OdbSport;

#pragma db object
class OdbBookie
{
public:
    OdbBookie(unsigned long id, const QString &name);

    unsigned long Id() const;

    const QString &Name() const;

    std::set<QLazyWeakPointer<OdbSport>> &Sports();

private:
    friend class odb::access;

    OdbBookie() = default;

    #pragma db id
    unsigned long m_id;

    #pragma db not_null
    QString m_name;

    #pragma db value_not_null inverse(m_booky)
    std::set<QLazyWeakPointer<OdbSport>> m_sports;
};

#ifdef ODB_COMPILER
#include "OdbData/Models/OdbSport.txx"
#endif
