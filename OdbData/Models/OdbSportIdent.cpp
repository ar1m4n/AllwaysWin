#include "OdbSportIdent.h"
#include <QList>
#include <QPair>

OdbSportIdentId OdbSportIdent::Id() const
{
    return m_id;
}

const QLazyWeakPointer<OdbSport> &OdbSportIdent::Sport() const
{
    return m_sport;
}

bool OdbSportIdentId::operator <(const OdbSportIdentId &other) const
{
    QList<QPair<const QString*, const QString*>> valuesToCompare = {
        { &moneybooksID, &other.moneybooksID },
        { &pinnacleID, &other.pinnacleID },
        { &smarketsID, &other.smarketsID },
        { &betdaqID, &other.betdaqID }
    };

    for(auto &p : valuesToCompare)
    {
        if(p.first->compare(*p.second, Qt::CaseInsensitive) < 0)
            return true;
    }

    return false;
}
