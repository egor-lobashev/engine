#ifndef __SINGLETON_OF_MANAGERS__
#define __SINGLETON_OF_MANAGERS__

#include "GraphicsManager.h"
#include "ScriptManager.h"
#include "PhysicsManager.h"

class Singleton
{
    public:
        static Singleton* getInstance();
        GraphicsManager graphics_manager;
        ScriptManager script_manager;
        PhysicsManager physics_manager;
        float dt;
    private:
        Singleton() {}
        static Singleton* instance;
};
#endif