#ifndef _included_HQ_h
#define _included_HQ_h
#include <SFML/Graphics.hpp>
#include "src/Entity.h"

class HQ : public Entity
{
 public:

	HQ();
	HQ(Entity&, float = 100);

	virtual void render();
	virtual void update();

	void    setHealth(float);
	float   getHealth() const;
	void    setDamage(float);


 protected:

    float     _health;


};
#endif
