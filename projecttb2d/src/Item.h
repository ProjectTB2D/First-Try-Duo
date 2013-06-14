#ifndef _included_Item_h
#define _included_Item_h
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Actor.h"

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
        IT_PISTOL = 6,
        IT_THROW_AXE = 7,
        IT_CHAINSAW = 8,
        IT_SHOTGUN = 9,
        IT_SMG = 10,
        IT_KATANA = 11,
        IT_PLASMA = 12,
        IT_RPG = 13,

        IT_BAT_SUPER = 14,
        IT_PISTOL_SUPER = 15,
        IT_THROW_AXE_SUPER = 16,
        IT_CHAINSAW_SUPER = 17,
        IT_SHOTGUN_SUPER = 18,
        IT_SMG_SUPER = 19,
        IT_KATANA_SUPER = 20,
        IT_PLASMA_SUPER = 21,
        IT_RPG_SUPER = 22};


class Item : public Entity
{

 public:

    Item();
    Item(int, sf::Vector2f, sf::Vector2f, sf::Vector2f, Item_t, Actor* = NULL);
    virtual ~Item() = 0;

    virtual void render() = 0;
	virtual bool update() = 0;
	virtual void use() = 0;

	Item_t          getItemType() const;
	Item_category   getItemCategory() const;


    void    setInfo(float, sf::Vector2f, Actor*);
    void    setOwner(Actor*);
    Actor*  getOwner();

 protected:

    Item_t          _it;
    Item_category   _icat;
    Actor*  _owner;

    float           _carrier_angle;
    sf::Vector2f    _carrier_pos;



};


class Ressource : public Item
{

 public:

    Ressource();
    Ressource(int, sf::Vector2f, sf::Vector2f, sf::Vector2f, Item_t);
    ~Ressource();

    bool update();
    void render();
    void use();

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
 ~Drop();

 void render();
 bool update();

 Item_t getItemType() const;
 bool   getGenerated() const;

 protected:

 Item_t     _it;
 bool       _generated;
 sf::Clock  _timer;

};

#endif
