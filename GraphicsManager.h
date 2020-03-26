#ifndef __GRAPHICS_MANAGER__
#define __GRAPHICS_MANAGER__


#include <SFML/Graphics.hpp>
#include <iostream>
#include "Component.h"

class GameObject;

class GraphicsManager {
    public:
        static GraphicsManager* getInstance();
        void drawAll(sf::RenderWindow& window);
        bool addRenderer(Component* new_renderer);
        bool removeRenderer(Component* removing_renderer);
    private:
        GraphicsManager() {}
        static GraphicsManager* instance;
        std::vector<Renderer*> renderers;
};
#endif