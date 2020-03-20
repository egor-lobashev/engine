#ifndef __GRAPHICS_MANAGER__
#define __GRAPHICS_MANAGER__


#include <SFML/Graphics.hpp>
#include <iostream>

class GameObject;

class GraphicsManager {
    public:
        static GraphicsManager* getInstance();
        void drawAll(sf::RenderWindow& window);
        bool addObject(std::string object_name , GameObject* obj);
        bool deleteObject(std::string object_name);
    private:
        GraphicsManager() {}
        static GraphicsManager* instance;
        std::map<std::string,GameObject*> drawable_objects;
};

#endif