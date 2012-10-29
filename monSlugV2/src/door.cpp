#include "../include/Door.h"
#include <cmath>
#include <iostream>


using namespace sf;
using namespace std;


Door::Door(sf::Texture & img, float x, float y, bool isOpen, std::string equipe, std::string type, bool solid, Object * button)
: Object(img, x, y, equipe, type, solid), _isOpen(isOpen), _button(button)
{
    if(isOpen)
        mySprite.setTextureRect(IntRect(0,0,50,200));
    else
        mySprite.setTextureRect(IntRect(50,0,50,200));
}

void Door::setOpen(bool open)
{
    _isOpen = open;

    if(_isOpen){
        _solid = false;
        mySprite.setTextureRect(IntRect(0,0,50,200));
    }
    else{
        _solid = true;
        mySprite.setTextureRect(IntRect(50,0,50,200));
    }
}

bool Door::getOpen() const
{
    return _isOpen;
}

bool Door::buttonIsActive()
{
    if(_button->getEstActive()){
        //cout << "actif" << endl;
        return true;
    }
    else{
        //cout << "pas actif" << endl;
        return false;
    }
}






