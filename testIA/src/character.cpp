#include "character.hpp"
#include <iostream>


using namespace sf;
using namespace std;

Character::Character(float x, float y)
:_cs(10.0f), _enDeplacement(false), _destination(0.0f, 0.0f)
{
    _cs.setFillColor(sf::Color::Blue);
    _cs.setPosition(x, y);

}


sf::CircleShape & Character::getShape()
{
    return _cs;
}

bool Character::getDeplacement() const
{
    return _enDeplacement;
}

sf::Vector2f Character::getPositionActuelle() const
{
    return _cs.getPosition();
}

sf::Vector2f Character::getDestination() const
{
    return _destination;
}

void Character::setDeplacement(bool dep)
{
    _enDeplacement = dep;
}

void Character::setDestination(sf::Vector2f dest)
{
    _destination = dest;
}



