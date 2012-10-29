#ifndef REWARD_H_INCLUDED
#define REWARD_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "../include/Object.h"

class Reward : public Object
{
	public:

	Reward();
	Reward(sf::Texture & img, float, float, std::string, std::string, bool, float, float);

    bool deplacement(bool, float);

    float getValeur();

	protected:

    float _valeur;
    float _vitesseX, _vitesseY;
    int _compteurSaut;

};

#endif // REWARD_H_INCLUDED
