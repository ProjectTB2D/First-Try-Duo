#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "../include/Object.h"

class Block : public Object
{
	public:

	Block();
	Block(sf::Texture & img, float, float, bool, std::string, std::string, bool, bool, std::string);

    bool getBreakable() const;
    bool getDeadly() const;
    bool getActive() const;
    std::string getDirection() const;

    void setDirection(std::string);
    void setActive(bool);


	protected:

    bool _isBreakable;
    bool _isDeadly;
    bool _isActive;
    std::string _direction;

};

#endif // BLOCK_H_INCLUDED
