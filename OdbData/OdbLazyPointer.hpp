#include "OdbLazyPointer.h"

template<class Entity>
OdbLazyPointer<Entity>::OdbLazyPointer(Entity *entity)
{
    m_lazyPtr = QLazySharedPointer<Entity>(entity);

    m_changeTrackingState = ChangeTrackingState::Persist;
}

template<class Entity>
OdbLazyPointer<Entity>::OdbLazyPointer(const QLazySharedPointer<Entity> &entityPtr)
    :OdbLazyPointer(entityPtr.data())
{

}

template<class Entity>
OdbLazyPointer<Entity>::~OdbLazyPointer()
{
    if(m_changeTrackingState == ChangeTrackingState::Persist)
        m_changeTrackingState = ChangeTrackingState::EraseTransient;
    else
        m_changeTrackingState = ChangeTrackingState::Erase;
}

template<class Entity>
Entity *OdbLazyPointer<Entity>::operator ->()
{
    const auto self = this;
    if(m_changeTrackingState == ChangeTrackingState::None)
        m_changeTrackingState = ChangeTrackingState::Update;

    return const_cast<Entity*>(self->operator ->());
}

template<class Entity>
const Entity *OdbLazyPointer<Entity>::operator ->() const
{
    auto self = const_cast<OdbLazyPointer<Entity>*>(this);
    if(!self->m_lazyPtr.loaded())
        self->m_lazyPtr.load();

    return m_lazyPtr.operator ->();
}

template<class Entity>
Entity &OdbLazyPointer<Entity>::operator *()
{
    return *this->operator ->();
}

template<class Entity>
const Entity &OdbLazyPointer<Entity>::operator *() const
{
    return *this->operator ->();
}

template<class Entity>
bool OdbLazyPointer<Entity>::operator!() const
{
    return !m_lazyPtr;
}

template<class Entity>
Entity *OdbLazyPointer<Entity>::Data() const
{
    return m_lazyPtr.data();
}
