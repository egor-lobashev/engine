#ifndef __DATA_STORAGE__
#define __DATA_STORAGE__


#include <string>
#include <map>
#include <vector>
#include "GraphicsManager.h"
#include "API.h"

class qqqP::DataStorage{
    public:
        ~DataStorage();
        bool addObject(std::string object_name, qqq::GameObject* obj);
        bool deleteObject(std::string object_name);
        qqq::GameObject* getObject(std::string object_name);
        std::vector<qqq::GameObject*> getAll();
    private:
        std::map<std::string, qqq::GameObject*> map_of_game_objects;
};

#endif



    


