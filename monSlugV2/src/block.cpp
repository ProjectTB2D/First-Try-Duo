#include "../include/block.h"
#include <cmath>
#include <iostream>


using namespace sf;
using namespace std;


Block::Block(sf::Texture & img, float x, float y, bool isBreakable, std::string equipe, std::string type, bool solid, bool isDeadly, std::string direction)
: Object(img, x, y, equipe, type, solid), _isBreakable(isBreakable), _isDeadly(isDeadly), _isActive(false), _direction(direction)
{
    if(type == "tileTerre"){
        mySprite.setTextureRect(IntRect(100,0,50,50));
    }
    else if(type == "tilePique")
    {
        if(direction == "haut"){

            mySprite.setTextureRect(IntRect(350,0,50,50));

        }else if(direction == "bas"){

            mySprite.setTextureRect(IntRect(300,50,50,50));

        }else if(direction == "droite"){

            mySprite.setTextureRect(IntRect(350,50,50,50));

        }else if(direction == "gauche"){

            mySprite.setTextureRect(IntRect(400,50,50,50));

        }
    }
    else if(type == "checkpoint")
    {
        mySprite.setTextureRect(IntRect(0,0,50,125));
    }
    else if(type == "blockPique")
    {
        mySprite.setTextureRect(IntRect(0,50,50,50));
    }
    else if(type == "")
    {

    }

}

bool Block::getBreakable() const
{
    return _isBreakable;
}

bool Block::getDeadly() const
{
    return _isDeadly;
}

bool Block::getActive() const
{
    return _isActive;
}

std::string Block::getDirection() const
{
    return _direction;
}

void Block::setDirection(std::string direction)
{
    _direction = direction;

}

void Block::setActive(bool active)
{
    _isActive = active;

    if(active)
        mySprite.setTextureRect(IntRect(50,0,50,125));
    else
        mySprite.setTextureRect(IntRect(0,0,50,125));
}
