#include "../include/Character.h"
#include <cmath>
#include <iostream>


using namespace sf;
using namespace std;


Character::Character()
: _x(100), _y(200), _speed(200), _speedY(0), _speedMax(1000), _life(100.0f), _power(100.0f), _surchauffe(false), _freeze(false), _killed(false), _direction("droite"), _surTerre(false),
_enSaut(false), _equipe("bleu"), _strategie("normal"), _descendre(false), _xInitial(100), _yInitial(200), _speedInitial(6), _lifeInitial(100.0f),
_surTerreInitial(false),_enSautInitial(false), _enDeplacement(false), _score(0), _mouvementGauche(false), _mouvementDroite(false), _shooting(false)
{
	if (!myImage.loadFromFile("images/samus.png")) // Si le chargement a échoué
    {
        cerr<<"Erreur durant le chargement de l'image"<<endl;
    }
    else // Si le chargement de l'image a réussi
    {
        mySprite.setTexture(myImage);
		//mySprite.Scale(0.7,0.7);
		mySprite.setPosition(_x,_y);
    }
}

Character::Character(sf::Texture & img, float x, float y, float speed, std::string equipe, std::string strategie)
: _x(x), _y(y), _speed(speed), _speedY(0), _speedMax(600), _life(100.0f), _power(100.0f), _surchauffe(false), _freeze(false), _killed(false), _direction("droite"), _surTerre(false),
_enSaut(false), _equipe(equipe), _strategie(strategie), _descendre(false), _xInitial(x), _yInitial(y), _speedInitial(speed), _lifeInitial(100.0f),
_surTerreInitial(false),_enSautInitial(false), _enDeplacement(false), _score(0), _mouvementGauche(false), _mouvementDroite(false), _shooting(false)
{
    mySprite.setTexture(img);
	//mySprite.SetSubRect(IntRect(0,150,50,225));
	//mySprite.scale(2,2);
	mySprite.setPosition(_x,_y);

}

Sprite Character::GetSprite() const
{
	return mySprite;
}

float Character::getLeftSide() const
{
	return _x;
	//return mySprite.GetPosition().x;
}

float Character::getMiddleSide() const
{
	return _x + (mySprite.getLocalBounds().width /2);
}

float Character::getRightSide() const
{
	return _x + mySprite.getLocalBounds().width;
	//return mySprite.GetPosition().x + mySprite.GetSize().x;
}

float Character::getTopSide() const
{
	return _y;
	//return mySprite.GetPosition().y;
}

float Character::getBottomSide() const
{
	return _y + mySprite.getLocalBounds().height;
	//return mySprite.GetPosition().y + mySprite.GetSize().y;
}

float Character::getInitialX() const
{
	return _xInitial;
}

float Character::getInitialY() const
{
	return _yInitial;
}


float Character::getInitialSpeed() const
{
    return _speedInitial;
}

float Character::getInitialLife() const
{
	return _lifeInitial;
}

bool Character::enSautInitial() const
{
	return _enSautInitial;
}


bool Character::surTerreInitial() const
{
    return _surTerreInitial;
}

void Character::setInitialPosition(float x, float y)
{
    _xInitial = x;
    _yInitial = y;
}

float Character::getX() const
{
	return _x;
}

float Character::getY() const
{
	return _y;
}

bool Character::getFreeze() const
{
    return _freeze;
}

float Character::getSpeed() const
{
    return _speed;
}

float Character::getSpeedY() const
{
    return _speedY;
}

bool Character::getSurchauffe() const
{
    return _surchauffe;
}

float Character::getPower() const
{
    return _power;
}

float Character::getLife() const
{
    return _life;
}

bool Character::isKilled() const
{

	if(_killed)
		return true;
	else if(_life <= 0.0f)
		return true;
	else
		return false;
}

float Character::getCanonX() const
{
	return _canonX;
}

float Character::getCanonY() const
{
	return _canonY;
}

std::string Character::getDirection() const
{
	return _direction;
}

bool Character::enSaut() const
{
	return _enSaut;
}

bool Character::surTerre() const
{
	return _surTerre;
}

std::string Character::getEquipe() const
{
	return _equipe;
}

std::string Character::getStrategie() const
{
	return _strategie;
}

float Character::getClockFreeze() const
{
	return _clockFreeze.getElapsedTime().asSeconds();
}

float Character::getClockSaut() const
{
	return _clockSaut.getElapsedTime().asSeconds();
}

float Character::getClockBullet() const
{
	return _clockBullet.getElapsedTime().asSeconds();
}

bool Character::getDescendre() const
{
	return _descendre;
}

bool Character::getDeplacement() const
{
	return _enDeplacement;
}

void Character::setDeplacement(bool depl)
{
	_enDeplacement = depl;

}

void Character::setDescendre(bool desc)
{
	_descendre = desc;
}

void Character::setStrategie(std::string strategie)
{
	_strategie = strategie;
}

void Character::setEquipe(std::string equipe)
{
	_equipe = equipe;
}

void Character::setEnSaut(bool enSaut)
{
    _enSaut = enSaut;
}

void Character::setSurTerre(bool surTerre)
{
    _surTerre = surTerre;
}

void Character::setX(float x)
{
    _x = x;
}

void Character::setY(float y)
{
    _y = y;
}

void Character::setFreeze(bool freeze)
{
    _freeze = freeze;
}

void Character::setSpeed(float speed)
{
    _speed = speed;
}

void Character::setSpeedY(float speed)
{
    _speedY = speed;
}

void Character::setSurchauffe(bool surchauffe)
{
    _surchauffe = surchauffe;
}

void Character::setPower(float power)
{
    _power = power;
}

void Character::setLife(float life)
{
    _life = life;
}

void Character::downLife(float life)
{
    _life -= life;
}

void Character::freezeTime(){

	if(_power > 20.0f && !_freeze && !_surchauffe){
		_power -= 20.0f;
		_freeze = true;
		_speedY = 0;
		_clockFreeze.restart();

		if(_speed > 200.0f)
			_speed = 200.0f;

		else if(_speed < -200.0f)
			_speed = -200.0f;
	}
}

void Character::teleport()
{
	if(_power > 0.0f){
		if(_direction == "droite"){

			_speed += 3000.0f;
			//_x += 25.0f;
			//mySprite.SetPosition(_x, _y);

		}
		else if(_direction == "gauche"){

			_speed -= 3000.0f;
			//_x -= 25.0f;
			//mySprite.SetPosition(_x, _y);
		}

		if(_speed > 3000.0f)
			_speed = 3000.0f;
		else if(_speed < -3000.0f)
			_speed = -3000.0f;

		_power -= 1.0f;

		if(_power < 5.0f)
			_surchauffe = true;

	}
	else if(_power <= 0){

		_power = 0;

	}
}

void Character::resetClockSaut()
{
	_clockSaut.restart();
}

void Character::resetClockBullet()
{
	_clockBullet.restart();
}

void Character::upLife(float life)
{
    _life += life;
}

void Character::setDirectionGauche()
{
	_direction = "gauche";
}

void Character::setDirectionDroite()
{
	_direction = "droite";
}

void Character::kill()
{
	_killed = true;
}

void Character::revive()
{
	_killed = false;
}

void Character::deplacementBasY()
{
	_y += 500.0f;
    mySprite.setPosition(_x, _y);
}

void Character::deplacementDroiteX()
{
    if(_speed < -1000){
        _speed += 300.0f;
    }
	else if(_speed < 0){
		_speed += 45.0f;
	}
	else if(_surTerre){

		if(_speed > (_speedMax + 100.0f))
				_speed -= 100.0f;
		else{
			if(_speed < _speedMax)
				_speed += 30.0f;

		}

	}
	else if(!_surTerre){

		if(_speed > (_speedMax + 500.0f))
				_speed -= 200.0f;
		else{
			if(_speed < _speedMax + 300.0f)
				_speed += 30.0f;
		}
	}

}

void Character::deplacementGaucheX()
{
	if(_speed > 1000){
        _speed -= 300.0f;
    }
	else if(_speed > 0){
		_speed -= 45.00f;
	}
	else if(_surTerre){

		if(_speed < (-_speedMax - 100.0f))
				_speed += 100.0f;
		else{
			if(_speed > -_speedMax)
				_speed -= 30.0f;
		}

	}
	else if(!_surTerre){

		if(_speed < (-_speedMax - 500.0f))
				_speed += 200.0f;
		else{
			if(_speed > -_speedMax - 300.0f)
				_speed -= 30.0f;
		}
	}

}

void Character::deplacement()
{

	_x += _speed;
    mySprite.setPosition(_x, _y);

}

void Character::saut()
{
	_y -= _speedY;
	mySprite.setPosition(_x, _y);
}

void Character::setPosition()
{
	mySprite.setPosition(_x, _y);
}

void Character::shootAnimation()
{
    _clockAnimArret.restart();
    _shooting = true;
}

void Character::notShooting()
{
    _shooting = false;
}

void Character::drawPlayer(sf::RenderWindow & app)
{
    if(_enDeplacement)
    {

        _clockAnimArret.restart();

        if(_mouvementDroite)
        {
            if(_clockAnimLateral.getElapsedTime().asSeconds() > 0.1f)
            {
                _clockAnimLateral.restart();
            }
            else if(_clockAnimLateral.getElapsedTime().asSeconds() < 0.05f)
            {
                mySprite.setTextureRect(IntRect(100,150,50,75));

            }
            else if(_clockAnimLateral.getElapsedTime().asSeconds() > 0.05f)
            {
                mySprite.setTextureRect(IntRect(50,150,50,75));
            }

            //mySprite.FlipX(false);
        }
        else if(_mouvementGauche)
        {
            if(_clockAnimLateral.getElapsedTime().asSeconds() > 0.1f)
            {
                _clockAnimLateral.restart();
            }
            else if(_clockAnimLateral.getElapsedTime().asSeconds() < 0.05f)
            {
                mySprite.setTextureRect(IntRect(100,250,50,75));

            }
            else if(_clockAnimLateral.getElapsedTime().asSeconds() > 0.05f)
            {
                mySprite.setTextureRect(IntRect(50,250,50,75));
            }

            //mySprite.FlipX(true);
        }

    }
    else
	{

        _clockAnimLateral.restart();

        if(_surTerre)
        {

            if(_clockAnimArret.getElapsedTime().asSeconds() < 1.5f)
            {

                if(_direction == "droite")
                {
                    mySprite.setTextureRect(IntRect(0,150,50,75));
                    //mySprite.FlipX(false);

                }
                else if(_direction == "gauche")
                {
                    mySprite.setTextureRect(IntRect(0,250,50,75));
                    //mySprite.FlipX(true);
                }
            }
            else
            {

                //mySprite.FlipX(false);

                if(_clockAnimArret2.getElapsedTime().asSeconds() > 3.0f)
                {
                    _clockAnimArret2.restart();
                }
                else if(_clockAnimArret2.getElapsedTime().asSeconds() < 0.75f)
                {
                    mySprite.setTextureRect(IntRect(0,50,50,75));
                }
                else if(_clockAnimArret2.getElapsedTime().asSeconds() < 1.50f)
                {
                    mySprite.setTextureRect(IntRect(50,50,50,75));
                }
                else if(_clockAnimArret2.getElapsedTime().asSeconds() < 2.25f)
                {
                    mySprite.setTextureRect(IntRect(0,50,50,75));
                }
                else if(_clockAnimArret2.getElapsedTime().asSeconds() < 3.0f)
                {
                    mySprite.setTextureRect(IntRect(100,50,50,75));
                }

              /*  if(_anClock.GetElapsedTime() > 0.1){

                    _anClock.Reset();

                    _an = (_an > 6) ? 0 : _an;

                    switch(_an){

                    case 0 : _spr_main.SetSubRect(sf::IntRect(0,0,60,50));break;
                    case 1 : _spr_main.SetSubRect(sf::IntRect(0,50,60,100));break;
                    case 2 : _spr_main.SetSubRect(sf::IntRect(0,100,60,150));break;
                    case 3 : _spr_main.SetSubRect(sf::IntRect(0,150,60,200));break;
                    case 4 : _spr_main.SetSubRect(sf::IntRect(0,200,60,250));break;
                    case 5 : _spr_main.SetSubRect(sf::IntRect(0,250,60,300));break;
                    case 6 : _spr_main.SetSubRect(sf::IntRect(0,300,60,350));break;
                    default : _spr_main.SetSubRect(sf::IntRect(0,0,60,50));

                    }

                    ++_an;

                }*/



            }
        }
        else
        {
            if(!_enSaut && !_shooting)
            {
                //mySprite.FlipX(false);

                mySprite.setTextureRect(IntRect(150,50,50,75));
            }
            else
            {
               _clockAnimArret.restart();
            }

        }
	}

	app.draw(mySprite);
}

void Character::setScore(int score)
{
    _score = score;
}

int Character::getScore() const
{
    return _score;
}

void Character::setMouvementGauche(bool mvt)
{
    _mouvementGauche = mvt;
}

void Character::setMouvementDroite(bool mvt)
{
    _mouvementDroite = mvt;
}

bool Character::getMouvementGauche() const
{
    return _mouvementGauche;
}

bool Character::getMouvementDroite() const
{
    return _mouvementDroite;
}








