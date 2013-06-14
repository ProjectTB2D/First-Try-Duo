#ifndef _included_Ent_h
#define _included_Ent_h
#include <SFML/Graphics.hpp>

class Entity
{
 public:

	Entity();
	Entity(int, sf::Vector2f, sf::Vector2f, sf::Vector2f); // int passé a l'image manager
    virtual ~Entity() = 0;

	// ???

	virtual void render() = 0;
	virtual bool update() = 0;

	// getter

	float 			getFrameH() const;
	float 			getFrameW() const;
	sf::Vector2f 	getPos() const;
	sf::Sprite*		getSpr();
	unsigned int 	getID() const;
	float 			getAngle() const;
	bool			getKilled() const;

	// setter

	void			setPos(sf::Vector2f&);
	void 			setSpr(int);
	void			setFrame(sf::Vector2f&);
	void			setAngle(float);
	void			kill();


 protected:

	sf::Sprite _spr;
	unsigned int _id;
	float _frameH;
	float _frameW;
	float _angle;

	bool _killed;

};
#endif
