#include "Crafter.h"
#include "Core.h"
#include "global.h"
#include "World.h"
#include <math.h>


Crafter::Crafter(){
}

Crafter::Crafter(int a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d)
:   Entity(a,b,c,d)
{
    _nbIron = 0;
    _nbGold = 50;
    _nbRuby = 50;
    _nbEmerald = 50;

    printf("init iron : %d\n", _nbIron);
}

bool Crafter::update(){return true;}

void Crafter::render(){

    g_core->getApp()->draw(_spr);

}

void Crafter::putIn(Item* it) {

_output.push_back(it->getItemType());

}

void Crafter::putIn(Item_t it) {

switch(it){

    case 0 : break;
    case 1 : _nbIron++;break;
    case 2 : _nbGold++;break;
    case 3 : _nbRuby++;break;
    case 4 : _nbEmerald++;break;
    default : _output.push_back(it);

}

    printf("+--------put in-----\n");
    printf("+ nbIron = %d\n", _nbIron);
    printf("+ nbGold = %d\n", _nbGold);
    printf("+ nbGold = %d\n", _nbRuby);
    printf("+ nbEmerald = %d\n", _nbEmerald);
    printf("+-------------------\n");

}

Item*   Crafter::putOut(Item_t it){

    return g_core->getWorld()->getItemFromIT(it);

}

Item* Crafter::craft(Item_t it){

    Item_t miss = IT_NONE;

    printf("craft()\n");

    recipe rec = getRecipe(it);


    if(!craftable(it, &miss)){
        printf("not enought ressources...\n");
        return NULL;
    }

    printf("youp\n");

    _nbIron -= rec.nbIron;
    _nbGold -= rec.nbGold;
    _nbRuby -= rec.nbRuby;

    return putOut(it);
}

bool Crafter::craftAndPutIn(Item_t it){

    Item_t miss = IT_NONE;

    recipe rec = getRecipe(it);

    if(!craftable(it, &miss))
        return false;

    printf("youp\n");

    _nbIron -= rec.nbIron;
    _nbGold -= rec.nbGold;
    _nbRuby -= rec.nbRuby;

    _output.push_back(it);

    return true;

}

bool Crafter::craftable(const Item_t& it, Item_t* miss) const{

    recipe rec = getRecipe(it);

    /*printf("rec.i = %d | i = %d\n", rec.nbIron, _nbIron);
    printf("rec.g = %d\n", rec.nbGold);
    printf("rec.r = %d\n", rec.nbRuby);
    */

    if(rec.nbRuby > _nbRuby){
        *miss = IT_RUBY;
        return false;
    }

    if(rec.nbGold > _nbGold){
        *miss = IT_GOLD;
        return false;
    }

    if(rec.nbIron > _nbIron){
        *miss = IT_IRON;
        return false;
    }

    return true;

}

bool Crafter::craftSuper(Item_t it){

    recipe rec = getRecipe(it);
    int ressManquante = 0;

    if(_nbEmerald <= 0)
        return false;

    // On detecte s'il manque une ressource
    if(rec.nbRuby > _nbRuby)
        ressManquante += (rec.nbRuby - _nbRuby);

    if(rec.nbGold > _nbGold)
        ressManquante += (rec.nbGold - _nbGold);

    if(rec.nbIron > _nbIron)
        ressManquante += (rec.nbIron - _nbIron);

    if(ressManquante > 1){ // On ne consomme qu'un emerald par SUPER recette
        return false;
    }else if(ressManquante == 1){ // S'il manque une seule ressource, on la remplace

        if(rec.nbRuby > _nbRuby){
            _nbRuby -= (rec.nbRuby - 1);
            _nbEmerald -= 1;

            _nbGold -= rec.nbGold;
            _nbIron -= rec.nbIron;
        }

        if(rec.nbGold > _nbGold){
            _nbGold -= (rec.nbGold - 1);
            _nbEmerald -= 1;

            _nbRuby -= rec.nbRuby;
            _nbIron -= rec.nbIron;
        }

        if(rec.nbIron > _nbIron){
            _nbIron -= (rec.nbIron - 1);
            _nbEmerald -= 1;

            _nbGold -= rec.nbGold;
            _nbRuby -= rec.nbRuby;
        }
    }else{ // S'il ne manque pas de ressource, on remplace la plus élevée

        if(rec.nbRuby > 0){
            _nbIron -= rec.nbIron;
            _nbGold -= rec.nbGold;
            _nbRuby -= (rec.nbRuby - 1);
            _nbEmerald -= 1;
        }
        else if(rec.nbGold > 0){
            _nbIron -= rec.nbIron;
            _nbGold -= (rec.nbGold - 1);
            _nbRuby -= rec.nbRuby;
            _nbEmerald -= 1;
        }
        else if(rec.nbIron > 0){
            _nbIron -= (rec.nbIron - 1);
            _nbGold -= rec.nbGold;
            _nbRuby -= rec.nbRuby;
            _nbEmerald -= 1;
        }
    }


    //_output.push_back(si);

    return true;
}

sf::Vector3i Crafter::getRessources() const{
    sf::Vector3i ress(_nbIron, _nbGold, _nbRuby);
    return ress;
}

int Crafter::getEmerald() const{
    return _nbEmerald;
}

recipe Crafter::getRecipe(Item_t it) const{

    recipe rec;
    rec.result = it;

    switch(it){

        case IT_BAT : rec.nbIron = 2; rec.nbGold = 0; rec.nbRuby = 0; break;
        case IT_BAT_SUPER : rec.nbIron = 2; rec.nbGold = 0; rec.nbRuby = 0; break;
        case IT_PISTOL : rec.nbIron = 2; rec.nbGold = 0; rec.nbRuby = 0; break;
        case IT_PISTOL_SUPER : rec.nbIron = 2; rec.nbGold = 0; rec.nbRuby = 0; break;
        case IT_THROW_AXE : rec.nbIron = 2; rec.nbGold = 0; rec.nbRuby = 0; break;
        case IT_THROW_AXE_SUPER : rec.nbIron = 2; rec.nbGold = 0; rec.nbRuby = 0; break;

        case IT_CHAINSAW : rec.nbIron = 4; rec.nbGold = 2; rec.nbRuby = 0; break;
        case IT_CHAINSAW_SUPER : rec.nbIron = 4; rec.nbGold = 2; rec.nbRuby = 0; break;
        case IT_SHOTGUN : rec.nbIron = 4; rec.nbGold = 2; rec.nbRuby = 0; break;
        case IT_SHOTGUN_SUPER : rec.nbIron = 4; rec.nbGold = 2; rec.nbRuby = 0; break;
        case IT_SMG : rec.nbIron = 4; rec.nbGold = 2; rec.nbRuby = 0; break;
        case IT_SMG_SUPER : rec.nbIron = 4; rec.nbGold = 2; rec.nbRuby = 0; break;

        case IT_KATANA : rec.nbIron = 6; rec.nbGold = 2; rec.nbRuby = 1; break;
        case IT_KATANA_SUPER : rec.nbIron = 6; rec.nbGold = 2; rec.nbRuby = 1; break;
        case IT_PLASMA : rec.nbIron = 6; rec.nbGold = 2; rec.nbRuby = 1; break;
        case IT_PLASMA_SUPER : rec.nbIron = 6; rec.nbGold = 2; rec.nbRuby = 1; break;
        case IT_RPG : rec.nbIron = 6; rec.nbGold = 2; rec.nbRuby = 1; break;
        case IT_RPG_SUPER : rec.nbIron = 6; rec.nbGold = 2; rec.nbRuby = 1; break;

        default : rec.nbIron = 0; rec.nbGold = 0; rec.nbRuby = 0;
    }

    return rec;
}

void Crafter::updateCrafterData(){

}







