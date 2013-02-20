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

printf("Construction NPC : %p\n", this);
    //_target = g_core->getWorld()->getTeam1()->p;
    _rs = NULL;
    _freeStyle = true;
    _weap_craft = IT_NONE;
    _ress = IT_IRON;

    switch(_type){

        case NPC_SCOUT : _alloc = 0;break;
        case NPC_SOLDIER : _alloc = 2;break;
        case NPC_MEDIC : _alloc = 1;break;
        case NPC_CYBORG : _alloc = 4;break;

    }

}

NPC::~NPC(){

printf("npc deleted !\n");
if(_hand != NULL){
    delete _hand;
}

}

void NPC::render(){

    _spr.setRotation(_angle*180/PI);
    if(_hand)
        _hand->render();
    g_core->getApp()->draw(_spr);
    Actor::render();
}

void NPC::update(){


    if(_action != ACT_ATK_ENEMY && (_attacked || (_type == NPC_SOLDIER && search()))){

        printf("action 2\n");
        _attacked = false;
        if(_hand != NULL && _hand->getItemCategory() == IC_WEAPON)
        _action = ACT_ATK_ENEMY;
        else
        _action = ACT_CRAFT;
        //printf("???????????????????????????????????\n");
    }

    if( _action == ACT_CRAFT){

        printf("ACT_CRAFT\n");
        ai_alloc();
        ai_craft(_weap_craft);

    }

    if(_action == ACT_COLLECTING){

        //printf("ACT_COLLECTING_____________________________\n");

        if(_hand){
            if(_hand->getItemType() > 0 && _hand->getItemType() < 5){

                    _destination = _team->crafter->getPos();


                if(ai_move()){

                    //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
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
            //printf("je suis arrive\n");
            Drop* d;
            d = ai_chose_spawner_drop();
            if(d != NULL){
                ai_get_drop(d);
            }
        }
    }

    if(_action == ACT_ATK_ENEMY){

        printf("ACTION 3\n");

        if(_target == NULL || (_target != NULL && _target->getKilled())){
            printf("target detruite...\n");
            _target = NULL;
            _action = ACT_IDLE;
        }
        else{

            if(_hand == NULL || (_hand != NULL && _hand->getItemCategory() != IC_WEAPON)){
                _action = ACT_CRAFT;
                //printf("j'ai pas d'arme, je fuis\n");
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

bool NPC::search(){

    World* w = g_core->getWorld();
    team* t = (_team == w->getTeam1()) ? w->getTeam2() : w->getTeam1();

    NPC** ai;

    // TEST PLAYER

    float b[4] = {  getPos().x - g_core->getWinSize().x/2,
                    getPos().y - g_core->getWinSize().y/2,
                    getPos().x + g_core->getWinSize().x/2,
                    getPos().y + g_core->getWinSize().y/2};



    for(ai = t->ai; (*ai) != NULL; ai++){

        if(!(*ai)->getKilled()){

            float a[4] = {  (*ai)->getPos().x,
                            (*ai)->getPos().y,
                            (*ai)->getFrameW(),
                            (*ai)->getFrameH()};

            if(g_core->bounding_box(a,b,false)){
                _target = *ai;
                printf("target found\n");
                return true;
            }
        }

    }

    return false;

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

    //printf("je prend un truc par terre\n");
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

    printf("1\n");

    Crafter* c;
    Item_t miss = IT_NONE;

    c = _team->crafter;

    if(c->craftable(it, &miss)){
        _destination = c->getPos();
        if(ai_move()){
            setHandItem(c->craft(it));
            _action = ACT_IDLE;
            _weap_craft = IT_NONE;

        }
    }
    else{

        printf("je suis pauvre (ptit merde)\n");
        _ress = miss;
        _action = ACT_COLLECTING;
    }

}

void NPC::ai_alloc(){

    int a = 13;
    Item_t i = IT_NONE;

    while(a > 4 && !_team->crafter->craftable((Item_t)a, &i)){a--;}


    if(_hand != NULL && _hand->getItemType() < a)
       _weap_craft = (Item_t)a;
    else
        _weap_craft = IT_PISTOL;

    printf("Item : %d\n", _weap_craft);

}

void NPC::dotest(){



}


