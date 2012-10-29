#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "../include/Character.h"

class Player : public Character
{
	public:

	Player();
	Player(sf::Texture & img, float, float, float, std::string, std::string);


	protected:

};

#endif
