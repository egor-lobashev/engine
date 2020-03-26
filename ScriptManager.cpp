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

bool ScriptManager::addScript(Component* new_script)
{
    try
    {
        scripts.push_back(static_cast<Script*>(new_script));
        return true;
    }
    catch(...)
    {
        return false;
    }
}

bool ScriptManager::removeScript(Component* removing_script)
{
    for (int i = 0; i < scripts.size(); i++)
    {
        if (scripts[i] == removing_script)
        {
            scripts.erase(scripts.begin() + i);
            return true;
        }
    }
    return false;
}

ScriptManager* ScriptManager::instance = nullptr;