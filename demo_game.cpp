#include <SFML/Graphics.hpp>
#include <random>
#include "DataStorage.h"
#include "GraphicsManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "demo game");
    DataStorage data_storage;
    GraphicsManager* graphics_manager = GraphicsManager::getInspance();
    ScriptManager* script_manager = ScriptManager::getInspance();
    sf::Clock clock;

    GameObject player;
    player.addComponent<Renderer>();
    player.getComponent<Renderer>()->loadTexture("image.png");
    player.getComponent<Renderer>()->createSprite();
    player.position[0] = 300;
    player.position[1] = 300;


    data_storage.addObject("player", &player);

    sf::Event event;
    while (window.isOpen())
	{
        if (clock.getElapsedTime().asSeconds())
		{
            clock.restart();

            GameObject enemy;
            player.addComponent<Renderer>();
            player.getComponent<Renderer>()->loadTexture("enemy.png");
            player.getComponent<Renderer>()->createSprite();
            enemy.position[0] = rand()%250;
            enemy.position[1] = rand()%250;
        }

        script_manager->updateAll();

        window.clear(sf::Color(255, 255, 255));
        graphics_manager->drawAll(window);

        while (window.pollEvent(event))
	    {
            if (event.type == sf::Event::Closed){
                window.close();
            }	   
	    }
    
    }

    return 0;
}