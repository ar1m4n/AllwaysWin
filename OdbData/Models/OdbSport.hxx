#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <QtCore/QList>

class OdbBookie;

#pragma db object
class OdbSport
{
public:
    OdbSport(const QString &id);

    const QString &Id() const;

    const QString &Name() const;

    const QList<QLazyWeakPointer<OdbBookie>> &Bookies() const;

private:
    friend class odb::access;

    OdbSport () = default;

    #pragma db id
    QString m_id;

    #pragma db not_null
    QString m_name;

    #pragma db value_not_null inverse(m_sports)
    QList<QLazyWeakPointer<OdbBookie>> m_bookies;

    #pragma db value_not_null
    QList<QLazySharedPointer<OdbSport>> m_sameAs;

    #pragma db value_not_null inverse(m_sameAs)
    QList<QLazyWeakPointer<OdbSport>> m_asSame;
};

#ifdef ODB_COMPILER
#include "OdbBookie.hxx"
#endif
