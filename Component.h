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
    void createSprite();
    sf::Sprite* getSprite();

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

/////////////////////////////////////////////////

class Script: public Component
{
public:
    Script();
    virtual void update() {}
};

/////////////////////////////////////////////////

class Collider: public Component
{   
    public:
        Collider();
        bool canThisObjBounce();
        void setBodyPoint( std::vector < float > point );
        int getQuantityOfBodyPoints();
        std::vector < float > getPointByIndex(int index);
        bool setHitboxRectangle(float height , float width);

    private:
        std::vector<std::vector<float>> hitbox_coordinates;
        bool this_object_can_bounce = false;
};

#endif