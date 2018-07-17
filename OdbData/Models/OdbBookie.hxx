#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/qt/list.hxx>

class OdbSport;

#pragma db object
class OdbBookie
{
public:
    OdbBookie(const QString &name);

    unsigned long Id() const;

    QString &Name();

    QOdbList<QLazyWeakPointer<OdbSport> > &Sports();

private:
    friend class odb::access;

    OdbBookie() = default;

    #pragma db id auto
    unsigned long m_id;

    #pragma db not_null
    QString m_name;

    #pragma db value_not_null inverse(m_booky)
    QOdbList<QLazyWeakPointer<OdbSport>> m_sports;
};

#ifdef ODB_COMPILER
#include "OdbSport.hxx"
#endif
