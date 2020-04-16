#include <SFML/Graphics.hpp>
#include <random>
#include "GameObject.h"
#include "API.h"


class Resistance: public qqq::Script
{
public:
    void update()
    {
        float dt = sqrt(2);//qqq::relativeTime();

        float resistance_of_field = 0.05;

        for ( int i = 0 ; i < 2 ; ++i)
        {
            if( owner->velocity[i] > 0 and owner->velocity[i] - resistance_of_field > 0  )
            {
                owner->velocity[i] -= resistance_of_field;
            }
            else if( owner->velocity[i] < 0 and owner->velocity[i] + resistance_of_field < 0 )
            {
                owner->velocity[i] += resistance_of_field;
            }
            else
            {
                owner->velocity[i] = 0;
            }
        }
    }
};

class Controller: public qqq::Script
{
public:
    float a = 100;

    void update()
    {
        float dt = qqq::relativeTime();
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            owner -> velocity[0] += a*dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            owner -> velocity[0] -= a*dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            owner -> velocity[1] += a*dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            owner -> velocity[1] -= a*dt;
        }

        owner -> changeCoordinatesBy({ owner->velocity[0] * dt , owner->velocity[1] * dt });
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
            //printf("GAME OVER\n\n\n");
        }
    }
};

class EnemyAI: public qqq::Script
{
public:
    float speed = 100;
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
        
        owner -> velocity[0] = rx * speed;
        owner -> velocity[1] = ry * speed;
        owner -> changeCoordinatesBy({ rx * speed * dt , ry * speed * dt });

        cooldown -= dt;
    }

    void ifCollision(qqq::GameObject* another)
    {   
    
        // if ((another->id_in_data_storage == "player") and (cooldown <= 0))
        // {
        //     cooldown = 5;
        //     another->getComponent<Health>()->health -= 1;
            
        // }
    }
};

class EnemySpawner: public qqq::Script
{
public:
    float timer = 1;
    int enemy_number = 0;

    static int quantity_of_enemies ;

    void update()
    {
        timer -= qqq::relativeTime();
        
        if (timer < 0 and quantity_of_enemies == 0)
        {   
            quantity_of_enemies ++;

            timer = 5;

            qqq::GameObject* enemy = new qqq::GameObject;
            enemy->dynamic = true;
            enemy->addComponent<qqq::Renderer>();
            enemy->getComponent<qqq::Renderer>()->loadTexture("enemy.png");
            enemy->getComponent<qqq::Renderer>()->createSprite();

            enemy->addComponent<qqq::Collider>();
            enemy->getComponent<qqq::Collider>()->setHitboxRectangle(60,60);

            enemy -> addComponent<qqq::BallReflection>();

            enemy -> addComponent<Resistance>();
            
            enemy->position[0] = rand()%250;
            enemy->position[1] = rand()%250;

            //enemy->addComponent<EnemyAI>();

            enemy->record("enemy_" + std::to_string(enemy_number++));
        }
    }
};

int EnemySpawner::quantity_of_enemies = 0;

int main()
{
    qqq::GameObject player;
    player.addComponent<qqq::Renderer>();
    player.getComponent<qqq::Renderer>()->loadTexture("image.png");
    player.getComponent<qqq::Renderer>()->createSprite();

    player.addComponent<qqq::Collider>();
    player.getComponent<qqq::Collider>()->setHitboxRectangle(90,60);

    player.addComponent<qqq::BallReflection>();

    player.addComponent<Resistance>();

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