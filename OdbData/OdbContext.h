#pragma once

#include <QScopedPointer>
#include "OdbEntitySet.hpp"
#include "OdbBookie-odb.hxx"
#include "QList"

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
    OdbContext();

    void SaveChanges();

private:
    OdbEntitySet<OdbBookie> m_bookies;

    QList<OdbEntitySet<OdbBookie> *> m_allSets;

    QScopedPointer<odb::sqlite::database> db;
};
