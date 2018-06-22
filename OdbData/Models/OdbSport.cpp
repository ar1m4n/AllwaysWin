#include "OdbSport.h"
#include "OdbSportIdent.h"

unsigned long OdbSport::Id() const
{
    return m_id;
}

const QLazySharedPointer<OdbSportIdent> &OdbSport::SportIdent() const
{
    return m_sportIdent;
}
