#pragma once

#include <QtCore/QScopedPointer>
#include <functional>
#include <unordered_map>
#include <QtCore/QList>

namespace odb
{
    namespace sqlite
    {
        class database;
    }
}

class OdbContext
{
public:
    static OdbContext &GetInstance();

private:
    friend class BaseEntity;
    static OdbContext * s_instance;

    OdbContext();

    std::unordered_map<const void*, QList<std::function<void()>>> m_changeTracker;

    QScopedPointer<odb::sqlite::database> db;
};
