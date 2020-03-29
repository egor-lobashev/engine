#include <SFML/Graphics.hpp>
#include <string>
#include "GameObject.h"
#include "Component.h"

////////////////////////////////////

Renderer::Renderer()
{
    name = typeid(*this).name();
}

void Renderer::draw(sf::RenderWindow& window)
{
    sprite.setPosition( owner->position[0], owner->position[1] );
    window.draw(sprite);
}

void Renderer::loadTexture(std::string texturename) 
{
    texture.loadFromFile(texturename);
}

void Renderer::createSprite()
{
    sprite.setTexture(texture);
}

sf::Sprite* Renderer::getSprite()
{
    return &sprite;
}

////////////////////////////////////

Script::Script(){

    this->name = typeid(Script).name();

}

////////////////////////////////////

Collider::Collider(){

    this->name = typeid(Collider).name();
}

bool Collider::canThisObjBounce(){
    
    return this_object_can_bounce;

}

void Collider::setBodyPoint( std::vector < float > point )
{
    hitbox_coordinates.push_back( point );
}

int Collider::getQuantityOfBodyPoints()
{
    return hitbox_coordinates.size();
}

std::vector<float> Collider::getPointByIndex(int index)
{
    return hitbox_coordinates[index];
}

bool Collider::setHitboxRectangle(float height, float width)
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