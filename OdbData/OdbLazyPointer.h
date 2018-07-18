#pragma once

#include <odb/qt/lazy-ptr.hxx>
#include <unordered_map>

enum class ChangeTrackingState {
    None, Persist, Update, Erase, EraseTransient
};

template<class Entity>
class OdbEntitySet;

template<class Entity>
class OdbLazyPointer
{
private:
    friend class OdbContext;

    QLazySharedPointer<Entity> m_lazyPtr;

    ChangeTrackingState m_changeTrackingState = ChangeTrackingState::None;

public:
    OdbLazyPointer(Entity* entity);

    OdbLazyPointer(const QLazySharedPointer<Entity> &entityPtr);

    ~OdbLazyPointer();

    Entity* operator ->();
    const Entity* operator ->() const;

    Entity& operator *();
    const Entity& operator *() const;

    bool operator! () const;

    Entity* Data() const;
};
