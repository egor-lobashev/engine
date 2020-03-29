#include <SFML/Graphics.hpp>
#include "DataStorage.h"
#include "GraphicsManager.h"
#include "ScriptManager.h"
#include "PhysicsManager.h"
#include <iostream>

class Controller: public Script
{
public:
    float speed = 40;

    Controller()
    {
        name = typeid(*this).name();
    }

    void update(float dt)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            owner->position_of_game_object[0] += speed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            owner->position_of_game_object[0] -= speed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            owner->position_of_game_object[1] += speed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            owner->position_of_game_object[1] -= speed * dt;
        }
    }
};

int main(){
    std::cout << "i work";
    sf::RenderWindow window(sf::VideoMode(600, 600), "demo game");
    
    DataStorage* data_storage = DataStorage::getInstance();
    GraphicsManager* graphics_manager = GraphicsManager::getInstance();
    ScriptManager* script_manager = ScriptManager::getInstance();
    PhysicsManager* physics_manager = PhysicsManager::getInstance();
    sf::Clock clock;
    
    GameObject player;
    player.addComponent<Controller>();
    player.addComponent<Collider>();
    player.addComponent<Renderer>();
    player.getComponent<Renderer>()->loadTexture("image.png");
    player.getComponent<Renderer>()->createSpriteAndSetSizeOfHitBox(90,60);
    player.position_of_game_object[0] = 300;
    player.position_of_game_object[1] = 300;
    data_storage->addObject("player",&player);

    GameObject* enemy;
    enemy->addComponent<Renderer>();
    enemy->getComponent<Renderer>()->loadTexture("enemy.png");
    enemy->getComponent<Renderer>()->createSpriteAndSetSizeOfHitBox(60,60);
    enemy->position_of_game_object[0] = rand()%250;
    enemy->position_of_game_object[1] = rand()%250;
    data_storage->addObject("enemy",enemy);
    

    sf::Event event;
    while (window.isOpen())
	{
        float dt = clock.getElapsedTime().asSeconds();
        clock.restart();
        
        script_manager->updateAll(dt);

        
        window.clear(sf::Color(255, 255, 255));
        graphics_manager->drawAll(window);

        while (window.pollEvent(event))
	    {
            if (event.type == sf::Event::Closed)
                window.close();
	    }

    
    }

    delete data_storage;
    delete graphics_manager;
    delete script_manager;

    return 0;
}