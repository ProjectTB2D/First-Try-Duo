#ifndef _included_BULLET_h
#define _included_BULLET_h
#include <SFML/Graphics.hpp>
#include "Entity.h"

    enum typeBullet {B_PISTOL, B_TROWAXE};

class Bullet : public Entity
{
 public:

	Bullet();
	Bullet(const Entity&, typeBullet, float, float, float, float);
	~Bullet();

	virtual void render();
	virtual void update();

    // SETTER

	void        setAngle(float);
	void        setSpeed(float);
    void        setSpread(float);
    void        setDamage(float);

    // GETTER

    typeBullet getTypebullet() const;
    float getAngle() const;
    float getSpeed() const;
    float getSpread() const;
    float getDamage() const;


 protected:

    typeBullet _tb;
    float _angle;
    float _speed;
    float _spread;
    float _damage;

    bool bulletKilled() const;

    sf::Clock _lifeTime;

};
#endif
