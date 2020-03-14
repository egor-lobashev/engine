#include <string>
#include <map>
#include <vector>
#include "GameObject.h"

class DataStorage{
    public:

        bool addObject(std::string object_name, GameObject& object){

            objects[object_name] = object;
            return true;
        }
        bool deleteObject(std::string object_name){
            if(objects.erase(object_name)){
                return true;
            }

            return false;
        }
        GameObject& getObject(std::string object_name){
            return objects[object_name];
        }

        std::vector <GameObject*> getAll(){
            
            std::vector <GameObject*> output_vector;
            for(auto item : objects){
                output_vector.push_back(&item.second);
            }
            return output_vector;

        }


    private:

    std::map<std::string,GameObject> objects;

};