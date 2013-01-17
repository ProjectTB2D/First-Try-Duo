#ifndef _included_Item_h
#define _included_Item_h
#include <SFML/Graphics.hpp>
#include "Entity.h"

enum Item_category {IC_WEAPON = 0,
                    IC_RESSOURCE = 1,
                    IC_MOBDROP = 2};

enum Item_t {
        IT_NONE = 0,
        IT_IRON = 1,
        IT_GOLD = 2,
        IT_RUBY = 3,
        IT_EMERALD = 4,
        IT_BAT = 5,
        IT_BAT_SUPER = 6,
        IT_PISTOL = 7,
        IT_PISTOL_SUPER = 8,
        IT_THROW_AXE = 9,
        IT_THROW_AXE_SUPER = 10,
        IT_CHAINSAW = 11,
        IT_CHAINSAW_SUPER = 12,
        IT_SHOTGUN = 13,
        IT_SHOTGUN_SUPER = 14,
        IT_SMG = 15,
        IT_SMG_SUPER = 16,
        IT_KATANA = 17,
        IT_KATANA_SUPER = 18,
        IT_PLASMA = 19,
        IT_PLASMA_SUPER = 20,
        IT_RPG = 21,
        IT_RPG_SUPER = 22};


class Item : public Entity
{

 public:

    Item();
    Item(int, sf::Vector2f, sf::Vector2f, sf::Vector2f, Item_t);
    virtual ~Item() = 0;

    virtual void render() = 0;
	virtual void update() = 0;
	virtual void use() = 0;

	Item_t          getItemType() const;
	Item_category   getItemCategory() const;


    void    setInfo(float, sf::Vector2f);

 protected:

    Item_t          _it;
    Item_category   _icat;

    float           _carrier_angle;
    sf::Vector2f    _carrier_pos;



};


class Ressource : public Item
{

 public:

    Ressource();
    Ressource(int, sf::Vector2f, sf::Vector2f, sf::Vector2f, Item_t);
    ~Ressource();

 protected:

};

/*

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

class Drop : public Entity
{

 public:

 Drop();
 Drop(int, sf::Vector2f, sf::Vector2f, sf::Vector2f, Item_t, bool = false);

 void render();
 void update();

 Item_t getItemType() const;

 protected:

 Item_t     _it;
 bool       _generated;
 sf::Clock  _timer;

};

#endif
