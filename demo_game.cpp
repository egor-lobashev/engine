#include <SFML/Graphics.hpp>
#include <random>
#include "GameObject.h"
#include "API.h"

class Controller: public qqq::Script
{
public:
    float speed = 40;

    void update()
    {
        qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
        float dt = qqq::relativeTime();

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

class Health: public qqq::Script
{
public:
    int health = 10;

    void update()
    {
        //printf("hp: %d\n", health);

        if (health <= 0)
        {
            //owner->storage->deleteObject(owner->id_in_data_storage);
        }
    }
};

class EnemyAI: public qqq::Script
{
public:
    float speed = 20;
    float cooldown = 0;

    void update()
    {
        qqq::GameObject* player = qqq::getObject("player");
        float dt = qqq::relativeTime();

        if (player == nullptr)
            return;
        
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

class EnemySpawner: public qqq::Script
{
public:
    float timer = 1;
    int enemy_number = 0;

    void update()
    {
        timer -= qqq::relativeTime();
        
        if (timer < 0)
        {
            timer = 5;

            qqq::GameObject* enemy = new qqq::GameObject;
            enemy->dynamic = true;
            enemy->addComponent<qqq::Renderer>();
            enemy->getComponent<qqq::Renderer>()->loadTexture("enemy.png");
            enemy->getComponent<qqq::Renderer>()->createSprite();

            enemy->addComponent<qqq::Collider>();
            enemy->getComponent<qqq::Collider>()->setHitboxRectangle(60,60);

            enemy->position[0] = rand()%250;
            enemy->position[1] = rand()%250;

            enemy->addComponent<EnemyAI>();

            enemy->record("enemy_" + std::to_string(enemy_number++));
        }
    }
};

int main()
{
    qqq::GameObject player;
    player.addComponent<qqq::Renderer>();
    player.getComponent<qqq::Renderer>()->loadTexture("image.png");
    player.getComponent<qqq::Renderer>()->createSprite();

    player.addComponent<qqq::Collider>();
    player.getComponent<qqq::Collider>()->setHitboxRectangle(90,60);

    player.position[0] = 300;
    player.position[1] = 300;

    player.addComponent<Controller>();

    player.addComponent<Health>();
    player.getComponent<Health>()->health = 1;

    player.record("player");
    

    qqq::GameObject enemy_spawner;
    enemy_spawner.addComponent<EnemySpawner>();

    enemy_spawner.record("enemy_spawner");

    qqq::runGame(600, 600, "Demo game");

    return 0;
}

// g++ demo_game.cpp Component.cpp DataStorage.cpp PhysicsManager.cpp GraphicsManager.cpp ScriptManager.cpp Singleton.cpp qqq_functions.cpp -o demo_game -lsfml-graphics -lsfml-window -lsfml-system