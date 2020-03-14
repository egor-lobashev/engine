#include <SFML/Graphics.hpp>
#include "DataStorage.h"
#include "GraphicsManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "Some game");
    DataStorage data_storage;
    GraphicsManager graphics_manager;

    GameObject player;
    player.addComponent<Renderer>();
    player.getComponent<Renderer>()->loadTexture("image.png");
    player.getComponent<Renderer>()->createSprite();
    player.position[0] = 400;
    player.position[1] = 20;

    data_storage.addObject("player", &player);

    window.clear(sf::Color(0,0,0));
    graphics_manager.drawAll(window, data_storage.getAll());

    sf::Event event;
    while (window.isOpen())
	{
        while (window.pollEvent(event))
	    {
            if (event.type == sf::Event::Closed){
                window.close();
            }	   
	    }
    
    }

    return 0;
}