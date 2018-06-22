#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <QtCore/QList>

class OdbSport;

#pragma db object
class OdbBookie
{
public:
    unsigned long Id() const;

    const QList<QLazySharedPointer<OdbSport> > &Sports() const;

    const QString &Name() const;

private:
    friend class odb::access;

    #pragma db id auto
    unsigned long m_id;

    #pragma db not_null
    QString m_name;

    #pragma db value_not_null
    QList<QLazySharedPointer<OdbSport>> m_sports;
};

#ifdef ODB_COMPILER
#include "OdbSport.hxx"
#endif
