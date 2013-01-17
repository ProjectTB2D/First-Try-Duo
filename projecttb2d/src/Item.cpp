
#include "global.h"
#include "Core.h"
#include "Entity.h"
#include "Item.h"

#define LIFETIME 50

Item::Item()
{


}

Item::Item(int a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d, Item_t type)
:   Entity(a,b,c,d),
    _it(type)
{



}

Item_t Item::getItemType() const{

    return _it;

}

void Item::setInfo(float angle, sf::Vector2f pos){

    _carrier_angle = angle;
    _carrier_pos = pos;

}

Item::~Item(){

    //printf("ITEM DELETED !!!!!!!!!!!!!!!!!\n");

}

////////////////////////////////RESSOURCE ////////////////////////////////////////:

Ressource::Ressource(){}

Ressource::Ressource(int a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d, Item_t it)
:Item(a, b, c, d, it)
{

}

Ressource::~Ressource()
{

}

////////////////////////////////// DROP ////////////////////////////////////////:

Drop::Drop(){}

Drop::Drop(int a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d, Item_t it, bool gen)
:   Entity(a,b,c,d),
    _it(it),
    _generated(gen)
{
     printf("id : %p, pos : %f , %f\n", this, getPos().x, getPos().y);
    _timer.restart();

}

void Drop::update(){

    if(!_generated && _timer.getElapsedTime().asSeconds() > LIFETIME)
        _killed = true;

}

void Drop::render(){

    //printf("pos : %f; %f\n", getPos().x, getPos().y);
    g_core->getApp()->draw(_spr);

}

Item_t Drop::getItemType() const{

    return _it;

}


