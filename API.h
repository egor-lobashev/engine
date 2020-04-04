#ifndef __QQQ_API__
#define __QQQ_API__

namespace qqqP
{
    class DataStorage;
    class Singleton;
    class GraphicsManager;
    class ScriptManager;
    class PhysicsManager;
}

namespace qqq
{
    class GameObject;
    class Component;
    class Renderer;
    class Script;
    class Collider;

    void runGame(int window_width, int window_height, std::string window_name);
    qqq::GameObject* getObject(std::string name);
    float absoluteTime();
    float relativeTime();
}

#endif