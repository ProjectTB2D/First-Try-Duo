#include "../include/Character.hpp"
#include <iostream>


using namespace sf;
using namespace std;

Character::Character(float x, float y)
:_cs(10.0f), _enDeplacement(false), _destination(0.0f, 0.0f)
{
    _cs.setFillColor(sf::Color::Green);
    _cs.setPosition(x, y);
    cout << "test" << endl;

}


sf::CircleShape Character::getShape()
{
    return _cs;
}
