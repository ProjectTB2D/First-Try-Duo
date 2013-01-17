
#include "Core.h"
#include "global.h"
#include "World.h"
#include "Weapon.h"
#include "Item.h"
#include <math.h>

#define PI 3.14159265359

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////                               WEAPON                                  /////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Weapon::Weapon()
{
}

Weapon::Weapon(int a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d, Item_t it, float dmgMult, float frMult, float sprMult)
:   Item(a, b, c, d, it)
{

    _spread = 0;
    _icat = IC_WEAPON;

    switch(it){

        case IT_BAT :  _dmg = 10; _fireRate = 0.8; _cac = true; break;
        case IT_BAT_SUPER :  _dmg = 10; _fireRate = 0.8; _cac = true; break;
        case IT_PISTOL : _dmg = 5; _fireRate = 1; _spread = 4; break;
        case IT_PISTOL_SUPER : _dmg = 5; _fireRate = 1; _spread = 4; break;
        case IT_THROW_AXE : _dmg = 13; _fireRate = 2; _spread = 10; break;
        case IT_THROW_AXE_SUPER : _dmg = 13; _fireRate = 2; _spread = 10; break;

        case IT_CHAINSAW : _dmg = 20; _fireRate = 1; _cac = true; break;
        case IT_CHAINSAW_SUPER : _dmg = 20; _fireRate = 1; _cac = true; break;
        case IT_SHOTGUN : _dmg = 5; _fireRate = 1.3; _spread = 30; break;
        case IT_SHOTGUN_SUPER : _dmg = 5; _fireRate = 1.3; _spread = 30; break;
        case IT_SMG : _dmg = 4; _fireRate = 0.1; _spread = 20; break;
        case IT_SMG_SUPER : _dmg = 4; _fireRate = 0.1; _spread = 20; break;

        case IT_KATANA : _dmg = 70; _fireRate = 2; _cac = true; break;
        case IT_KATANA_SUPER : _dmg = 70; _fireRate = 2; _cac = true; break;
        case IT_PLASMA : _dmg = 20; _fireRate = 0.5; _spread = 0; break;
        case IT_PLASMA_SUPER : _dmg = 20; _fireRate = 0.5; _spread = 0; break;
        case IT_RPG : _dmg = 90; _fireRate = 3; _spread = 6; break;
        case IT_RPG_SUPER : _dmg = 90; _fireRate = 3; _spread = 6; break;

        default : _dmg = 0; _fireRate = 0;
    }

    _dmg *= dmgMult;
    _fireRate *= frMult;
    _spread *= sprMult;


}

void Weapon::update(){

    // 0.78539;

    float ang = _carrier_angle + 0.58539;

    _spr.setPosition(_carrier_pos.x - 30*cos(ang), _carrier_pos.y - 30*sin(ang));
    _spr.setRotation(_carrier_angle);

}

void Weapon::render(){

    _spr.setRotation(_carrier_angle * 180 / PI);
    g_core->getApp()->draw(_spr);

}

Weapon::~Weapon(){

    printf("+ weapon : %d deleted\n", _it);

}

void Weapon::use(){

    if(_rate.getElapsedTime().asSeconds() > _fireRate){

        if(!_cac){

            g_core->getWorld()->addBullet(_it , getPos() ,_carrier_angle, 1);
        }

        _rate.restart();
    }
}
