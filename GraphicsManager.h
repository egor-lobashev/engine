#ifndef __GRAPHICS_MANAGER__
#define __GRAPHICS_MANAGER__


#include <SFML/Graphics.hpp>

class GraphicsManager {
    public:
        void DrawAll(sf::RenderWindow& window , std::vector <GameObject*> all_objects){

            for (auto object : all_objects){
                if( object -> getComponent<Renderer>() != nullptr ){

                    window.draw( *( object -> getComponent<Renderer>() -> getSprite() )  );

                }
            }

            window.display();
        }

    private:
};

#endif