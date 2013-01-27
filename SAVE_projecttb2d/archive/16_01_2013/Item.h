#ifndef _included_Item_h
#define _included_Item_h
#include <SFML/Graphics.hpp>
#include "Entity.h"

enum Item_t {
        IT_NONE = 0,
        IT_IRON = 1,
        IT_GOLD = 2,
        IT_RUBY = 3,
        IT_BAT = 4,
        IT_PISTOL = 5,
        IT_THROW_AXE = 6,
        IT_CHAINSAW = 7,
        IT_SHOTGUN = 8,
        IT_SMG = 9,
        IT_KATANA = 10,
        IT_PLASMA = 11,
        IT_RPG = 12};

class Item : public Entity
{

 public:

    Item();
    Item(const Entity&, Item_t, bool = false);
    virtual ~Item() = 0;

    virtual void render() = 0;
	virtual void update() = 0;
	virtual void use() = 0;

	bool    getSuper() const;
	Item_t  getItemType() const;
    bool    getWeapon() const;

    void    setInfo(float, sf::Vector2f);

 protected:

    Item_t  _it;
    bool    _super;
    bool    _weapon;

    float           _carrier_angle;
    sf::Vector2f    _carrier_pos;



};

/*
class Ressource : public Item
{

 public:

 protected:


};

class MobDrop : public Item
{

 public:

 protected:


};

class Bag : public Item
{

 public:

 protected:


};
*/
#endif
