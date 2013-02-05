
#include "global.h"
#include "Core.h"
#include "Entity.h"
#include "Item.h"
#include <math.h>
#define PI 3.14159265359

#define LIFETIME 50

Item::Item()
{


}

Item::Item(int a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d, Item_t type, Actor* owner)
:   Entity(a,b,c,d),
    _it(type),
    _owner(owner)
{



}

Item_t Item::getItemType() const{

    return _it;

}

void Item::setInfo(float angle, sf::Vector2f pos, Actor* own){

    _carrier_angle = angle;
    _carrier_pos = pos;
    _owner = own;

}

void Item::setOwner(Actor* o){

    _owner = o;

}

Actor* Item::getOwner(){

    return _owner;

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

void Ressource::update(){

    float ang = _carrier_angle + 0.58539;

    _spr.setPosition(_carrier_pos.x - 30*cos(ang), _carrier_pos.y - 30*sin(ang));
    _spr.setRotation(_carrier_angle);
}

void Ressource::render(){

    _spr.setRotation(_carrier_angle * 180 / PI);
    g_core->getApp()->draw(_spr);

}

void Ressource::use(){


}

////////////////////////////////// DROP ////////////////////////////////////////:

Drop::Drop(){}

Drop::Drop(int a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d, Item_t it, bool gen)
:   Entity(a,b,c,d),
    _it(it),
    _generated(gen)
{
     //printf("id : %p, pos : %f , %f\n", this, getPos().x, getPos().y);
    _timer.restart();

}

Drop::~Drop(){

    printf("drop deleted\n");

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

bool Drop::getGenerated() const{

    return _generated;

}
