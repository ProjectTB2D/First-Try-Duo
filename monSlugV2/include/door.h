#ifndef DOOR_H_INCLUDED
#define DOOR_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "../include/Object.h"

class Door : public Object
{
	public:

	Door();
	Door(sf::Texture & img, float, float, bool, std::string, std::string, bool, Object * button);

    void setOpen(bool);
    bool getOpen() const;
    bool buttonIsActive();

	protected:

    bool _isOpen;
    Object* _button;


};

#endif // DOOR_H_INCLUDED
