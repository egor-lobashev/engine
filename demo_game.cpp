#include <SFML/Graphics.hpp>
#include <random>
#include "DataStorage.h"
#include "GraphicsManager.h"
#include "ScriptManager.h"

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
            owner->position[0] += speed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            owner->position[0] -= speed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            owner->position[1] += speed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            owner->position[1] -= speed * dt;
        }
    }
};

class Health: public Script
{
public:
    int health = 10;

    Health()
    {
        name = typeid(*this).name();
    }

    void update(float dt)
    {
        if (health <= 0)
        {
            DataStorage* data_storage = DataStorage::getInstance();

            data_storage->deleteObject(owner->id_in_data_storage);
        }
    }
};

class EnemyAI: public Script
{
public:
    float speed = 20;
    float cooldown = 0;

    EnemyAI()
    {
        name = typeid(*this).name();
    }

    void update(float dt)
    {
        DataStorage* data_storage = DataStorage::getInstance();

        GameObject* player = data_storage->getObject("player");

        float rx = player->position[0] - owner->position[0];
        float ry = player->position[1] - owner->position[1];

        float distance = sqrt(rx*rx + ry*ry);

        rx /= distance;
        ry /= distance;

        owner->position[0] += rx * speed * dt;
        owner->position[1] += ry * speed * dt;

        cooldown -= dt;
        if ((cooldown <= 0) and (distance <= 20))
        {
            cooldown = 5;
            player->getComponent<Health>()->health -= 1;
        }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "demo game");
    DataStorage* data_storage = DataStorage::getInstance();
    GraphicsManager* graphics_manager = GraphicsManager::getInstance();
    ScriptManager* script_manager = ScriptManager::getInstance();
    sf::Clock clock;

    GameObject player;
    player.addComponent<Renderer>();
    player.getComponent<Renderer>()->loadTexture("image.png");
    player.getComponent<Renderer>()->createSprite();
    player.position[0] = 300;
    player.position[1] = 300;

    player.addComponent<Controller>();

    player.addComponent<Health>();
    player.getComponent<Health>()->health = 10;

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
            enemy->addComponent<Renderer>();
            enemy->getComponent<Renderer>()->loadTexture("enemy.png");
            enemy->getComponent<Renderer>()->createSprite();
            enemy->position[0] = rand()%250;
            enemy->position[1] = rand()%250;

            enemy->addComponent<EnemyAI>();

            data_storage->addObject("enemy_" + std::to_string(enemy_number++), enemy);
        }

        script_manager->updateAll(dt);

        printf("hp: %d\n", data_storage->getObject("player")->getComponent<Health>()->health);
        if (data_storage->getObject("player") == nullptr)
        {
            window.close();
        }

        window.clear(sf::Color(255, 255, 255));
        graphics_manager->drawAll(window);

        while (window.pollEvent(event))
	    {
            if (event.type == sf::Event::Closed){
                window.close();
            }	   
	    }
    
    }

    delete data_storage;
    delete graphics_manager;
    delete script_manager;

    return 0;
}

// g++ demo_game.cpp Component.cpp DataStorage.cpp GraphicsManager.cpp ScriptManager.cpp -o demo_game -lsfml-graphics -lsfml-window -lsfml-system