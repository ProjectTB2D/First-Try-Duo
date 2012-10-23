#ifndef _included_Actor_h
#define _included_Actor_h
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Brick.h"



class Actor
{


protected:

// ID

int             _objectID;

// about sprite

sf::Sprite      _spr_main;
float           _frameH;
float           _frameW;

sf::Clock       _aux1; // energy regain


// about myself

short           _life;
float           _angle;
sf::Vector2f    _maxSpeed;
//int             _attack1Dmg;
bool            _killed;

public:


Actor(sf::Vector2f ,short, sf::Vector2f, sf::Vector2f, short, sf::Vector2f); // position / n° image / pos image (sheet) / dim image (sheet) / life / maxspeed

// -------- SETTERS ------------

void    setAngle(float a);

// COLLISION :

void getAutoCollision(std::vector<Brick*>& ,Brick**, Brick**, Brick**, Brick**, Brick**, Brick**,bool = false);


//void getManuelCollision();

Brick* brick_at(std::vector<Brick*>&, sf::Vector2f,bool = false);


// DEPLACEMENT

void move(sf::Vector2f);

// ------- OPERATORS -----------

void            kill();
void            damage(int);

// ------- GETTERS -------------

int             getID()     const;
float           getAngle()  const;
sf::Vector2f    getPos()    const;
float           getFrameW() const;
float           getFrameH() const;
bool            isKilled()  const;

// --------  DESTROYER --------------

virtual ~Actor();

};
#endif
