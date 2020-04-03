#ifndef __GRAPHICS_MANAGER__
#define __GRAPHICS_MANAGER__


#include <SFML/Graphics.hpp>
#include <iostream>
#include "Component.h"

class GraphicsManager {
    public:
        void drawAll(sf::RenderWindow& window);
        bool addRenderer(Component* new_renderer);
        bool removeRenderer(Component* removing_renderer);
    private:
        std::vector<Renderer*> renderers;
};

#endif