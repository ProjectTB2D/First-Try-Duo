#ifndef _included_player_h
#define _included_player_h

#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Item.h"

class Player : public Actor
{

 public:

    Player();
    Player(const Actor&);
    ~Player();

	virtual void render();
	virtual void update();


    // action

    void moveForward();
    void aim();
    void strafL();
    void strafR();


 protected:

sf::Clock   _clock_use;
bool        _menu;



};


#endif
