#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "API.h"
#include "GameObject.h"
#include <fstream>


void settingHitboxPointsWithMouse(sf::RenderWindow& window , std::string name_of_pictures_folder)
{
    qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
    std::ifstream pictures_folder;
    pictures_folder.open("name_of_pictures_folder");
   

}