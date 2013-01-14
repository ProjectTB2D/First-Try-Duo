#include "Player.h"
#include "global.h"
#include "Core.h"
#include "Actor.h"
#include "Entity.h"
#include <math.h>

#define PI 3.14159265359

Player::Player()
{

}

Player::Player(const Actor& act)
: Actor(act)
{

    _leftAngle = 90 * PI / 180;

}

Player::~Player(){

printf("joueur deleted !\n");

}

void Player::update(){

sf::Vector2f position = g_core->getApp()->convertCoords(sf::Mouse::getPosition(), (*g_core->getView()));

float distance_x = getPos().x - position.x;
float distance_y = getPos().y - position.y;

_angle = atan2(distance_y, distance_x);



if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){

    _spr.move(-_speed*cos(_angle), -_speed*sin(_angle));
    //printf("angle = %f\n | speed = %f\n", _angle*180/PI, _speed);

}
else
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){

    _spr.move(_speed*cos(_angle), _speed*sin(_angle));
    //printf("angle = %f\n | speed = %f\n", _angle*180/PI, _speed);

}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
 {
    _spr.move(_speed*cos(_angle + _leftAngle), _speed*sin(_angle + _leftAngle));
    //printf("angle = %f\n | speed = %f\n", _angle*180/PI, _speed);

 }
 else
 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
 {
    _spr.move(_speed*cos(_angle - _leftAngle), _speed*sin(_angle - _leftAngle));
    //printf("angle = %f\n | speed = %f\n", _angle*180/PI, _speed);

 }

/* if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
 {
    _spr.move(_speed*cos(_angle - _leftAngle), _speed*sin(_angle - _leftAngle));
    printf("angle = %f\n | speed = %f\n", _angle*180/PI, _speed);

 }*/


}

void Player::render(){

    _spr.setRotation(_angle*180/PI);
    g_core->getApp()->draw(_spr);

}
