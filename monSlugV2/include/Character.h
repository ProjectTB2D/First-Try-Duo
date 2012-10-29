#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

class Character
{
	public:

	// Image, x, y, speed
	Character();
	Character(sf::Texture & img, float, float, float, std::string, std::string);

	sf::Sprite GetSprite() const;

	float getLeftSide() const;
	float getMiddleSide() const;
	float getRightSide() const;
	float getTopSide() const;
	float getBottomSide() const;

	float getInitialX() const;
	float getInitialY() const;
	float getInitialSpeed() const;
	float getInitialLife() const;
	bool enSautInitial() const;
	bool surTerreInitial() const;

    void setInitialPosition(float, float);

	float getX() const;
	float getY() const;
	bool getFreeze() const;
	float getSpeed() const;
	float getSpeedY() const;
	bool getSurchauffe() const;
	float getPower() const;
	float getLife() const;
	bool isKilled() const;
	float getCanonX() const;
	float getCanonY() const;
	std::string getDirection() const;
	bool enSaut() const;
	bool surTerre() const;
	std::string getEquipe() const;
	std::string getStrategie() const;
	float getClockFreeze() const;
	float getClockSaut() const;
	float getClockBullet() const;
	bool getDescendre() const;
	bool getDeplacement() const;

	void setDeplacement(bool);
	void setDescendre(bool);
	void setStrategie(std::string);
	void setEquipe(std::string);
	void setEnSaut(bool);
	void setSurTerre(bool);
	void setX(float);
	void setY(float);
	void setFreeze(bool);
	void setSpeed(float);
	void setSpeedY(float);
	void setSurchauffe(bool);
	void setPower(float);
	void setLife(float);
	void downLife(float);
	void upLife(float);

	void freezeTime();
	void teleport();
	void resetClockSaut();
	void resetClockBullet();
	void setDirectionDroite();
	void setDirectionGauche();
	void kill();
	void revive();
	void deplacementBasY();
	void deplacementDroiteX();
	void deplacementGaucheX();
	void deplacement();
	void saut();
	void setPosition();
	void shootAnimation();
	void notShooting();
	void drawPlayer(sf::RenderWindow &);

	void setScore(int);
	int getScore() const;

    void setMouvementGauche(bool);
	void setMouvementDroite(bool);

	bool getMouvementGauche() const;
	bool getMouvementDroite() const;

	protected:
		sf::Texture myImage;
		sf::Sprite mySprite;
		sf::Clock _clockSaut;
		sf::Clock _clockBullet;
		sf::Clock _clockFreeze;
		sf::Clock _clockAnimLateral;
		sf::Clock _clockAnimArret, _clockAnimArret2;

        float _x, _y;
		float _speed, _speedY, _speedMax;
        float _life, _power;
        bool _surchauffe;
        bool _freeze;
        bool _killed;

		std::string _direction;

		bool _surTerre;
		bool _enSaut;
		std::string _equipe;
        std::string _strategie;
        bool _descendre;
        float _xInitial, _yInitial;
        float _speedInitial;
        float _lifeInitial;
		bool _surTerreInitial;
        bool _enSautInitial;
        bool _enDeplacement;

		float _canonX;
		float _canonY;

		int _score;

		bool _mouvementGauche, _mouvementDroite;
		bool _shooting;


};

#endif
