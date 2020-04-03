#include <SFML/Graphics.hpp>
#include <string>
#include "GameObject.h"
#include "Component.h"

////////////////////////////////////

qqq::Renderer::Renderer()
{
    name = typeid(*this).name();
}

void qqq::Renderer::draw(sf::RenderWindow& window)
{
    sprite.setPosition( owner->position[0], owner->position[1] );
    window.draw(sprite);
}

void qqq::Renderer::loadTexture(std::string texturename) 
{
    texture.loadFromFile(texturename);
}

void qqq::Renderer::createSprite()
{
    sprite.setTexture(texture);
}

sf::Sprite* qqq::Renderer::getSprite()
{
    return &sprite;
}

////////////////////////////////////

qqq::Script::Script(){

    this->name = typeid(qqq::Script).name();

}

////////////////////////////////////

qqq::Collider::Collider(){

    this->name = typeid(qqq::Collider).name();
}

bool qqq::Collider::canThisObjBounce(){
    
    return this_object_can_bounce;

}

void qqq::Collider::setBodyPoint( std::vector < float > point )
{
    hitbox_coordinates.push_back( point );
}

int qqq::Collider::getQuantityOfBodyPoints()
{
    return hitbox_coordinates.size();
}

std::vector<float> qqq::Collider::getPointByIndex(int index)
{
    return hitbox_coordinates[index];
}

bool qqq::Collider::setHitboxRectangle(float height, float width)
{
    for ( int i = 0 ; i < 2 ; ++i)
    {
        for( int j = 0 ; j < 2 ; ++j)
        {
            setBodyPoint( { width*j , height*i } );
        }
    }
    return true;
}