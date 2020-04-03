#include "GameObject.h"
#include "ScriptManager.h"

void ScriptManager::updateAll()
{
    for (Script* script : scripts)
    {
        script->update();
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