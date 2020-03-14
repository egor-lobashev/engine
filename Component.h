#ifndef __COMPONENT__
#define __COMPONENT__

#include <SFML/Graphics.hpp>
#include <string>

class GameObject;

class Component
{
public:
    std::string name;
    GameObject* owner;
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
    Renderer()
    {
        name = typeid(*this).name();
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }

    /*
    std::vector getSpriteposition()
    {
        return sprite.getPosition();
    }
    */

    void loadTexture(std::string texturename) 
    {
        texture.loadFromFile(texturename);
    }

    void createSprite(int x, int y)
    {
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
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