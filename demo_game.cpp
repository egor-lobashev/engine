#include <SFML/Graphics.hpp>
#include <random>
#include "GameObject.h"

class Controller: public Script
{
public:
    float speed = 40;

    Controller()
    {
        name = typeid(*this).name();
    }

    void update()
    {
        Singleton* singleton = Singleton::getInstance();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            owner->position[0] += speed * singleton->dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            owner->position[0] -= speed * singleton->dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            owner->position[1] += speed * singleton->dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            owner->position[1] -= speed * singleton->dt;
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

    void update()
    {
        //printf("hp: %d\n", health);

        if (health <= 0)
        {
            //owner->storage->deleteObject(owner->id_in_data_storage);
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

    void update()
    {
        Singleton* singleton = Singleton::getInstance();
        GameObject* player = owner->storage->getObject("player");

        if (player == nullptr)
            return;
        
        float rx = player->position[0] - owner->position[0];
        float ry = player->position[1] - owner->position[1];

        float distance = sqrt(rx*rx + ry*ry);

        rx /= distance;
        ry /= distance;

        owner->position[0] += rx * speed * singleton->dt;
        owner->position[1] += ry * speed * singleton->dt;

        cooldown -= singleton->dt;
        if ((cooldown <= 0) and (distance <= 20))
        {
            cooldown = 5;
            player->getComponent<Health>()->health -= 1;
        }
    }
};

class EnemySpawner: public Script
{
public:
    float timer = 1;
    int enemy_number = 0;

    EnemySpawner()
    {
        name = typeid(*this).name();
    }

    void update()
    {
        Singleton* singleton = Singleton::getInstance();
        timer -= singleton->dt;
        
        if (timer < 0)
        {
            timer = 5;

            GameObject* enemy = new GameObject;
            enemy->dynamic = true;
            enemy->addComponent<Renderer>();
            enemy->getComponent<Renderer>()->loadTexture("enemy.png");
            enemy->getComponent<Renderer>()->createSprite();

            enemy->addComponent<Collider>();
            enemy->getComponent<Collider>()->setHitboxRectangle(60,60);

            enemy->position[0] = rand()%250;
            enemy->position[1] = rand()%250;

            enemy->addComponent<EnemyAI>();

            owner->storage->addObject("enemy_" + std::to_string(enemy_number++), enemy);
        }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "demo game");
    DataStorage data_storage;
    Singleton* singleton = Singleton::getInstance();
    sf::Clock clock;

    GameObject player;
    player.addComponent<Renderer>();
    player.getComponent<Renderer>()->loadTexture("image.png");
    player.getComponent<Renderer>()->createSprite();

    player.addComponent<Collider>();
    player.getComponent<Collider>()->setHitboxRectangle(90,60);

    player.position[0] = 300;
    player.position[1] = 300;

    player.addComponent<Controller>();

    player.addComponent<Health>();
    player.getComponent<Health>()->health = 1;

    data_storage.addObject("player", &player);
    
    GameObject enemy_spawner;
    enemy_spawner.addComponent<EnemySpawner>();

    data_storage.addObject("enemy_spawner", &enemy_spawner);

    sf::Event event;
    while (window.isOpen())
	{
        singleton->dt = clock.getElapsedTime().asSeconds();
        clock.restart();

        singleton->script_manager.updateAll();
        singleton->physics_manager.checkAllCollisions();

        //if (data_storage->getObject("player") == nullptr)
        if (player.getComponent<Health>()->health <= 0)
        {
            std::cout << "game over\n";
            window.close();
        }
        
        window.clear(sf::Color(255, 255, 255));
        singleton->graphics_manager.drawAll(window);

        while (window.pollEvent(event))
	    {
            if (event.type == sf::Event::Closed)
                window.close();
	    }
    }

    // delete data_storage;
    // delete graphics_manager;
    // delete script_manager;

    return 0;
}

// g++ demo_game.cpp Component.cpp DataStorage.cpp PhysicsManager.cpp GraphicsManager.cpp ScriptManager.cpp Singleton.cpp -o demo_game -lsfml-graphics -lsfml-window -lsfml-system