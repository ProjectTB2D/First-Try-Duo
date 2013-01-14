
#include "Actor.h"
#include "Core.h"
#include "global.h"

Actor::Actor()
{

}

Actor::Actor(const Entity& ent, int healthmax, float speedmax)
:   Entity(ent),
    _healthMax(healthmax),
    _speedMax(speedmax)
{
printf("Construction Actor \n");
    _health = _healthMax;
    _speed = _speedMax;
    _selectedItem = 0;


}

Actor::~Actor(){

    printf("destruction de Actor\n");

}

void Actor::update(){}

void Actor::render(){}

int Actor::getHealth() const{

    return _health;

}

int Actor::getHealthMax() const{

    return _healthMax;

}

float Actor::getSpeed() const{

    return _speed;

}

float Actor::getSpeedMax() const{

    return _speedMax;

}

//Item * Actor::getHand(){}

//Item ** Actor::getBelt(){}

    //setter

void Actor::setHealth(int h){

    _health = h;

}

void Actor::setHealthMax(int h){

    _healthMax = h;

}

void Actor::setSpeed(float s){

    _speed = s;

}

void Actor::setSpeedMax(float s){

    _speedMax = s;

}


void Actor::damage(int d){

    _health = _health - d;

    if(_health <= 0)
        _killed = true;

}

void fire(){}

void drop(){}

void rollItem(){}

void use(){}

void putItemToCrafter(){}







