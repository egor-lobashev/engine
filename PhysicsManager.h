#ifndef _PHYSICS_MANAGER_
#define _PHYSICS_MANAGER_

#include <vector>
#include "Component.h"
#include "API.h"

class qqqP::PhysicsManager{
    public:
        bool addCollider(qqq::Component* new_collider);
        bool removeCollider(qqq::Component* removing_collider);
        bool checkForCollide( qqq::Collider* first , qqq::Collider* second );
        void checkAllCollisions();
    private:
        std::vector <qqq::Collider*> collider_objects;

};
#endif