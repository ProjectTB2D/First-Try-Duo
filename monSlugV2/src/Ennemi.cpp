#include "../include/Ennemi.h"
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

Ennemi::Ennemi()
: Character()
{

}

Ennemi::Ennemi(sf::Texture & img, float x, float y, float speed, std::string equipe, std::string strategie)
: Character(img, x, y, speed, equipe, strategie)
{

}
