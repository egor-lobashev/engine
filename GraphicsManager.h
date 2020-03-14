#ifndef __GRAPHICS_MANAGER__
#define __GRAPHICS_MANAGER__


#include <SFML/Graphics.hpp>
#include <iostream>

class GraphicsManager {
    public:
        static GraphicsManager* getInspance()
        {
            if (!instance)
                instance = new GraphicsManager();
            return instance;
        }
        
        void drawAll(sf::RenderWindow& window){

            for (GameObject* object : drawable_objects){
                if( object->getComponent<Renderer>() != nullptr ){
                    object->getComponent<Renderer>()->draw(window);

                }
            }

            window.display();
        }

    private:
        GraphicsManager() {}
        static GraphicsManager* instance;
        std::vector<GameObject*> drawable_objects;
};

GraphicsManager* GraphicsManager::instance = nullptr;

#endif