#include "Bullet.h"
#include "Core.h"
#include "global.h"
#include <math.h>

#define PI 3.14159265359

#define vieBullet 10

Bullet::Bullet()
{

}

Bullet::Bullet(const Entity& ent, typeBullet tb, float angle, float speed, float spread, float damage)
:   Entity(ent),
    _tb(tb),
    _angle(angle),
    _speed(speed),
    _spread(spread),
    _damage(damage)
{
    _lifeTime.restart();
    printf("balle\n");
}

Bullet::~Bullet(){

}

void Bullet::update(){

    if(bulletKilled()){
        _killed = true;
    }
    else{

        _spr.move(-_speed*cos(_angle), -_speed*sin(_angle));
    }
}

void Bullet::render(){

    _spr.setRotation(_angle*180/PI);
    g_core->getApp()->draw(_spr);
}

// SETTER

void Bullet::setAngle(float a){

    _angle = a;
}
void Bullet::setSpeed(float s){

    _speed = s;
}
void Bullet::setSpread(float s){

    _spread = s;
}
void Bullet::setDamage(float d){

    _damage = d;
}

// GETTER

typeBullet Bullet::getTypebullet() const{

    return _tb;
}
float Bullet::getAngle() const{

    return _angle;
}
float Bullet::getSpeed() const{

    return _speed;
}
float Bullet::getSpread() const{

    return _spread;
}
float Bullet::getDamage() const{

    return _damage;
}

bool Bullet::bulletKilled() const{

    if(_lifeTime.getElapsedTime().asSeconds() > vieBullet)
        return true;

    return false;
}





