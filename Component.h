#ifndef __COMPONENT__
#define __COMPONENT__

#include <SFML/Graphics.hpp>
#include <string>

class Component
{
public:
    std::string name;
};

class TestType: public Component
{
public:
    TestType()
    {
        name = typeid(*this).name();
    }
    std::string test_string = "it works :)";
};

class Renderer: public Component
{
public:
    void draw() {}
    void loadTexture(std::string) {}
    void makeSprite() {}
    sf::Sprite* getSprite() {}
private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif