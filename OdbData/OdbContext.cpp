#include "OdbContext.h"
#include <odb/sqlite/database.hxx>

OdbContext * OdbContext::s_instance = nullptr;

OdbContext &OdbContext::GetInstance()
{
    if(!s_instance)
        s_instance = new OdbContext();

    return *s_instance;
}

OdbContext::OdbContext()
{

}
