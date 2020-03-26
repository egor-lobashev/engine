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

Collider::Collider(bool can_bounce){

    this->name = typeid(Collider).name();
    this -> this_object_can_bounce = can_bounce;

}

bool Collider::canThisObjBounce(){
    
    return this_object_can_bounce;

}