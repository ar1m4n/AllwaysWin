#pragma once

#include <QScopedPointer>
#include <odb/qt/list.hxx>
#include <odb/sqlite/database.hxx>

class OdbContext
{
public:
    static OdbContext &Instance();
    QScopedPointer<odb::sqlite::database> db;

private:
    OdbContext(const QString &connectionStr);
    static OdbContext *s_instance;
};
