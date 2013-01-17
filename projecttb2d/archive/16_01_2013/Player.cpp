#include "Player.h"
#include "global.h"
#include "Core.h"
#include "Actor.h"
#include "Entity.h"
#include "Weapon.h"
#include <math.h>

#define PI 3.14159265359

Player::Player()
{

}

Player::Player(const Actor& act)
:   Actor(act),
    _hand(NULL)
{

    _leftAngle = 90 * PI / 180;
    _hand = new Weapon(Entity(3, getPos(), sf::Vector2f(0,0), sf::Vector2f(30,10)),
                        IT_SMG);

}

Player::~Player(){

printf("joueur deleted !\n");
if(_hand != NULL){
    delete _hand;
}

}

void Player::update(){

sf::Vector2f position = g_core->getApp()->convertCoords(sf::Mouse::getPosition(), (*g_core->getView()));

float distance_x = getPos().x - position.x;
float distance_y = getPos().y - position.y;
float ft = g_core->getFrameTime();
//printf("ft = %f", ft);

_angle = atan2(distance_y, distance_x);



if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){

    _spr.move(-_speed*ft*cos(_angle), -_speed*ft*sin(_angle));
    //printf("angle = %f\n | speed = %f\n", _angle*180/PI, _speed);

}
else
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){

    _spr.move(_speed*ft*cos(_angle), _speed*ft*sin(_angle));
    //printf("angle = %f\n | speed = %f\n", _angle*180/PI, _speed);

}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
 {
    _spr.move(_speed*ft*cos(_angle + _leftAngle), _speed*ft*sin(_angle + _leftAngle));
    //printf("angle = %f\n | speed = %f\n", _angle*180/PI, _speed);

 }
 else
 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
 {
    _spr.move(_speed*ft*cos(_angle - _leftAngle), _speed*ft*sin(_angle - _leftAngle));
    //printf("angle = %f\n | speed = %f\n", _angle*180/PI, _speed);

 }

 if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
 {
    _hand->use();

 }
_hand->setInfo(_angle, getPos());
_hand->update();

}

void Player::render(){

    _spr.setRotation(_angle*180/PI);
    g_core->getApp()->draw(_spr);
    _hand->render();

}
