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
    _straf_time = 0.1;


    if(_team == g_core->getWorld()->getTeam1())
        _spr.setTextureRect(sf::IntRect(0, 0, 50, 50));
    else
        _spr.setTextureRect(sf::IntRect(50, 0, 50, 50));

    switch(_type){

        case NPC_SCOUT : _alloc = 0;_action=ACT_COLLECTING;break;
        case NPC_SOLDIER : _alloc = 2;break;
        case NPC_MEDIC : _alloc = 1;break;
        case NPC_CYBORG : _alloc = 4;break;

    }

}

NPC::~NPC(){

printf("NPC :: Deleted !\n");
if(_hand != NULL){
    delete _hand;
}

}

void NPC::render(){

  sf::Text fpsMessage;
    int FPS;
    ostringstream oss;

    FPS = _action;
    oss << "id : " << this << " | Act : " << FPS << " | t = " << _target << " w : " << ((_slot_weap)?_slot_weap->getItemType() : -1);

    fpsMessage.setPosition(getPos().x - 25, getPos().y + 25);
    fpsMessage.setColor(sf::Color(255,0,0,255));
    fpsMessage.setString(oss.str());
    fpsMessage.setCharacterSize(14);



    _spr.setRotation(_angle*180/PI);
    if(_hand)
        _hand->render();
    g_core->getApp()->draw(_spr);
    Actor::render();
     g_core->getApp()->draw(fpsMessage);
}

void NPC::update(){

    if(_action == ACT_IDLE){

        if(_checkWeapon.getElapsedTime().asSeconds() > 5){

            printf("check weapon\n");
            _checkWeapon.restart();
            if(ai_alloc())
                _action = ACT_CRAFT;
            else
                _action = ACT_COLLECTING;


        }

    }

    if(_action != ACT_ATK_ENEMY && (_attacked || (_type == NPC_SOLDIER && search()))){

        //printf("action 2\n");
        _attacked = false;
        _best_weap = getBestWeapon();
        if(_best_weap != NULL && _best_weap->getItemCategory() == IC_WEAPON){
            _action = ACT_ATK_ENEMY;
            if(_best_weap != _hand){
                switchWeapon();
            }

        }
        else
        _action = ACT_CRAFT;
        //printf("???????????????????????????????????\n");
    }

    if( _action == ACT_CRAFT){

        //printf("ACT_CRAFT\n");
        //ai_alloc();
        ai_craft(_weap_craft);

    }

    if(_action == ACT_COLLECTING){

        //printf("ACT_COLLECTING_____________________________\n");

        if(_hand){
            if(_hand->getItemCategory() == IC_RESSOURCE){

                    _destination = _team->crafter->getPos();


                if(ai_move()){

                    //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                    drop();
                    _rs = NULL;

                    if(ai_alloc())
                        _action = ACT_CRAFT;

                    //if(_weap_craft != IT_NONE)
                    //    _action = ACT_CRAFT;

                }
            }
            else{
                //drop();
                Item* aux = getWeakestWeapon();
                if(_slot_weap == NULL)
                    switchWeapon();
                else{
                    if(_hand == aux)
                        drop();
                    else{
                        switchWeapon();
                        drop();
                    }
                }
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

        //printf("ACTION 3\n");

        if(_target == NULL || (_target != NULL && _target->getKilled())){
            printf("%p : target detruite... : %p\n", this, _target);
            _target = NULL;
            _action = ACT_IDLE;
        }
        else{

            if(_best_weap == NULL){
                _action = ACT_CRAFT;
                //printf("j'ai pas d'arme, je fuis\n");
            }
            else{

                if(_strafTimer.getElapsedTime().asSeconds() > _straf_time){
                    _strafTimer.restart();
                    _straf_time = rand()%5 + 1;

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


    // TEST PLAYER

    float b[4] = {  getPos().x - g_core->getWinSize().x/2,
                    getPos().y - g_core->getWinSize().y/2,
                    getPos().x + g_core->getWinSize().x/2,
                    getPos().y + g_core->getWinSize().y/2};



    for(vector<NPC*>::iterator it = t->ai.begin(); it != t->ai.end(); it++){

        //printf("je cherche\n");
        if(!(*it)->getKilled()){

            float a[4] = {  (*it)->getPos().x - 25,
                            (*it)->getPos().y - 25,
                            (*it)->getPos().x + 25,
                            (*it)->getPos().y + 25};

            if(g_core->bounding_box(a,b,false)){
                _target = *it;
                //printf("target found\n");
                return true;
            }
        }

    }
    _target = NULL;
    return false;

}

Item* NPC::getBestWeapon(){

    if(_hand == NULL && _slot_weap == NULL)
        return NULL;

    if(_hand == NULL && _slot_weap != NULL)
        return _slot_weap;

    if(_hand != NULL && _slot_weap == NULL)
        return _hand;

    if(!_hand && !_slot_weap){

        if(_hand->getItemType() > _slot_weap->getItemType())
            return _hand;
        else
            return _slot_weap;

    }

    return NULL;

}

Item* NPC::getWeakestWeapon(){

    if(_hand == NULL && _slot_weap == NULL)
        return NULL;

    if(_hand == NULL && _slot_weap != NULL)
        return _slot_weap;

    if(_hand != NULL && _slot_weap == NULL)
        return _hand;

    if(!_hand && !_slot_weap){

        if(_hand->getItemType() < _slot_weap->getItemType())
            return _hand;
        else
            return _slot_weap;

    }

    return NULL;

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
    g_core->getWorld()->disolve_dead_drop();

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

    //printf("1\n");

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

        //printf("je suis pauvre (ptit merde)\n");
        _ress = miss;
        _action = ACT_COLLECTING;
    }

}

bool NPC::ai_alloc(){

    int a = 13;
    Item_t i = IT_NONE;

    while(a > 6 && !_team->crafter->craftable((Item_t)a, &i)){a--;}

    Item* aux = getBestWeapon();

    if((aux == NULL) || (aux != NULL && aux->getItemType() < a)){
       _weap_craft = (Item_t)a;
       printf("arme possible = %d\n", a);
       return true;
    }
    return false;

    //printf("Item : %d\n", _weap_craft);

}

bool NPC::ai_take_drop(){

return 0;

}

void NPC::dotest(){



}


