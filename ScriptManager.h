#ifndef __SCRIPT_MANAGER__
#define __SCRIPT_MANAGER__

class ScriptManager
{
public:
    static ScriptManager* getInstance()
    {
        if (!instance)
            instance = new ScriptManager();
        return instance;
    }

    void updateAll()
    {
        // Zhenya's code here
    }

    bool addObject(std::string object_name , GameObject* obj)
    {
        if(scripted_objects[object_name] = obj)
        {
            return true;
        }

        return false;
    }

    bool deleteObject(std::string object_name)
    {
        if(scripted_objects.count(object_name) == 1){

            delete scripted_objects[object_name];
            scripted_objects.erase(object_name);
            return true;
        }
        return false;
    }

private:
    ScriptManager() {}
    static ScriptManager* instance;
    std::map<std::string, GameObject*> scripted_objects;
};

ScriptManager* ScriptManager::instance = nullptr;

#endif