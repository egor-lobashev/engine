#include <SFML/Graphics.hpp>
#include "Singleton.h"
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
        singleton->data_storage.updateAll();
        
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