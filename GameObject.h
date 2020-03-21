#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include <string>
#include <vector>
#include <iostream>
#include "Component.h"
#include "GraphicsManager.h"
#include "ScriptManager.h"

class GameObject
{
public:
    float position[2];
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
                graphics_manager->addObject(id_in_data_storage, this);
            }
            else if (std::is_base_of<Script, T>())
            {
                ScriptManager* script_manager = ScriptManager::getInstance();
                script_manager->addObject(new_component);
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

        if (typeid(T).name() == typeid(Renderer).name())
        {
            GraphicsManager* graphics_manager = GraphicsManager::getInstance();
            graphics_manager->deleteObject(id_in_data_storage);
        }

        else if (std::is_base_of<Script, T>())
        {
            // must be done
        }
    }
private:
    std::vector<Component*> components;
};

#endif