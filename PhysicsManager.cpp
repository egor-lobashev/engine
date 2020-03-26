#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::instance = nullptr;

PhysicsManager* PhysicsManager::getInstance(){

    if(!instance){
        instance = new PhysicsManager;
    }
    return instance;
}

bool PhysicsManager::addCollider(Component* new_collider){

    try
    {
        collider_objects.push_back(static_cast<Collider*>(new_collider));
        return true;
    }
    catch(...)
    { 
        return false;
    }
}

bool PhysicsManager::removeCollider(Collider* removing_collider){

    for(int i = 0 ; i < collider_objects.size() ; i++){

        if(collider_objects[i] == removing_collider)
        {
            collider_objects.erase(collider_objects.begin() + i );
            return true;
        }

        return false;
    }
}



