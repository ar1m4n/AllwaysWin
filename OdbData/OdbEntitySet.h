#pragma once

#include "OdbLazyPointer.hpp"
#include <QHash>

template<class Entity>
class OdbEntitySet
{
private:
    friend class OdbContext;
    QHash<const void*, OdbLazyPointer<Entity>> m_internalSet;

public:
    OdbEntitySet();
};
