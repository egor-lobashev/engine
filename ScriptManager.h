#ifndef __SCRIPT_MANAGER__
#define __SCRIPT_MANAGER__

#include "GameObject.h"

class ScriptManager
{
public:
    static ScriptManager* getInstance();
    void updateAll(float dt);
    bool addScript(Component* new_script);
    bool removeScript(Component* removing_script);

private:
    ScriptManager() {}
    static ScriptManager* instance;
    std::vector<Script*> scripts;
};

#endif