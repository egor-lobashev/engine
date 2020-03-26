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

    for (Renderer* renderer: renderers){
        renderer->draw(window);
    }

    window.display();
}

bool GraphicsManager::addRenderer(Component* new_renderer)
{
    try
    {
        renderers.push_back(static_cast<Renderer*>(new_renderer));
        return true;
    }
    catch(...)
    {
        return false;
    }
}

bool GraphicsManager::removeRenderer(Component* removing_renderer)
{
    for (int i = 0; i < renderers.size(); i++)
    {
        if (renderers[i] == removing_renderer)
        {
            renderers.erase(renderers.begin() + i);
            return true;
        }
    }
    return false;
}

GraphicsManager* GraphicsManager::instance = nullptr;