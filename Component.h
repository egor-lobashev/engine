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
    int x = 0;
    int y = 0;

    void draw(sf::RenderWindow& window)
    {
        sprite.setPosition(x, y);
        window.draw(sprite);
    }

    void loadTexture(std::string texturename) 
    {
        if (!texture.loadFromFile(texturename))
            return -1;
    }

    void createSprite()
    {
        sprite.setTexture(texture);
    }

    sf::Sprite* getSprite()
    {
        return sf::Sprite* result = &sprite;
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif