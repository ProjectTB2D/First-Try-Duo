#ifndef _included_player_h
#define _included_player_h

#include <SFML/Graphics.hpp>
#include "Actor.h"

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

float   _leftAngle;

};


#endif
