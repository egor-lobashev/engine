#include <SFML/Graphics.hpp>
#include <iostream>
#include "GraphicsManager.h"
#include "GameObject.h"


GraphicsManager* GraphicsManager::getInstance()
{
    if (!instance)
        instance = new GraphicsManager();
    return instance;
}

void GraphicsManager::drawAll(sf::RenderWindow& window){

    for (auto& object : drawable_objects){
        object.second->getComponent<Renderer>()->draw(window);
    }

    window.display();
}

bool GraphicsManager::addObject(std::string object_name , GameObject* obj)
{
    if(drawable_objects[object_name] = obj)
    {
        return true;
    }

    return false;
}

bool GraphicsManager::deleteObject(std::string object_name)
{
    if(drawable_objects.count(object_name) == 1){

        delete drawable_objects[object_name];
        drawable_objects.erase(object_name);
        return true;
    }
    return false;
}

GraphicsManager* GraphicsManager::instance = nullptr;