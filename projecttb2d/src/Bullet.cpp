#include "Bullet.h"
#include "Core.h"
#include "global.h"
#include "World.h"
#include <math.h>

#define PI 3.14159265359

#define vieBullet 1

Bullet::Bullet()
{

}

Bullet::Bullet(int a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d, Item_t it, float angle, float damage, Actor* own)
:   Entity(a,b,c,d),
    _tb(it),
    _damage(damage),
    _owner(own)
{

    //printf("init get pos x = %f, pos y = %f\n", getPos().x, getPos().y);

    _angle = angle;
    _rotation = 0;

    switch(it){

        case IT_PISTOL : _damage = 10; _speed = 1000; break;
        case IT_PISTOL_SUPER : _damage = 5; _speed = 1000; break;
        case IT_THROW_AXE : _damage = 13; _speed = 800; break;
        case IT_THROW_AXE_SUPER : _damage = 13; _speed = 800; break;
        case IT_SHOTGUN : _damage = 5; _speed = 1000; break;
        case IT_SHOTGUN_SUPER : _damage = 5; _speed = 1000; break;
        case IT_SMG : _damage = 4; _speed = 1000; break;
        case IT_SMG_SUPER : _damage = 4; _speed = 1000; break;
        case IT_PLASMA : _damage = 20; _speed = 900; break;
        case IT_PLASMA_SUPER : _damage = 20; _speed = 900; break;
        case IT_RPG : _damage = 90; _speed = 800; break;
        case IT_RPG_SUPER : _damage = 90; _speed = 800; break;

        default : _damage = 0; _speed = 0;
    }

    _lifeTime.restart();
    //printf("balle\n");
}

Bullet::~Bullet(){

    //printf("bullet destroyed !\n");

}

void Bullet::update(){

    if(bulletKilled()){
        _killed = true;
    }
    else{
        _spr.move(-_speed*g_core->getFrameTime()*cos(_angle), -_speed*g_core->getFrameTime()*sin(_angle));
    }
}

void Bullet::render(){


    //printf("pos x = %f, pos y = %f\n", getPos().x, getPos().y);
    if(g_core->getWorld()->insideScreenPoint(getPos().x, getPos().y, 2)){
        if((_tb == IT_THROW_AXE) || (_tb == IT_THROW_AXE_SUPER))
            _rotation += -25*g_core->getFrameTime();
        else
            _rotation = _angle;
        _spr.setRotation(_rotation*180/PI);
        g_core->getApp()->draw(_spr);
    }
    //system("pause");
}

// SETTER

void Bullet::setAngle(float a){

    _angle = a;
}

void Bullet::setSpeed(float s){

    _speed = s;
}

void Bullet::setDamage(float d){

    _damage = d;
}

// GETTER

Item_t Bullet::getTypebullet() const{

    return _tb;
}

float Bullet::getAngle() const{

    return _angle;
}

float Bullet::getSpeed() const{

    return _speed;
}

float Bullet::getDamage() const{

    return _damage;
}

bool Bullet::bulletKilled() const{

    if(_lifeTime.getElapsedTime().asSeconds() > vieBullet)
        return true;

    return false;
}





