#ifndef __COMPONENT__
#define __COMPONENT__

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class GameObject;

class Component
{
public:
    std::string name;
    GameObject* owner;
};

/////////////////////////////////////////////////

class Renderer: public Component
{
public:
    Renderer();
    void draw(sf::RenderWindow& window);
    void loadTexture(std::string texturename);
    void createSpriteAndSetSizeOfHitBox( float height , float width );
    sf::Sprite* getSprite();

private:
    std::map < std::string , float > size_of_object;
    sf::Texture texture;
    sf::Sprite sprite;
};

/////////////////////////////////////////////////

class Script: public Component
{
public:
    Script();
    virtual void update(float dt) {}
};

/////////////////////////////////////////////////

class Collider: public Component
{   
    public:
        Collider();
        bool canThisObjBounce();

    private:

        bool this_object_can_bounce = false;
};

#endif