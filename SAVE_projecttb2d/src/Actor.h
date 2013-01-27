#ifndef _included_actor_h
#define _included_actor_h

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Item.h"

class Actor : public Entity
{

 public:

    Actor();
    Actor(int, sf::Vector2f, sf::Vector2f, sf::Vector2f, int, float);
    virtual ~Actor();

	virtual void render();
	virtual void update();

    //getter

    int getHealth() const;
    int getHealthMax() const;
    float getSpeed() const;
    float getSpeedMax() const;

    Item * getHand() {return _hand;}
    //Item ** getBelt();

    //setter

    void setHealth(int);
    void setHealthMax(int);
    void setSpeed(float);
    void setSpeedMax(float);

    //void setBeltItem(int, Item*);
    void    setHandItem(Item*);

    // Action

    void damage(int); //inflige des dégats a l'actor
    void fire(); //tirer
    void drop(); // Drop l'item en main
    void rollItem(); // naviguer entre les items de la ceinture et de la main
    void use(); // Ramasser, utiliser, conduire, action...
    void putItemToCrafter(); // Transfert d'un item de la main au crafter (QUE si c'est un bloc)
    //void takeItemFromCrafter(Item_t);
    //void testCollisionWorld(Obstacle*);
    //void testCollisionBullet(Bullet*);


 protected:

    int _health;
    int _healthMax;
    float _speed;
    float _speedMax;

    Item *_hand;
    //Item *_belt[3];

    int _selectedItem;



};



class NPC : public Actor
{

 public:

 protected:


};

class Mob : public Entity
{

 public:

 protected:


};


#endif
