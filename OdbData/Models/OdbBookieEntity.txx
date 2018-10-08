#pragma once

#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <odb/qt/list.hxx>
#include <set>

#pragma db object abstract
class OdbBookieEntity
{
public:
    OdbBookieEntity(const QString &idInBookie);

    const QString &IdInBookie() const;

protected:
    friend class odb::access;

    OdbBookieEntity() = default;

    #pragma db index not_null
    QString m_idInBookie;
};

template <class Entity, template <class PtrValueType> class PtrType>
bool operator <(const PtrType<Entity> &a, const PtrType<Entity> &b)
{
    return a.data()->IdInBookie() < b.data()->IdInBookie();
};
