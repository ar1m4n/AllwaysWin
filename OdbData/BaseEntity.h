#ifndef BASEENTITY_H
#define BASEENTITY_H

class BaseEntity
{
public:
    template <class EntityType>
    static void Register(EntityType *entity);
};

#endif // BASEENTITY_H
