#ifndef __SCRIPT_MANAGER__
#define __SCRIPT_MANAGER__

class ScriptManager
{
public:
    void updateAll();
    bool addScript(Component* new_script);
    bool removeScript(Component* removing_script);

private:
    std::vector<Script*> scripts;
};

#endif