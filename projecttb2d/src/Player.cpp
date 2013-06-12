#include "Player.h"
#include "global.h"
#include "Core.h"
#include "Actor.h"
#include "Entity.h"
#include "Weapon.h"
#include "World.h"
#include <math.h>

#define PI 3.14159265359

Player::Player()
{

}

Player::Player(const Actor& act)
:   Actor(act),
    _menu(false)
{

    _health = 100000000;

    _ID = g_core->getUniqueID();
    printf("player has ID : %d\n", _ID);

    _hand = g_core->getWorld()->getItemFromIT(IT_SHOTGUN);
}

Player::~Player(){

printf("joueur deleted !\n");
if(_hand != NULL){
    delete _hand;
}

}

void Player::update(){

if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && collisionWithCrafter() &&_clock_use.getElapsedTime().asSeconds() > 0.5)
 {
    _clock_use.restart();
    if(!_menu){
        g_core->getMenu()->enable();
        _menu = true;
    }
    else{
        g_core->getMenu()->disable();
        _menu = false;
    }


 }

if(!_menu){

    sf::Vector2f position = g_core->getApp()->mapPixelToCoords(sf::Mouse::getPosition(), (*g_core->getView()));

    float distance_x = getPos().x - position.x;
    float distance_y = getPos().y - position.y;
    float ft = g_core->getFrameTime();
    //printf("ft = %f", ft);

    _angle = atan2(distance_y, distance_x);



    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){

        _spr.move(-_speed*ft*cos(_angle), -_speed*ft*sin(_angle));
        //printf("angle = %f\n | speed = %f\n", _angle*180/PI, _speed);

    }
    else
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){

        _spr.move(_speed*ft*cos(_angle), _speed*ft*sin(_angle));
        //printf("angle = %f\n | speed = %f\n", _angle*180/PI, _speed);

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
     {
        _spr.move(_speed*ft*cos(_angle + _leftAngle), _speed*ft*sin(_angle + _leftAngle));
        //printf("angle = %f\n | speed = %f\n", _angle*180/PI, _speed);

     }
     else
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
     {
        _spr.move(_speed*ft*cos(_angle - _leftAngle), _speed*ft*sin(_angle - _leftAngle));
        //printf("angle = %f\n | speed = %f\n", _angle*180/PI, _speed);

     }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
     {
        drop();
        //system("cls");
        //g_core->getWorld()->getTeam1()->ai[0]->getTarget()->dump();
        //g_core->getWorld()->getTeam1()->ai[0]->getTarget()->render();

     }
     else
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && _clock_use.getElapsedTime().asSeconds() > 0.5)
     {
         //system("pause");

        for(unsigned int i = 0; i < g_core->getWorld()->getTeam2()->ai.size(); i++){

            g_core->getWorld()->getTeam2()->ai[i]->setTarget(NULL);

        }

        //g_core->getWorld()->addNPC(getPos(), _team, NPC_SOLDIER);

        use();
        _clock_use.restart();
            /*printf("-----------------\n");
            for(unsigned int i = 0; i < g_core->getWorld()->getDrop()->size(); i++){

                printf("id = %p\n", &(*g_core->getWorld()->getDrop())[i]);

            }
    */
     }



    if(_hand){

         if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
         {
            _hand->use();

         }

    }

}

if(_hand){
    _hand->setInfo(_angle, getPos(), this);
    _hand->update();
}

}

void Player::render(){

    _spr.setRotation(_angle*180/PI);
    if(_hand)
        _hand->render();
    g_core->getApp()->draw(_spr);
    Actor::render();
}



