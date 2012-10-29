#ifndef LAUNCHER_H_INCLUDED
#define LAUNCHER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "../include/Object.h"

class Launcher : public Object
{
	public:

	Launcher();
	Launcher(sf::Texture & img, float, float, std::string, std::string, bool, std::string, float, float, std::string);

    std::string getDirection() const;
    float getInterval() const;
    bool getIsReady() const;
    float getDecallage() const;
    float getClock() const;

    void setReady(bool);
    void resetClock();

    std::string getAmmoType() const;

	protected:

    std::string _direction;
    float _interval;
    bool _isReady;
    float _decallage;
    sf::Clock _clockLauncher;
    std::string _ammoType;

};

#endif // LAUNCHER_H_INCLUDED
