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
    sprite.setPosition( owner->position_of_game_object[0], owner->position_of_game_object[1] );
    window.draw(sprite);
}

void Renderer::loadTexture(std::string texturename) 
{
    texture.loadFromFile(texturename);
}

void Renderer::createSpriteAndSetSizeOfHitBox( float height , float width )
{
    sprite.setTexture(texture);
    size_of_object["height"] = height;
    size_of_object["width"] = width;
    
    for ( int i = 0 ; i < 2 ; ++i)
    {
        for( int j = 0 ; j < 2 ; ++j)
        {
            owner -> setBodyPoint( { width*j , height*i } );
        }

    }
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