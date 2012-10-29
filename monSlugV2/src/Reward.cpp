#include "../include/Reward.h"
#include <cmath>
#include <iostream>


using namespace sf;
using namespace std;


Reward::Reward(sf::Texture & img, float x, float y, std::string equipe, std::string type, bool solid, float valeur, float vitesse)
: Object(img, x, y, equipe, type, solid), _valeur(valeur), _vitesseX(vitesse), _vitesseY(0), _compteurSaut(0)
{
    if(type == "tileTerre"){
        mySprite.setTextureRect(IntRect(100,0,50,50));
    }
    else if(type == "tilePique")
    {
        mySprite.setTextureRect(IntRect(350,0,50,50));
    }
    else if(type == "")
    {

    }
    else
    {
        mySprite.setTextureRect(IntRect(20,0,20,20));
    }

}

bool Reward::deplacement(bool collision, float frameTime)
{

    if(collision)
    {
        if(_compteurSaut < 4)
        {
            _vitesseY = std::abs(_vitesseY) * 2 / 3 ;
            //_vitesseY = 500.0f;

            _compteurSaut++;
        }
        else
        {
            _vitesseY = 0.0f;
        }

    }
    else
    {
        _vitesseY -= 5.0f;

        if(_vitesseY < -500.0f)
            _vitesseY = -500.0f;
    }

    if(_vitesseX < 0)
    {
        _vitesseX += 0.5f;

        if(_vitesseX > 0)
            _vitesseX = 0;

        if(_compteurSaut > 2)
            _vitesseX = 0;
    }
    else if(_vitesseX > 0)
    {
        _vitesseX -= 0.5f;

        if(_vitesseX < 0)
            _vitesseX = 0;

        if(_compteurSaut > 2)
            _vitesseX = 0;
    }

    _x += (_vitesseX * frameTime);
    _y -= (_vitesseY * frameTime);

    mySprite.setPosition(_x, _y);


    return false;

}

float Reward::getValeur()
{
    return _valeur;
}









