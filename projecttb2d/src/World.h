#ifndef _included_world_h
#define _included_world_h

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string.h>
#include <list>
#include "Actor.h"
#include "Player.h"

#define MAXNPC 10

class Bullet;
class Drop;
class Obstacle;

struct team{

    int id;
    Player * p;
    NPC * ai[MAXNPC];
    // HQ base;
    // Crafter craft;
    //std::list<Bullet> proj;
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

 int             generateUniqueID();

 team*         getTeam1();
 team*         getTeam2();

 Player*         getPlayerTeam1();
 Player*         getPlayerTeam2();

 bool            insideScreen(int,int,int,int,int) const;

 NPC*            getNPCTeam1(int);
 NPC*            getNPCTeam2(int);

protected:

int                 _nextUniqueID;
// tile...
team                _team1;
team                _team2;
//vector<Drop>        _drop;

vector<NPC*>      _NPC_reduced;
//vector<Bullet*>   _bullet_reduced;
//vector<Drop*>     _drop_reduced;
//vector<Obstacle*> _obstacle_reduced;

};

#endif
