#include <SFML/Graphics.hpp>
#include <random>
#include "GameObject.h"
#include "API.h"

class PrototypeOfFuncionIfCollide : public qqq::Script
{
    public:

        void ifCollision(qqq::GameObject* another)
        {   
            
            if( this -> owner -> collider)
            {

                double sin = -1;
                double cos = 0;

            
                if (this -> owner -> position[0] == another -> position[0])
                {
                    if (this -> owner -> position[1] < another -> position[1])
                    {
                        sin = 1;
                        cos = 0;
                    }
                    else 
                    {
                        sin = -1;
                        cos = 0;
                    }
                }
                else {
                    double k = (another -> position[1] - this -> owner -> position[1]) / (another -> position[0] - this -> owner -> position[0]);
                    sin = k / (sqrt(pow(k, 2) + 1));
                    cos = 1 / (sqrt(pow(k, 2) + 1));
                }

                // зададим через матрицу перехода свзять координат в разных СО

                float V_csi_before_1_obj = cos * this -> owner -> velocity_before_hitting[0] + sin * this -> owner -> velocity_before_hitting[1];
                float V_eta_before_1_obj = (-1) * sin * this -> owner -> velocity_before_hitting[0] + cos * this -> owner -> velocity_before_hitting[1];

                float V_csi_before_2_obj = cos * another -> velocity_before_hitting[0] + sin * another -> velocity_before_hitting[1];
                float V_eta_before_2_obj = (-1) * sin * another -> velocity_before_hitting[0] + cos * another -> velocity_before_hitting[1];

                float csi_coord_1_obj =  cos * this -> owner -> position[0] + sin * this -> owner -> position[1];
                float eta_coord_1_obj = (-1) * sin * this -> owner -> position[0] + cos * this -> owner -> position[1];

                float csi_coord_2_obj =  cos * another -> position[0] + sin * another -> position[1];
                float eta_coord_2_obj = (-1) * sin * another -> position[0] + cos * another -> position[1];
                // выразил скорости в новой СК , теперь поменяем нормальные составляющие и проверим, требуется ли в данном 
                // рассталкивать эти обьекты

                if (    csi_coord_2_obj > csi_coord_1_obj and V_csi_before_2_obj < 0 and V_csi_before_1_obj > 0 or
                        csi_coord_2_obj < csi_coord_1_obj and V_csi_before_2_obj > 0 and V_csi_before_1_obj < 0 or
                        csi_coord_2_obj > csi_coord_1_obj and V_csi_before_1_obj - V_csi_before_2_obj > 0       or
                        csi_coord_2_obj < csi_coord_1_obj and V_csi_before_1_obj - V_csi_before_2_obj < 0           )
                {

                    V_csi_before_1_obj = V_csi_before_2_obj;

                    // теперь переходим к старым координатам

                    double V_x_1_obj_after_hitting = cos * V_csi_before_1_obj - sin * V_eta_before_1_obj;
			        double V_y_1_obj_after_hitting = sin * V_csi_before_1_obj + cos * V_eta_before_1_obj;
                    
                    this -> owner -> velocity_after_hitting[0] = V_x_1_obj_after_hitting;
                    this -> owner -> velocity_after_hitting[1] = V_y_1_obj_after_hitting;

                }
            }
        }
};

class Controller: public qqq::Script
{
public:
    float speed = 100;

    void update()
    {
        qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
        float dt = qqq::relativeTime();

        owner -> velocity_before_hitting = {0,0};

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            owner -> position[0] += speed*dt;
            owner -> velocity_before_hitting[0] = speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            owner -> position[0] -= speed*dt;
            owner -> velocity_before_hitting[0] = -speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            owner -> position[1] += speed*dt;
            owner -> velocity_before_hitting[1] = speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            owner -> position[1] -= speed*dt;
            owner -> velocity_before_hitting[1] = -speed;
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
            //printf("GAME OVER\n\n\n");
        }
    }
};

class EnemyAI: public qqq::Script
{
public:
    float speed = 0;
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
        
        owner -> velocity_before_hitting[0] = rx * speed;
        owner -> velocity_before_hitting[1] = ry * speed;
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

            enemy -> addComponent<PrototypeOfFuncionIfCollide>();

            enemy->position[0] = rand()%250;
            enemy->position[1] = rand()%250;

            enemy->addComponent<EnemyAI>();

            enemy->record("enemy_" + std::to_string(enemy_number++));
        }
    }
};

int EnemySpawner::quantity_of_enemies = 0;

int main()
{
    qqq::GameObject player;
    player.collider = false;
    player.addComponent<qqq::Renderer>();
    player.getComponent<qqq::Renderer>()->loadTexture("image.png");
    player.getComponent<qqq::Renderer>()->createSprite();

    player.addComponent<qqq::Collider>();
    player.getComponent<qqq::Collider>()->setHitboxRectangle(90,60);

    player.addComponent<PrototypeOfFuncionIfCollide>();

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