#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet
{

	public:
	// Image, x, y, speed
	Bullet(sf::Texture & img, float, float, float, std::string direction, std::string equipe, std::string type);

	sf::Sprite GetSprite() const;

	float getLeftSide() const;
	float getRightSide() const;
	float getTopSide() const;
	float getBottomSide() const;

	float getX() const;
	float getY() const;
	float getSpeed() const;
	bool isKilled() const;
	float getDegat() const;
	std::string getDirection() const;
	std::string getEquipe() const;

	void setEquipe(std::string);
	void setX(float);
	void setY(float);
	void setSpeed(float);
	void kill();

	void deplacementDroiteX();
	void deplacementGaucheX();
	void setPosition(float, float);
	void drawBullet(sf::RenderWindow &);

	std::string getType() const;

    protected:
//		sf::Image myImage;
		sf::Sprite mySprite;
		sf::Clock _time;
        float _x, _y;
        float _speed;
        bool _killed;
        float _degat;
        std::string _direction;
		std::string _equipe;
		std::string _type;

};

#endif
