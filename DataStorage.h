#ifndef __DATA_STORAGE__
#define __DATA_STORAGE__


#include <string>
#include <map>
#include <vector>
#include "GameObject.h"

class DataStorage{
    public:

        //  ~DataStorage(){

        //    for(auto item : map_of_game_objects){
        //        delete map_of_game_objects[item.first];
        //    }

        //}

        bool addObject(std::string object_name , GameObject* obj){

            if(map_of_game_objects[object_name] = obj){
                return true;
            }

            return false;
        }
        bool deleteObject(std::string object_name){
            if(map_of_game_objects.count(object_name) == 1){

                delete map_of_game_objects[object_name];
                map_of_game_objects.erase(object_name);
                return true;
            }
            return false;
        }
        GameObject* getObject(std::string object_name){
            return map_of_game_objects[object_name];
        }

        std::vector <GameObject*> getAll(){
            
            std::vector <GameObject*> output_vector;
            for(auto item : map_of_game_objects){
                output_vector.push_back(item.second);
            }

            return output_vector;
        }


    private:

        std::map<std::string,GameObject*> map_of_game_objects;

};

#endif
