#include <SFML/Graphics.hpp>
#include <random>
#include "DataStorage.h"
#include "GraphicsManager.h"

class Controller: public Script
{
public:
    float speed = 1;

    void update(float dt)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            owner->position[0] += speed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            owner->position[0] -= speed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            owner->position[1] += speed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            owner->position[1] -= speed * dt;
        }
    }
};

class EnemyAI: public Script
{
    float speed = 1;

    void update(float dt)
    {
        DataStorage* data_storage = DataStorage::getInspance();

        GameObject* player = data_storage["player"];

        float rx = player->position[0] - owner->position[0];
        float ry = player->position[1] - owner->position[1];

        float distance = sqrt(rx*rx + ry*ry);

        rx /= distance;
        ry /= distance;

        owner->position[0] += rx * speed * dt;
        owner->position[1] += ry * speed * dt;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "demo game");
    DataStorage* data_storage = DataStorage::getInspance();
    GraphicsManager* graphics_manager = GraphicsManager::getInspance();
    ScriptManager* script_manager = ScriptManager::getInspance();
    sf::Clock clock;

    GameObject player;
    player.addComponent<Renderer>();
    player.getComponent<Renderer>()->loadTexture("image.png");
    player.getComponent<Renderer>()->createSprite();
    player.position[0] = 300;
    player.position[1] = 300;

    data_storage->addObject("player", &player);

    float timer = 20;
    int enemy_number = 0;

    sf::Event event;
    while (window.isOpen())
	{
        float dt = clock.getElapsedTime().asSeconds();
        clock.restart();

        timer -= dt;
        if (timer < 0)
        {
            timer = 20;

            GameObject* enemy = new GameObject;
            player.addComponent<Renderer>();
            player.getComponent<Renderer>()->loadTexture("enemy.png");
            player.getComponent<Renderer>()->createSprite();
            enemy->position[0] = rand()%250;
            enemy->position[1] = rand()%250;

            data_storage->addObject("enemy_" + std::to_string(enemy_number++), enemy);
        }

        script_manager->updateAll(dt);

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