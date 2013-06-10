
#include "Actor.h"
#include "Core.h"
#include "global.h"
#include "World.h"
#include "Weapon.h"
#include <math.h>
#define PI 3.14159265359

Actor::Actor()
{

}

Actor::Actor(int a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d, int healthmax, float speedmax, team* tm)
:   Entity(a,b,c,d),
    _healthMax(healthmax),
    _speedMax(speedmax),
    _hand(NULL),
    _attacked(false),
    _team(tm),
    _colorRed(0),
    _colorGreen(255)
{
printf("Construction Actor : %p\n", this);
    _health = _healthMax;
    _speed = _speedMax;
    _selectedItem = 0;

    _slot_weap = NULL;

    _best_weap = NULL;

    //_hand = new Weapon(15, getPos(), sf::Vector2f(0,0), sf::Vector2f(67,18),IT_PLASMA);

    _leftAngle = 90 * PI / 180;

    _circleLife.setRadius(5);
    _circleLife.setFillColor(sf::Color(0,255,0));
    _circleLife.setPosition(getPos());

    _ID = g_core->getUniqueID();

}

Actor::~Actor(){

    printf("destruction de Actor\n");

}

void Actor::dump(){

    printf("-------------------------\n");
    printf("pos : %f; %f\n", getPos().x, getPos().y);
    printf("health = %d\n", _health);
    printf("address : %p\n", this);
    printf("+++++++++++++++++++++++++\n");

}


void Actor::update(){}

void Actor::render(){

    _circleLife.setPosition(getPos().x - 5, getPos().y - 5);
    g_core->getApp()->draw(_circleLife);
}

int Actor::getHealth() const{

    return _health;

}

team* Actor::getTeam() const{

    return _team;
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

bool Actor::collisionWithCrafter() {

    Crafter* c;

    c = _team->crafter;


    if(getPos().x > c->getPos().x - 150 &&
       getPos().x < c->getPos().x + 150 &&
       getPos().y > c->getPos().y - 150 &&
       getPos().y < c->getPos().y + 150)
        return true;
    else
        return false;


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

    _colorRed = 255 - _health * 2.55;
    _colorGreen = _health * 2.55;

    _circleLife.setFillColor(sf::Color(_colorRed, _colorGreen, 0));

    _attacked = true;

    if(_health <= 0){
        _killed = true;
        drop();
    }

}

void Actor::fire(){}

void Actor::drop(){



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

        float b[4] = {  (*g_core->getWorld()->getDrop())[i]->getPos().x - (*g_core->getWorld()->getDrop())[i]->getFrameW()/2,
                        (*g_core->getWorld()->getDrop())[i]->getPos().y - (*g_core->getWorld()->getDrop())[i]->getFrameH()/2,
                        (*g_core->getWorld()->getDrop())[i]->getPos().x + (*g_core->getWorld()->getDrop())[i]->getFrameW()/2,
                        (*g_core->getWorld()->getDrop())[i]->getPos().y + (*g_core->getWorld()->getDrop())[i]->getFrameH()/2};

        //printf("[2] d = %p | g_core = %p \n" ,d, &(*g_core->getWorld()->getDrop())[i]);

        if(g_core->bounding_box(a, b, true)){

            //printf("[3] d =%p | g_core = %p \n" ,d, &(*g_core->getWorld()->getDrop())[i]);

            setHandItem(g_core->getWorld()->getItemFromIT((*g_core->getWorld()->getDrop())[i]->getItemType()));

            //printf("[4] d = %p | g_core = %p \n" ,d, &(*g_core->getWorld()->getDrop())[i]);

            (*g_core->getWorld()->getDrop())[i]->kill();
            return;

        }


}

}

void Actor::putItemToCrafter(){}

void Actor::switchWeapon(){

    if(_hand != NULL && _hand->getItemCategory() == IC_RESSOURCE){
        drop();
    }

    Item* aux;

    aux = _hand;
    _hand = _slot_weap;
    _slot_weap = aux;
}


void Actor::setHandItem(Item * it){ // METTRE A JOUR

    printf("set hand Item\n");

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
/*
void Actor::defineWBWeap(){

    _best_weap = NULL; _worst_weap = NULL;

    if(_hand != NULL && _hand->getItemCategory == IC_WEAPON){
        _best_weap = _hand;
        _worst_weap = _hand;
    }


        if(_belt[i] != NULL && _belt[i]->getItemCategory == IC_WEAPON){
            if(_best_weap == NULL || (_best_weap->getItemType() < _belt[i]->getItemType()))
                _best_weap = _belt[i];

}
*/





