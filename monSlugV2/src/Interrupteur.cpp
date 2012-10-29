#include "../include/Interrupteur.h"
#include <cmath>
#include <iostream>


using namespace sf;
using namespace std;


Interrupteur::Interrupteur(sf::Texture & img, float x, float y, bool estActive, float temps, std::string equipe, std::string type, bool solid, int id)
: Object(img, x, y, equipe, type, solid, id), _estActive(estActive), _delai(temps)
{
    if(!estActive)
        mySprite.setTextureRect(IntRect(0,0,50,75));
    else
        mySprite.setTextureRect(IntRect(50,0,50,75));
}

void Interrupteur::setActive()
{
    if(!_estActive){

        _estActive = true;
        mySprite.setTextureRect(IntRect(50,0,50,75));
    }
}

void Interrupteur::setNotActive()
{
    if(_estActive){

        _estActive = false;
        mySprite.setTextureRect(IntRect(0,0,50,75));
    }
}

bool Interrupteur::getEstActive()
{

    return _estActive;
}

float Interrupteur::getClockInt()
{
    return _clockDesactivation.getElapsedTime().asSeconds();
}

void Interrupteur::resetClockInt()
{
    _clockDesactivation.restart();
}

float Interrupteur::getDelai()
{
    return _delai;
}



