#include "BaseEntity.h"
#include "OdbContext.h"
#include <odb/sqlite/database.hxx>

template <class EntityType>
void BaseEntity::Register(EntityType *entity)
{
    auto el = OdbContext::GetInstance().m_changeTracker.emplace(entity, QList<std::function<void()>>());
    el.first->second.push_back([entity](){
        OdbContext::GetInstance().db->persist(entity);
    });
}
