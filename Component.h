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

    void draw(sf::RenderWindow& window, int x, int y)
    {
        sprite.setPosition(x, y);
        window.draw(sprite);
        window.display();
    }

    void loadTexture(std::string texturename) 
    {
        texture.loadFromFile(texturename);
    }

    void createSprite()
    {
        sprite.setTexture(texture);
    }

    sf::Sprite* getSprite()
    {
        return &sprite;
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif