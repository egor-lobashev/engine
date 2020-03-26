#ifndef __DATA_STORAGE__
#define __DATA_STORAGE__


#include <string>
#include <map>
#include <vector>
#include "GameObject.h"
#include "GraphicsManager.h"

class GameObject;
class DataStorage;

class DataStorageDestructor{
    private:
        DataStorage* instance;
    public:
        ~DataStorageDestructor();
        void initialize(DataStorage* tmpinstance);
};


class DataStorage{
    private:
        static DataStorage* instance;
        static DataStorageDestructor destructor;
        std::map<std::string,GameObject*> map_of_game_objects;
    protected:    
        DataStorage() {}
        ~DataStorage();
        friend class DataStorageDestructor;
    public:
        static DataStorage* getInstance();
        bool addObject(std::string object_name , GameObject* obj);
        bool deleteObject(std::string object_name);
        GameObject* getObject(std::string object_name);
        std::vector <GameObject*> getAll();
};

#endif



    


