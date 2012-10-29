#include "../include/Player.h"
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

Player::Player()
: Character()
{

}

Player::Player(sf::Texture & img, float x, float y, float speed, std::string equipe, std::string strategie)
: Character(img, x, y, speed, equipe, strategie)
{

}
