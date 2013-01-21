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

}

void Crafter::update(){}

void Crafter::render(){}

bool Crafter::craft(Item_t it){

    recipe rec = getRecipe(it);

    if(rec.nbRuby > _nbRuby)
        return false;

    if(rec.nbGold > _nbGold)
        return false;

    if(rec.nbIron > _nbIron)
        return false;

    storedItem si;
    si.item = it;
    si.dmg_mult = 1;
    si.spd_mult = 1;
    si.spr_mult = 1;

    _output.push_back(si);

    _nbIron -= rec.nbIron;
    _nbGold -= rec.nbGold;
    _nbRuby -= rec.nbRuby;

    return true;
}

bool Crafter::craftSuper(Item_t it){

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







