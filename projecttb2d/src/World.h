#ifndef _included_world_h
#define _included_world_h

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string.h>
#include <list>
#include "team.h"
#include "Actor.h"
#include "Player.h"
#include "Bullet.h"
#include "Item.h"
#include "NPC.h"
#include "HQ.h"
#include "Crafter.h"

class Bullet;
class Drop;
class Obstacle;


struct area{

    std::vector<Entity*> list;
    sf::Vector2f pos;
    sf::Vector2f dim;

};

struct tile{

    sf::Sprite spr;
    int num;

};



class World
{


public:

World();
~World();

// --------- CREATE FUNCTIONS -------------

void        createWorld(const char*);
void        createPlayer();
void        createNPC();
void        createItem();

// --------- ADD FUNCTIONS -------------

void        addBullet(Item_t, sf::Vector2f, float, float, Actor*, team*);
Drop*       addDrop(const sf::Vector2f&, const Item_t&, bool = false);

void        addNPC(sf::Vector2f, team*, npc_type = NPC_SOLDIER);

// -------- UPDATE FUNCTIONS -----------

void update();


// -------- RENDER FUNCTIONS -----------

void            render();

void            renderWorld();

void            centerCamera();


// --------- DISOLVE FUNCTIONS ---------------------

void            disolve();

void            disolve_dead_drop();
void            disolve_dead_NPC();
void            disolve_dead_bullet();


// ----------- GETTER -------------------

 int                generateUniqueID();

 team*              getTeam1();
 team*              getTeam2();

 Player*            getPlayerTeam1();
 Player*            getPlayerTeam2();

 bool               insideScreen(int,int,int,int,int) const;
 bool               insideScreenPoint(int, int, int) const;

 NPC*               getNPCTeam1(int);
 NPC*               getNPCTeam2(int);

 tile***            getMatrice(){ return &_matrice;}
 std::vector<Drop*>* getDrop() {return &_drop;}

 RessourceSpawner** getRSpawn(){return _r_spawner;}

 Item*              getItemFromIT(const Item_t&);


protected:

int                 _nextUniqueID;

tile**              _matrice;
team                _team1;
team                _team2;
vector<Drop*>       _drop;

area                _area[9];
RessourceSpawner*   _r_spawner[3];

float               _b[4];
sf::Vector2f        _mapSize;

vector<NPC*>      _NPC_reduced;
//vector<Bullet*>   _bullet_reduced;
//vector<Drop*>     _drop_reduced;
//vector<Obstacle*> _obstacle_reduced;

void        parseMapTmx(string, tile***); //, std::vector<Obstacle*>)

};

#endif
