#ifndef __SINGLETON_OF_MANAGERS__
#define __SINGLETON_OF_MANAGERS__

#include "GraphicsManager.h"
#include "ScriptManager.h"
#include "PhysicsManager.h"
#include "API.h"

class qqqP::Singleton
{
    public:
        static qqqP::Singleton* getInstance();
        qqqP::GraphicsManager graphics_manager;
        qqqP::ScriptManager script_manager;
        qqqP::PhysicsManager physics_manager;
        float dt;
    private:
        Singleton() {}
        static qqqP::Singleton* instance;
};
#endif