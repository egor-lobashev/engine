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

void qqq::Collider::setBodyPointClockwise( std::vector < float > point )
{
    relative_hitbox_coordinates.push_back( point );
    absolute_hitbox_coordinates.push_back({ point[0] + this -> owner -> position[0] , point[1] + this -> owner -> position[1] });
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

std::vector< std::vector<float> > qqq::Collider::getAbsoluteHitboxCoordinates()
{
    return absolute_hitbox_coordinates;
}

std::vector< std::vector<float> > qqq::Collider::getRelativeHitboxCoordinates()
{
    return relative_hitbox_coordinates;
}

void qqq::Collider::setAbsoluteHitboxCoordinates(std::vector< std::vector<float> > absolute_hitbox_coordinates)
{
    this->absolute_hitbox_coordinates = absolute_hitbox_coordinates;
}