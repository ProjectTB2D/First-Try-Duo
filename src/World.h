#ifndef _included_World_hpp
#define _included_World_hpp
#include <stdio.h>
#include <string.h>
#include <list>
#include "Actor.h"
#include "Player.h"
#include "Brick.h"
#include "Enemy.h"
#include "Door.h"
#include "Effect.h"


struct BlockInfo{

    char name[255];
    int x;
    int y;
    int w;
    int h;
    int img;
    brick_type type;

};


class World
{

protected:

int                 _nextUniqueID;


vector<Brick*>      _brickList;
Player*             _player;
vector<Enemy*>      _enemiesList;
list<Item*>         _itemList;
vector<Button*>     _buttonList;
list<Effect>        _effectList;

int                 _gravity;

sf::Clock           _tick;


vector<Brick*>      _brickreduced;
vector<Enemy*>      _enemyreduced;

public:

World();


// --------- CREATE FUNCTIONS -------------

void        createWorld(const char*);
void        createPlayer();
//void        createEnemy();
//void        createItem();


// --------- ADD FUNCTIONS -------------

void        addItem(Item*);
void        addEFence(sf::Vector2f);
void        addEffect(Effect);

// -------- UPDATE FUNCTIONS -----------

void update();

// (update world ???)

// update player



// -------- RENDER FUNCTIONS -----------

void            render();

void            renderWorld();

void            renderPlayer();

void            renderEnemies();

void            renderItems();

void            centerCamera();


// --------- DISOLVE FUNCTIONS ---------------------

void            disolve();

void            disolve_dead_items();
void            disolve_dead_enemies();


// renderEnemies


// renderItems


// --------- SETTER --------------------

 void            setGravity(int);

// ----------- GETTER -------------------

 int             getGravity() const;

 int             generateUniqueID();

 void            SelectBoxBricks(int);
 vector<Brick*>  SelectBoxBricksRender();

 void            SelectBoxEnemy(int);
 vector<Enemy*>  SelectBoxEnemyRender();

 void            SelectBoxItem(int, list<Item*>&);

 Player*         getPlayer();

 bool            insideScreen(int,int,int,int,int);

 Enemy*          getEnemy(int, std::vector<Enemy*>&);

 void            getValueFromParser(char*);




~World();

};
#endif
