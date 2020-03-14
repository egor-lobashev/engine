#ifndef __GRAPHICS_MANAGER__
#define __GRAPHICS_MANAGER__


#include <SFML/Graphics.hpp>
#include <iostream>

class GraphicsManager {
    public:
        void drawAll(sf::RenderWindow& window , std::vector <GameObject*> all_objects){

            for (GameObject* object : all_objects){
                if( object->getComponent<Renderer>() != nullptr ){
                    std::cout << "doofwelp\n";
                    object->getComponent<Renderer>()->draw(window);

                }
            }

            window.display();
        }

    private:
};

#endif