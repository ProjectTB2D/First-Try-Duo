#ifndef _included_weap_h
#define _included_weap_h
#include "Item.h"
#include "Actor.h"

#include <SFML/Graphics.hpp>

class Weapon : public Item
{

 public:

    Weapon();
    Weapon(int, sf::Vector2f, sf::Vector2f, sf::Vector2f, Item_t, float = 1.0f, float = 1.0f, float = 1.0f);
    virtual ~Weapon();


    virtual void use();
    virtual void update();
    virtual void render();


 protected:

    int _dmg;
    float _fireRate;
    float _spread;
    bool  _cac;
    sf::Clock _rate;

};
/*
class W_Launcher : public Weapon
{

 public:

 protected:


};

class W_Melee : public Weapon
{

 public:

 protected:


};
*/

#endif
