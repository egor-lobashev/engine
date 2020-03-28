#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include <string>
#include <vector>
#include <iostream>
#include "Component.h"
#include "GraphicsManager.h"
#include "ScriptManager.h"
#include "PhysicsManager.h"

class GameObject
{
public:
    float position_of_game_object[2];
    std::vector < std::vector < float > > array_of_relative_x_y_coordinates_clockwise;
    std::string id_in_data_storage;  // it's not good
    std::vector<Script*> scripts;

    ~GameObject()
    {
        delete getComponent<Renderer>();
    }

    template <typename T>
    bool addComponent()
    {
        try
        {
            T* new_component = new T;
            components.push_back(new_component);
            components[components.size() - 1]->owner = this;
            
            if (typeid(T).name() == typeid(Renderer).name())
            {
                GraphicsManager* graphics_manager = GraphicsManager::getInstance();
                graphics_manager -> addRenderer(new_component);
            }
            else if (std::is_base_of<Script, T>())
            {
                ScriptManager* script_manager = ScriptManager::getInstance();
                script_manager -> addScript(new_component);
            }
            else if ( typeid(T).name() == typeid(Collider).name() )
            {
                PhysicsManager* physics_manager = PhysicsManager::getInstance();
                physics_manager -> addCollider(new_component);
            }

            return true;
        }
        catch(...)
        {
            return false;
        }
    }

    template <typename T>
    T* getComponent()
    {
	    std::string name = typeid(T).name();

        for (Component* comp: components)
        {
            if (comp->name == name)
                return static_cast<T*>(comp);
        }
        return nullptr;
    }

    template <typename T>
    bool removeComponent()
    {

        if (typeid(T).name() == typeid(Renderer).name())  
        {
            GraphicsManager* graphics_manager = GraphicsManager::getInstance();
            graphics_manager -> removeRenderer(getComponent<T>());
        }
        else if ( typeid(T).name() == typeid(Collider).name() )
        {
            PhysicsManager* physics_manager = PhysicsManager::getInstance();
            physics_manager -> removeCollider(getComponent<T>());
        }
        else if (std::is_base_of<Script, T>())
        {
            ScriptManager* script_manager = ScriptManager::getInstance();
            script_manager -> removeScript(getComponent<T>());
        }

        std::string name = typeid(T).name();

        for (int i = 0; i < components.size(); i++)
        {
            if (components[i]->name == name)
            {
                delete components[i];
                components.erase(components.begin() + i);
                return true;
            }
            return false;
        }

        
    }

    void setBodyPoint( std::vector < float > point )
    {
        array_of_relative_x_y_coordinates_clockwise.push_back( point );
    }

    int getQuantityOfBodyPoints()
    {
        return array_of_relative_x_y_coordinates_clockwise.size();
    }

    std::vector < float > getPointByIndex(int index){

        return array_of_relative_x_y_coordinates_clockwise[index];
    }

private:
    
    std::vector<Component*> components;
};

#endif