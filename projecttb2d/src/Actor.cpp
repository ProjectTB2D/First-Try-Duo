
#include "Actor.h"
#include "Core.h"
#include "global.h"
#include "World.h"
#include "Weapon.h"
#include <math.h>

Actor::Actor()
{

}

Actor::Actor(int a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d, int healthmax, float speedmax)
:   Entity(a,b,c,d),
    _healthMax(healthmax),
    _speedMax(speedmax),
    _hand(NULL)
{
printf("Construction Actor \n");
    _health = _healthMax;
    _speed = _speedMax;
    _selectedItem = 0;

   _hand = new Weapon(3, getPos(), sf::Vector2f(0,0), sf::Vector2f(30,10),
                        IT_PLASMA);
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

void Actor::fire(){}

void Actor::drop(){

    printf("drop d'une arme\n");

    if(_hand != NULL){


        sf::Vector2f point(getPos().x - 45*cos(_angle),getPos().y - 45*sin(_angle));

        g_core->getWorld()->addDrop(point, _hand->getItemType());
        delete _hand;
        _hand = NULL;

    }

}

void Actor::rollItem(){}

void Actor::use(){


    sf::Vector2f point;

    point.x = getPos().x - 45*cos(_angle);
    point.y = getPos().y - 45*sin(_angle);

    float a[4] = {  point.x - 10,
                    point.y - 10,
                    point.x + 10,
                    point.y + 10};

    for(unsigned int i = 0; i < g_core->getWorld()->getDrop()->size(); i++){

        //Drop* d = NULL;
        //d = &(*g_core->getWorld()->getDrop())[i];
        //printf("[1] d = %p | g_core = %p \n" ,d, &(*g_core->getWorld()->getDrop())[i]);

        float b[4] = {  (*g_core->getWorld()->getDrop())[i].getPos().x - (*g_core->getWorld()->getDrop())[i].getFrameW()/2,
                        (*g_core->getWorld()->getDrop())[i].getPos().y - (*g_core->getWorld()->getDrop())[i].getFrameH()/2,
                        (*g_core->getWorld()->getDrop())[i].getPos().x + (*g_core->getWorld()->getDrop())[i].getFrameW()/2,
                        (*g_core->getWorld()->getDrop())[i].getPos().y + (*g_core->getWorld()->getDrop())[i].getFrameH()/2};

        //printf("[2] d = %p | g_core = %p \n" ,d, &(*g_core->getWorld()->getDrop())[i]);

        if(g_core->bounding_box(a, b, true)){

            //printf("[3] d =%p | g_core = %p \n" ,d, &(*g_core->getWorld()->getDrop())[i]);

            setHandItem(g_core->getWorld()->getItemFromIT((*g_core->getWorld()->getDrop())[i].getItemType()));

            //printf("[4] d = %p | g_core = %p \n" ,d, &(*g_core->getWorld()->getDrop())[i]);

            (*g_core->getWorld()->getDrop())[i].kill();
            break;

        }


}

}

void Actor::putItemToCrafter(){}


//////////////////////////////////// PROTECTED //////////////////////////////////////

void Actor::setHandItem(Item * it){

    if(!it) return;

    if(!_hand){
        _hand = it;
    }
    else
    if(_hand){
        drop();
        _hand = it;
    }

}






