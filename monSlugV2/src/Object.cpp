#include "../include/Object.h"
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

Object::Object(sf::Texture & img, float x, float y, std::string equipe, std::string type, bool solid, int id)
: _x(x), _y(y), _killed(false), _equipe(equipe), _type(type), _solid(solid), _id(id)
{

        mySprite.setTexture(img);
		//mySprite.Scale(0.7,0.7);
		mySprite.setPosition(_x,_y);

}

Object::~Object()
{

}

Sprite Object::GetSprite() const
{
	return mySprite;
}

float Object::getLeftSide() const
{
	return mySprite.getPosition().x;
}

float Object::getRightSide() const
{
	return mySprite.getPosition().x + mySprite.getLocalBounds().width;
}

float Object::getTopSide() const
{
	return mySprite.getPosition().y;
}

float Object::getBottomSide() const
{
	return mySprite.getPosition().y + mySprite.getLocalBounds().height;
}

int Object::getId()
{
    return _id;
}

bool Object::getSolid() const
{
    return _solid;
}

float Object::getX() const
{
    return _x;
}

float Object::getY() const
{
    return _y;
}

bool Object::isKilled() const
{

	if(_killed)
		return true;
	else
		return false;
}

std::string Object::getEquipe() const
{
	return _equipe;
}

std::string Object::getType() const
{
	return _type;
}

float Object::getLife() const
{
	return 0;
}

void Object::setSolid(bool solid)
{
	_solid = solid;
}

void Object::setEquipe(std::string equipe)
{
	_equipe = equipe;
}

void Object::setX(float x)
{
    _x = x;
}

void Object::setY(float y)
{
    _y = y;
}

void Object::kill()
{
	_killed = true;
}

void Object::deplacementDroiteX()
{
	_x += 3.0f;
    mySprite.setPosition(_x, _y);
}

void Object::deplacementGaucheX()
{
    _x -= 3.0f;
    mySprite.setPosition(_x, _y);
}

void Object::deplacementHautY()
{
    _y -= 3.0f;
    mySprite.setPosition(_x, _y);
}

void Object::deplacementBasY()
{
    _y += 3.0f;
    mySprite.setPosition(_x, _y);
}

void Object::setPosition(float x, float y)
{
	mySprite.setPosition(x, y);
}

void Object::drawObject(sf::RenderWindow & app)
{
	app.draw(mySprite);
}


void Object::setActive(){}

void Object::setNotActive(){}

bool Object::getEstActive(){return true;}

float Object::getClockInt(){return 1;}

void Object::resetClockInt(){}

float Object::getDelai(){return 1;}

bool Object::buttonIsActive(){return true;}

void Object::setOpen(bool){}

bool Object::getOpen(){return true;}

bool Object::getBreakable() const {return false;}

bool Object::getDeadly() const {return false;}

std::string Object::getDirection() const {return "";}
float Object::getInterval() const {return 0.0f;}
bool Object::getIsReady() const {return false;}
float Object::getDecallage() const {return 0.0f;}
float Object::getClock() const {return 0.0f;}
void Object::setReady(bool){}
void Object::resetClock(){}

bool Object::getActive() const {return false;}
void Object::setActive(bool){}

void Object::setDirection(std::string){}

bool Object::deplacement(bool, float){return false;}
float Object::getValeur(){return 0.0f;}

std::string Object::getAmmoType() const {return "";}
