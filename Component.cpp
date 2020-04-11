#include <SFML/Graphics.hpp>
#include <string>
#include "GameObject.h"
#include "Component.h"

////////////////////////////////////

void qqq::Renderer::draw(sf::RenderWindow& window)
{
    sprite.setPosition( owner->position[0], owner->position[1] );
    window.draw(sprite);
}

void qqq::Renderer::loadTexture(std::string texturename) 
{
    texture.loadFromFile(texturename);
}

std::string qqq::Renderer::getNameOfTexture()
{
    return name_of_texture;
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

bool qqq::Collider::canThisObjBounce(){
    
    return this_object_can_bounce;

}

void qqq::Collider::setBounceType( bool object_type )
{
    this_object_can_bounce = object_type;
}

void qqq::Collider::setBodyPointClockwise( std::vector < float > point )
{
    relative_hitbox_coordinates.push_back( point );
}

int qqq::Collider::getQuantityOfBodyPoints()
{
    return relative_hitbox_coordinates.size();
}

std::vector<float> qqq::Collider::getPointByIndex(int index)
{
    return relative_hitbox_coordinates[index];
}

bool qqq::Collider::setHitboxRectangle(float height, float width)
{
    setBodyPointClockwise( { width*0 , height*0 } );
    setBodyPointClockwise( { width*1 , height*0 } );
    setBodyPointClockwise( { width*1 , height*1 } );
    setBodyPointClockwise( { width*0 , height*1 } );
    return true;
}