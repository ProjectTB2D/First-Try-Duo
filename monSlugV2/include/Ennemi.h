#ifndef ENNEMI_H
#define ENNEMI_H

#include <SFML/Graphics.hpp>
#include "../include/Character.h"

class Ennemi : public Character
{
	public:

	Ennemi();
	Ennemi(sf::Texture & img, float, float, float, std::string, std::string);

	private:

};

#endif
