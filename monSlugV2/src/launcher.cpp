#include "../include/launcher.h"
#include <cmath>
#include <iostream>


using namespace sf;
using namespace std;


Launcher::Launcher(sf::Texture & img, float x, float y, std::string equipe, std::string type, bool solid, std::string direction,
                   float interval, float decallage, std::string ammoType)
: Object(img, x, y, equipe, type, solid), _direction(direction), _interval(interval), _isReady(false), _decallage(decallage),
_ammoType(ammoType)
{
    if((type == "launcher") && (direction == "gauche"))
    {
        mySprite.setTextureRect(IntRect(400,0,50,50));
    }
    else if((type == "launcher") && (direction == "droite"))
    {
        mySprite.setTextureRect(IntRect(450,0,50,50));
    }
    else if((type == "launcher") && (direction == "haut"))
    {
        mySprite.setTextureRect(IntRect(100,0,50,50));
    }
    else if((type == "launcher") && (direction == "bas"))
    {
        mySprite.setTextureRect(IntRect(100,0,50,50));
    }

}

std::string Launcher::getDirection() const
{
    return _direction;
}

float Launcher::getInterval() const
{
    return _interval;
}

bool Launcher::getIsReady() const
{
    return _isReady;
}

float Launcher::getDecallage() const
{
    return _decallage;
}

float Launcher::getClock() const
{
    return _clockLauncher.getElapsedTime().asSeconds();
}

void Launcher::setReady(bool ready)
{
    _isReady = ready;
}

void Launcher::resetClock()
{
    _clockLauncher.restart();
}

std::string Launcher::getAmmoType() const
{
    return _ammoType;
}






