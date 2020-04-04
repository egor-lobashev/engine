#include <string>
#include <map>
#include <vector>
#include "GameObject.h"
#include "GraphicsManager.h"
#include "DataStorage.h"


DataStorage::~DataStorage(){

    for (auto item : map_of_game_objects)
    {
        std::cout << item.second->id_in_data_storage << std::endl;
        if (item.second->dynamic)
            delete item.second;
        std::cout << "successfully" << std::endl << std::endl;
    }
};

bool DataStorage::addObject(std::string object_name , GameObject* obj){
    
    obj->id_in_data_storage = object_name;
    obj->storage = this;

    try
    { 
        map_of_game_objects[object_name] = obj;
        return true;
    }
    catch(...)
    {
        return false;
    }
}

bool DataStorage::deleteObject(std::string object_name){

    if(map_of_game_objects.count(object_name) == 1){
        delete map_of_game_objects[object_name];
        map_of_game_objects.erase(object_name);
        return true;
    }
    return false;
}

GameObject* DataStorage::getObject(std::string object_name){
    
    return map_of_game_objects[object_name];
}

std::vector <GameObject*> DataStorage:: getAll(){
            
    std::vector <GameObject*> output_vector;
    for(auto item : map_of_game_objects){
        output_vector.push_back(item.second);
    }

    return output_vector;
}