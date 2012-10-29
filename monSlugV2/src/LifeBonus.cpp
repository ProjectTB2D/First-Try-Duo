#include "../include/LifeBonus.h"
#include <cmath>
#include <iostream>


using namespace sf;
using namespace std;


LifeBonus::LifeBonus(sf::Texture & img, float x, float y, std::string equipe, std::string type, bool solid)
: Object(img, x, y, equipe, type, solid), _life(25.0f)
{

}

float LifeBonus::getLife() const
{
	return _life;
}
