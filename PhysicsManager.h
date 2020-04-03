#ifndef _PHYSICS_MANAGER_
#define _PHYSICS_MANAGER_

#include <vector>
#include "Component.h"

class PhysicsManager{
    public:
        bool addCollider(Component* new_collider);
        bool removeCollider(Component* removing_collider);
        void checkForCollide( Collider* first , Collider* second );
        void checkAllCollisions();
    private:
        std::vector <Collider*> collider_objects;

};
#endif