#ifndef _included_HQ_h
#define _included_HQ_h
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Item.h"

#define IRON_SPAWN_RATE 1
#define GOLD_SPAWN_RATE 30
#define RUBY_SPAWN_RATE 60
#define EMRLD_SPAWN_RAND_I 5
#define EMRLD_SPAWN_RAND_G 10
#define EMRLD_SPAWN_RAND_R 15
#define DISTANCE 10

class HQ : public Entity
{
 public:

	HQ();
	HQ(int, sf::Vector2f, sf::Vector2f, sf::Vector2f, float, team*);

	virtual void render();
	virtual bool update();

	void    setHealth(float);
	float   getHealth() const;
	void    setDamage(float);


 protected:

    float     _health;
    team*     _tm;


};

class RessourceSpawner : public Entity
{

 public:

 RessourceSpawner();
 RessourceSpawner(int, sf::Vector2f, sf::Vector2f, sf::Vector2f, Item_t, int);
 ~RessourceSpawner();

 bool update();
 void render();

 void    restartTimer(){ _timer.restart();}
 Drop**  getMatrice();
 Item_t getRSType() {return _it;}

 protected:

 Item_t _it;
 int    _spawn;  // 0 : iron | 1 : gold | 2 : ruby
 Drop*  _matrice[9];
 sf::Clock _timer;
 int _spawnRate, _spawnRand;

 void   addRessource();
 void   addEmerald();

};
#endif
