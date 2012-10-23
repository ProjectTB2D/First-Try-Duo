#include "Character.hpp"
#include <iostream>


using namespace sf;
using namespace std;

Character::Character(float x, float y)
:_cs(10.0f), _enDeplacement(false), _destination(0.0f, 0.0f), _inObstacle(false)
{
    _cs.setFillColor(sf::Color::Blue);
    _cs.setPosition(x, y);
    _cs.setOrigin((_cs.getLocalBounds().width / 2), (_cs.getLocalBounds().height / 2));

}


sf::CircleShape & Character::getShape()
{
    return _cs;
}

sf::FloatRect Character::getRect() const
{
    sf::FloatRect box(_cs.getPosition().x, _cs.getPosition().y, _cs.getLocalBounds().width, _cs.getLocalBounds().height);

    return box;
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

    if(_listDestination.size() > 0)
    {
        return _listDestination[_listDestination.size() - 1]; // Sa destination sera toujours le dernier element
    }
    else
    {
        sf::Vector2f dest(0.0f, 0.0f);
        return dest;
    }
}

bool Character::getInObstacle() const
{
    return _inObstacle;
}

int Character::getNbDestination() const
{
    return _listDestination.size();
}

void Character::setInObstacle(bool obs)
{
    _inObstacle = obs;
}

void Character::setDeplacement(bool dep)
{
    _enDeplacement = dep;
}

void Character::setDestination(sf::Vector2f dest)
{
    for(int i = 0; i < _listDestination.size(); i++)
    {
        _listDestination.pop_back();
    }

    _listDestination.push_back(dest);
}

void Character::ajoutDest(sf::Vector2f dest)
{
    _listDestination.push_back(dest);
}

void Character::destinationSuivante()
{
    if(_listDestination.size() >= 1)
        _listDestination.pop_back();
}






