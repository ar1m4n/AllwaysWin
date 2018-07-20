#pragma once

#include <QScopedPointer>
#include <odb/qt/list.hxx>
#include "OdbBookie-odb.hxx"
#include "OdbEvent-odb.hxx"
#include "OdbEventParticipant.hxx"
#include "OdbMarket-odb.hxx"
#include "OdbMarketEvents-odb.hxx"
#include "OdbPrice-odb.hxx"
#include "OdbRunner-odb.hxx"
#include "OdbSport-odb.hxx"
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
