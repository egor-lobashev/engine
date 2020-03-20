#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include <string>
#include <vector>
#include <iostream>
#include "Component.h"
#include "GraphicsManager.h"

class GameObject
{
public:
    float position[2];
    std::string id_in_data_storage;  // it's not good

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
            
            if (new_component->name == typeid(Renderer).name())
            {
                GraphicsManager* graphics_manager = GraphicsManager::getInspance();
                graphics_manager->addObject(id_in_data_storage, this);
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
            GraphicsManager* graphics_manager = GraphicsManager::getInspance();
            graphics_manager->deleteObject(id_in_data_storage);
        }
    }
private:
    std::vector<Component*> components;
};

#endif