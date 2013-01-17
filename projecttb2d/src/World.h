#ifndef _included_world_h
#define _included_world_h

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string.h>
#include <list>
#include "Actor.h"
#include "Player.h"
#include "Bullet.h"
#include "Item.h"
#include "HQ.h"

#define MAXNPC 10

class Bullet;
class Drop;
class Obstacle;

struct tile{

    sf::Sprite spr;
    int num;

};

struct team{

    int id;
    Player * p;
    NPC * ai[MAXNPC];
    std::list<Bullet> proj;
    // HQ base;
    // Crafter craft;

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

void        addBullet(Item_t, sf::Vector2f, float, float);
void        addDrop(const sf::Vector2f&, const Item_t&);

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
 std::vector<Drop>* getDrop() {return &_drop;}

 Item*              getItemFromIT(const Item_t&);


protected:

int                 _nextUniqueID;

tile**              _matrice;
team                _team1;
team                _team2;
vector<Drop>        _drop;

RessourceSpawner*   _r_spawner[3];


float               _b[4];

vector<NPC*>      _NPC_reduced;
//vector<Bullet*>   _bullet_reduced;
//vector<Drop*>     _drop_reduced;
//vector<Obstacle*> _obstacle_reduced;

void        parseMapTmx(string, tile***); //, std::vector<Obstacle*>)

};

#endif
