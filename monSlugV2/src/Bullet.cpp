#include "../include/Bullet.h"
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

Bullet::Bullet(sf::Texture & img, float x, float y, float speed, std::string direction, std::string equipe, std::string type)
: _x(x), _y(y), _speed(speed), _killed(false), _degat(5.0f), _direction(direction), _equipe(equipe), _type(type)
{
        mySprite.setTexture(img);
		//mySprite.Scale(0.7,0.7);
		mySprite.setPosition(_x,_y);


		if(type == "ball"){
        mySprite.setTextureRect(IntRect(0,0,20,20));
        }
        else if(type == "arrow")
        {
            mySprite.setTextureRect(IntRect(20,0,20,10));
        }
        else if(type == "pike")
        {
            mySprite.setTextureRect(IntRect(20,10,20,10));
        }
        else if(type == "a")
        {
            mySprite.setTextureRect(IntRect(0,0,0,0));
        }
        else if(type == "b")
        {
            mySprite.setTextureRect(IntRect(0,0,0,0));
        }
        else if(type == "c")
        {
            mySprite.setTextureRect(IntRect(0,0,0,0));
        }

}

Sprite Bullet::GetSprite() const
{
	return mySprite;
}

float Bullet::getLeftSide() const
{
	return mySprite.getPosition().x;
}

float Bullet::getRightSide() const
{
	return mySprite.getPosition().x + mySprite.getLocalBounds().width;
}

float Bullet::getTopSide() const
{
	return mySprite.getPosition().y;
}

float Bullet::getBottomSide() const
{
	return mySprite.getPosition().y + mySprite.getLocalBounds().height;
}

float Bullet::getX() const
{
    return _x;
}

float Bullet::getY() const
{
    return _y;
}


float Bullet::getSpeed() const
{
    return _speed;
}

bool Bullet::isKilled() const
{

	if(_killed)
		return true;
	else if(_time.getElapsedTime().asSeconds() > 5.5f)
		return true;
	else
		return false;
}

float Bullet::getDegat() const
{
	return _degat;
}

std::string Bullet::getDirection() const
{
	return _direction;
}

std::string Bullet::getEquipe() const
{
	return _equipe;
}

void Bullet::setEquipe(std::string equipe)
{
	_equipe = equipe;
}

void Bullet::setX(float x)
{
    _x = x;
}

void Bullet::setY(float y)
{
    _y = y;
}

void Bullet::setSpeed(float speed)
{
    _speed = speed;
}

void Bullet::kill()
{
	_killed = true;
}

void Bullet::deplacementDroiteX()
{
	_x += _speed;
    mySprite.setPosition(_x, _y);
}

void Bullet::deplacementGaucheX()
{
    _x -= _speed;
    mySprite.setPosition(_x, _y);
}

void Bullet::setPosition(float x, float y)
{
	mySprite.setPosition(x, y);
}

void Bullet::drawBullet(sf::RenderWindow & app)
{
	app.draw(mySprite);
}

std::string Bullet::getType() const
{
	return _type;
}
