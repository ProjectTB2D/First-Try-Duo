#ifndef INTERRUPTEUR_H_INCLUDED
#define INTERRUPTEUR_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "../include/Object.h"

class Interrupteur : public Object
{
	public:

	Interrupteur();
	Interrupteur(sf::Texture & img, float, float, bool, float, std::string, std::string, bool, int id = 0);

    void setActive();
    void setNotActive();
    bool getEstActive();
    float getClockInt();
    void resetClockInt();
    float getDelai();

	protected:

    sf::Clock _clockDesactivation;
    bool _estActive;
    float _delai;


};

#endif // INTERRUPTEUR_H_INCLUDED
