#ifndef __DATA_STORAGE__
#define __DATA_STORAGE__


#include <string>
#include <map>
#include <vector>
#include "GameObject.h"
#include "GraphicsManager.h"

class GameObject;
// class DataStorage;

// class DataStorageDistructor{
//     private:
//         DataStorage* sample;
//     public:
//         ~DataStorageDistructor();
//         void initialize(DataStorage* s);
// };


class DataStorage{
    private:
        static DataStorage* sample;
        //static DataStorageDistructor distructor;
        std::map<std::string,GameObject*> map_of_game_objects;
    //protected:    
        DataStorage() {};
        DataStorage(const DataStorage&);
        DataStorage& operator = (DataStorage&);
        //friend class DataStorageDistructor;
    public:
        static DataStorage* getSample();
        bool addObject(std::string object_name , GameObject* obj);
        bool deleteObject(std::string object_name);
        GameObject* getObject(std::string object_name);
        std::vector <GameObject*> getAll();
};

#endif



    


