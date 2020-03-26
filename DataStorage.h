#ifndef __DATA_STORAGE__
#define __DATA_STORAGE__


#include <string>
#include <map>
#include <vector>
#include "GameObject.h"
#include "GraphicsManager.h"

class GameObject;

class DataStorage{
    public:
        ~DataStorage();
        static DataStorage* getInstance();
        bool addObject(std::string object_name , GameObject* obj);
        bool deleteObject(std::string object_name);
        GameObject* getObject(std::string object_name);
        std::vector <GameObject*> getAll();
    private:
        DataStorage() {}
        static DataStorage* instance;
        std::map<std::string,GameObject*> map_of_game_objects;
};

#endif



    


