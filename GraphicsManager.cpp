#include <SFML/Graphics.hpp>
#include <iostream>
#include "GraphicsManager.h"
#include "GameObject.h"


void qqqP::GraphicsManager::drawAll(sf::RenderWindow& window){

    for (qqq::Renderer* renderer: renderers){
        renderer->draw(window);
    }

    window.display();
}

bool qqqP::GraphicsManager::addRenderer(qqq::Component* new_renderer)
{
    try
    {
        renderers.push_back(static_cast<qqq::Renderer*>(new_renderer));
        return true;
    }
    catch(...)
    {
        return false;
    }
}

bool qqqP::GraphicsManager::removeRenderer(qqq::Component* removing_renderer)
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