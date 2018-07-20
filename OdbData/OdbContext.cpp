#include "OdbContext.h"

OdbContext *OdbContext::s_instance = nullptr;

OdbContext &OdbContext::Instance()
{
    if(!s_instance)
        s_instance = new OdbContext("");

    return *s_instance;
}

OdbContext::OdbContext(const QString &connectionStr)
{
    db.reset(new odb::sqlite::database(connectionStr.toStdString()));
}
