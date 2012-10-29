#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

class Object
{
	public:
	// Image, x, y, speed
	Object(sf::Texture & img, float, float, std::string equipe, std::string type, bool, int id = 0);
    ~Object();

	sf::Sprite GetSprite() const;

	float getLeftSide() const;
	float getRightSide() const;
	float getTopSide() const;
	float getBottomSide() const;

    int getId();
    bool getSolid() const;
	float getX() const;
	float getY() const;
	bool isKilled() const;
	std::string getEquipe() const;
	std::string getType() const;
	virtual float getLife() const;
	virtual bool getEstActive();

    void setSolid(bool);
	void setEquipe(std::string);
	void setX(float);
	void setY(float);
	void kill();

    virtual void setActive();
    virtual void setNotActive();
	void deplacementDroiteX();
	void deplacementGaucheX();
	void deplacementHautY();
	void deplacementBasY();
	void setPosition(float, float);
	void drawObject(sf::RenderWindow &);

	virtual float getClockInt();
	virtual void resetClockInt();
	virtual float getDelai();

    virtual bool buttonIsActive();
	virtual void setOpen(bool);
	virtual bool getOpen();

    virtual bool getBreakable() const;
    virtual bool getDeadly() const;

    virtual std::string getDirection() const;
    virtual float getInterval() const;
    virtual bool getIsReady() const;
    virtual float getDecallage() const;
    virtual float getClock() const;
    virtual void setReady(bool);
    virtual void resetClock();

    virtual bool getActive() const;
    virtual void setActive(bool);

    virtual void setDirection(std::string);

    virtual bool deplacement(bool, float);
    virtual float getValeur();

    virtual std::string getAmmoType() const;

	protected:
		sf::Sprite mySprite;


        float _x, _y;
        bool _killed;
		std::string _equipe;
        std::string _type;
        bool _solid;
        int _id;
};

#endif
