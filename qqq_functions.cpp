#include <SFML/Graphics.hpp>
#include <cmath>
#include "Singleton.h"
#include "GameObject.h"
#include "API.h"


void qqq::runGame(int window_width, int window_height, std::string window_name)
{
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), window_name);

    qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
    sf::Event event;
    while (window.isOpen())
    {
        singleton->dt = singleton->clock.getElapsedTime().asSeconds();
        singleton->clock.restart();

        singleton->script_manager.updateAll();
        singleton->physics_manager.checkAllCollisions();
        
        window.clear(sf::Color(255, 255, 255));
        singleton->graphics_manager.drawAll(window);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    delete singleton;
}

qqq::GameObject* qqq::getObject(std::string name)
{
    qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
    return singleton->data_storage.getObject(name);
}

float qqq::absoluteTime()
{
    qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
    return singleton->clock.getElapsedTime().asSeconds();
}

float qqq::relativeTime()
{
    qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
    return singleton->dt;
}

void qqq::BallReflection::update()  // move this function to PhysicsManager or somwhere else
{
    float dt = qqq::relativeTime();
    owner -> changeCoordinatesBy({ owner->velocity[0] * dt , owner->velocity[1] * dt });
}

void qqq::BallReflection::ifCollision(qqq::GameObject* another)
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
    float V_csi_before_1_obj = cos * this -> owner -> velocity[0] + sin * this -> owner -> velocity[1];
    float V_eta_before_1_obj = (-1) * sin * this -> owner -> velocity[0] + cos * this -> owner -> velocity[1];

    float V_csi_before_2_obj = cos * another -> velocity[0] + sin * another -> velocity[1];
    float V_eta_before_2_obj = (-1) * sin * another -> velocity[0] + cos * another -> velocity[1];

    float csi_coord_1_obj =  cos * this -> owner -> position[0] + sin * this -> owner -> position[1];
    float eta_coord_1_obj = (-1) * sin * this -> owner -> position[0] + cos * this -> owner -> position[1];

    float csi_coord_2_obj =  cos * another -> position[0] + sin * another -> position[1];
    float eta_coord_2_obj = (-1) * sin * another -> position[0] + cos * another -> position[1];
    // выразил скорости в новой СК , теперь поменяем нормальные составляющие и проверим, требуется ли в данном 
    // рассталкивать эти обьекты

    if (    (csi_coord_2_obj > csi_coord_1_obj and V_csi_before_2_obj <= 0 and V_csi_before_1_obj >= 0) or
            (csi_coord_2_obj < csi_coord_1_obj and V_csi_before_2_obj >= 0 and V_csi_before_1_obj <= 0) or
            (csi_coord_2_obj > csi_coord_1_obj and V_csi_before_1_obj - V_csi_before_2_obj > 0)       or
            (csi_coord_2_obj < csi_coord_1_obj and V_csi_before_1_obj - V_csi_before_2_obj < 0)           )
    {
        float tmp = V_csi_before_1_obj;
        V_csi_before_1_obj = V_csi_before_2_obj;
        V_csi_before_2_obj = tmp;

        // теперь переходим к старым координатам

        double V_x_1_obj_after_hitting = cos * V_csi_before_1_obj - sin * V_eta_before_1_obj;
        double V_y_1_obj_after_hitting = sin * V_csi_before_1_obj + cos * V_eta_before_1_obj;
        double V_x_2_obj_after_hitting = cos * V_csi_before_2_obj - sin * V_eta_before_2_obj;
        double V_y_2_obj_after_hitting = sin * V_csi_before_2_obj + cos * V_eta_before_2_obj;
        
        this -> owner -> velocity[0] = V_x_1_obj_after_hitting;
        this -> owner -> velocity[1] = V_y_1_obj_after_hitting;

        another->velocity[0] = V_x_2_obj_after_hitting;
        another->velocity[1] = V_y_2_obj_after_hitting;
    }
}