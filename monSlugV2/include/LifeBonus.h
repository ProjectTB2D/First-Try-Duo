#ifndef LIFEBONUS_HPP
#define LIFEBONUS_HPP

#include <SFML/Graphics.hpp>
#include "../include/Object.h"

class LifeBonus : public Object
{
	public:

	LifeBonus();
	LifeBonus(sf::Texture & img, float, float, std::string, std::string, bool);

	float getLife() const;


	private:

	float _life;

};

#endif
