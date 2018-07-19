#include "OdbContext.h"

template<class Entity, template <class Other> class PtrType, typename ... OtherLists>
void OdbContext::RegisterListForTracking(QOdbList<PtrType<Entity>> &entityList, OtherLists & ... otherLists)
{
    m_changeTracker.append([&entityList, this](){
        for(size_t idx(0), size(entityList.size()); idx < size; idx++)
        {
            switch (entityList._impl().state(idx)) {
            case odb::vector_impl::state_inserted:
                db->persist(entityList.at(idx).getEager());
                break;
            case odb::vector_impl::state_updated:
                db->update(entityList.at(idx).getEager());
                break;
            case odb::vector_impl::state_erased:
                db->erase(entityList.at(idx).getEager());
                break;
            default:
                break;
            }
        }
    });
    RegisterListForTracking(otherLists...);
}
