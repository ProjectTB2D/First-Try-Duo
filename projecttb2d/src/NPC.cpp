#include "NPC.h"
#include "global.h"
#include "Core.h"
#include "Actor.h"
#include "Entity.h"
#include "Weapon.h"
#include "World.h"
#include <math.h>

#define PI 3.14159265359

NPC::NPC(const Actor& act, npc_type nt)
:   Actor(act),
    _type(nt),
    _action(ACT_IDLE),
    _target(NULL),
    _strafLeft(true)
{

    //_target = g_core->getWorld()->getTeam1()->p;

}

NPC::~NPC(){


}

void NPC::render(){

    _spr.setRotation(_angle*180/PI);
    if(_hand)
        _hand->render();
    g_core->getApp()->draw(_spr);

}

void NPC::update(){

    if(_attacked){

        _action = ACT_ATK_ENEMY;
    }

    if(_action == ACT_ATK_ENEMY){

        if(_strafTimer.getElapsedTime().asSeconds() > 5.0f){
            _strafTimer.restart();

            if(_strafLeft)
                _strafLeft = false;
            else
                _strafLeft = true;
        }

        float distance_x = getPos().x - _target->getPos().x;
        float distance_y = getPos().y - _target->getPos().y;
        float ft = g_core->getFrameTime();

        _angle = atan2(distance_y, distance_x);

        _hand->use();

        if(fabs(distance_x) > 200.0f || fabs(distance_y) > 200.f)
            _spr.move(-_speed*ft*cos(_angle), -_speed*ft*sin(_angle));
        else if(_strafLeft)
            _spr.move(_speed*ft*cos(_angle + _leftAngle), _speed*ft*sin(_angle + _leftAngle));
        else if(!_strafLeft)
            _spr.move(_speed*ft*cos(_angle - _leftAngle), _speed*ft*sin(_angle - _leftAngle));

    }

    if(_hand){
        _hand->setInfo(_angle, getPos(), this);
        _hand->update();
    }

}


Actor* NPC::getTarget(){

    return _target;

}

void NPC::setTarget(Actor* a){

    _target = a;

}



