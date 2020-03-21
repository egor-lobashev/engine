#ifndef __SCRIPT_MANAGER__
#define __SCRIPT_MANAGER__

#include "GameObject.h"

class ScriptManager
{
public:
    static ScriptManager* getInstance();
    void updateAll(float dt);
    bool addObject(Script* script);
    bool deleteObject(std::string object_name);

private:
    ScriptManager() {}
    static ScriptManager* instance;
    std::vector<Script*> scripts;
};

ScriptManager* ScriptManager::instance = nullptr;

#endif