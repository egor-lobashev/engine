#ifndef _PHYSICS_MANAGER_
#define _PHYSICS_MANAGER_

#include <vector>
#include "Component.h"


class PhysicsManager{
    public:
        static PhysicsManager* getInstance();
        bool addCollider(Component* new_collider);
        bool removeCollider(Collider* removing_collider);


    private:
        static PhysicsManager* instance;
        std::vector <Collider*> collider_objects;

};
#endif