#include "GameObject.h"
#include "ScriptManager.h"

ScriptManager* ScriptManager::getInstance()
{
    if (!instance)
        instance = new ScriptManager();
    return instance;
}

void ScriptManager::updateAll(float dt)
{
    for (Script* script : scripts)
    {
        script->update(dt);
    }
}

bool ScriptManager::addObject(Script* script)
{
    try
    {
        scripts.push_back(script);
        return true;
    }
    catch(...)
    {
        return false;
    }
}

// bool ScriptManager::deleteObject(std::string object_name)
// {
//     if(scripts.count(object_name) == 1){

//         delete scripts[object_name];
//         scripted_objects.erase(object_name);
//         return true;
//     }
//     return false;
// }