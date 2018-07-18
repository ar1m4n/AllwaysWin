#include "OdbContext.h"
#include <odb/sqlite/database.hxx>
#include <odb/transaction.hxx>
#include <functional>

OdbContext::OdbContext()
{

}

void OdbContext::SaveChanges()
{
    auto tr = db->begin();
    QList<std::function<void()>> lateActions;
    for(auto set : m_allSets)
    {
        for(auto ptrIt(set->m_internalSet.begin()); ptrIt != set->m_internalSet.end(); ptrIt++)
        {
            lateActions.append([ptrIt](){
                ptrIt.value().m_changeTrackingState = ChangeTrackingState::None;
            });

            switch (ptrIt.value().m_changeTrackingState) {
            case ChangeTrackingState::Persist:
                db->persist(ptrIt.value().m_lazyPtr.getEager());
                break;
            case ChangeTrackingState::Update:
                db->update(ptrIt.value().m_lazyPtr.getEager());
                break;
            case ChangeTrackingState::Erase:
                db->erase(ptrIt.value().m_lazyPtr.getEager());
            case ChangeTrackingState::EraseTransient:
                lateActions.back() = [set, ptrIt](){
                    set->m_internalSet.erase(ptrIt);
                };
                break;
            default:
                break;
            }
        }
    }

    for(auto &action : lateActions)
    {
        action();
    }

    tr->commit();
}
