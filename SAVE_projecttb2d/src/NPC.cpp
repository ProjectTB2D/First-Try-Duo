#include "NPC.h"
#include "global.h"
#include "Core.h"
#include "Actor.h"
#include "Entity.h"
#include "Weapon.h"
#include "World.h"
#include "Item.h"
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
    _rs = NULL;
    _freeStyle = true;
    _weap_craft = IT_NONE;
    _ress = IT_IRON;

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

        _attacked = false;
        _action = ACT_ATK_ENEMY;
        printf("???????????????????????????????????\n");
    }

    if( _action == ACT_CRAFT){

        _weap_craft = IT_PISTOL;
        ai_craft(_weap_craft);

    }

    if(_action == ACT_COLLECTING){

        //printf("ACT_COLLECTING_____________________________\n");

        if(_hand){
            if(_hand->getItemType() > 0 && _hand->getItemType() < 5){
                if(_team == '1')
                    _destination = g_core->getWorld()->getTeam1()->crafter->getPos();
                else
                    _destination = g_core->getWorld()->getTeam2()->crafter->getPos();

                if(ai_move()){

                    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                    drop();
                    _rs = NULL;
                    if(_weap_craft != IT_NONE)
                        _action = ACT_CRAFT;
                }
            }
            else{
                drop();
                _rs = NULL;
            }
        }

        if(_rs == NULL){

            _rs = ai_get_spawner(_ress);

            if(!_rs) printf("no resspawner found...\n");

            _destination = _rs->getPos();


        }


        if(_hand == NULL && ai_move()){
            printf("je suis arrive\n");
            Drop* d;
            d = ai_chose_spawner_drop();
            if(d != NULL){
                ai_get_drop(d);
            }
        }
    }

    if(_action == ACT_ATK_ENEMY){

        if(_hand == NULL || (_hand != NULL && _hand->getItemCategory() != IC_WEAPON)){
            _action = ACT_CRAFT;
            printf("j'ai pas d'arme, je fuis\n");
        }
        else{

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

///////////////////////////// AI ACTION ///////////////////////////////

RessourceSpawner* NPC::ai_get_spawner(const Item_t& it){

    //printf("DEBUT AI_GET_SPAWNER\n");

    World* w = g_core->getWorld();

    RessourceSpawner** rs;
    RessourceSpawner* ret = NULL;

    float distance = 1100000;
    float dist;

    for(rs = w->getRSpawn(); (*rs) != NULL; rs++){

        //printf("boucle\n");

        if((*rs)->getRSType() == it){
            //printf("autre\n");
            dist = sqrt(pow((getPos().x - (*rs)->getPos().x), 2) +  pow((getPos().y - (*rs)->getPos().y), 2));
            //printf("dist = %f\n", dist);
            if(dist < distance){
                //printf("found\n");
                distance = dist;
                ret = (*rs);
                //printf("found2\n");
            }
        }
    }

    //printf("exit...\n");

    return ret;

}

Drop* NPC::ai_chose_spawner_drop(){

    if(_rs->getMatrice()[4])
        return _rs->getMatrice()[4];

    for(int i = 0; i < 9; i++)
        if(_rs->getMatrice()[i])
            return _rs->getMatrice()[i];

    return NULL;

}

bool NPC::ai_get_drop(Drop* d){

    printf("je prend un truc par terre\n");
    setHandItem(g_core->getWorld()->getItemFromIT(d->getItemType()));
    d->kill();

    return true;
}

bool NPC::ai_move(){

    float distance_x = getPos().x - _destination.x;
    float distance_y = getPos().y - _destination.y;
    float ft = g_core->getFrameTime();

    _angle = atan2(distance_y, distance_x);

    float distance_total = sqrt(pow(distance_x,2) + pow(distance_y,2));

    if(fabs(distance_total) > 5){
        _spr.move(-_speed*ft*cos(_angle), -_speed*ft*sin(_angle));
        return false;
    }
        return true;

}

void NPC::ai_drop(){}

void NPC::ai_craft(Item_t it){


    Crafter* c;
    Item_t miss = IT_NONE;

    if(_team == '1')
        c = g_core->getWorld()->getTeam1()->crafter;
    else
        c = g_core->getWorld()->getTeam2()->crafter;

    if(c->craftable(it, &miss)){
        _destination = c->getPos();
        if(ai_move()){
            setHandItem(c->craft(it));
            _action = ACT_ATK_ENEMY;

        }
    }
    else{

        printf("je suis pauvre (ptit merde)\n");
        _ress = miss;
        _action = ACT_COLLECTING;
    }

}

void NPC::dotest(){



}



