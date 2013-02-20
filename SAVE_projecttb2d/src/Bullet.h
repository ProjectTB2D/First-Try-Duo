#ifndef _included_BULLET_h
#define _included_BULLET_h
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Item.h"
#include "Actor.h"


class Bullet : public Entity
{
 public:

	Bullet();
	Bullet(int, sf::Vector2f, sf::Vector2f, sf::Vector2f, Item_t, float, float, Actor*);
	~Bullet();

	virtual void render();
	virtual void update();

    // SETTER

	void        setAngle(float);
	void        setSpeed(float);
    void        setDamage(float);

    // GETTER

    Item_t getTypebullet() const;
    float getAngle() const;
    float getSpeed() const;
    float getDamage() const;
    Actor*getOwner() { return _owner;}


 protected:

    Item_t _tb;
    float _speed;
    float _damage;
    float _rotation;
    Actor*  _owner;

    bool bulletKilled() const;

    sf::Clock _lifeTime;

};
#endif
