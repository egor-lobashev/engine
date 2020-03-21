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

class Renderer: public Component
{
public:
    Renderer();
    void draw(sf::RenderWindow& window);
    void loadTexture(std::string texturename);
    void createSprite();
    sf::Sprite* getSprite();

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

class Script: public Component
{
public:
    Script()
    {
        name = typeid(*this).name();
    }
    virtual void update(float dt);
};

#endif