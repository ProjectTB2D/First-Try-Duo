#ifndef _included_NPC_h
#define _included_NPC_h

#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Item.h"

#define HEAL_RADIUS 20

enum npc_type{NPC_SCOUT, NPC_SOLDIER, NPC_MEDIC, NPC_CYBORG};

enum npc_action{ACT_IDLE,
                ACT_COLLECTING,
                ACT_DEF_PLAYER,
                ACT_DEF_HQ,
                ACT_ATK_ENEMY,
                ACT_ATK_BUILD,
                ACT_TAKING_DROP};

class NPC : public Actor
{

 public:

    NPC(const Actor&, npc_type = NPC_SCOUT);
    ~NPC();

 	void render();
	void update();

	Actor*    getTarget();
	void      setTarget(Actor*);

 protected:

    npc_type    _type;
    npc_action  _action;
    Actor*      _target;

    bool        _strafLeft;
    sf::Clock   _LOSTimer;
    sf::Clock   _strafTimer;

};
#endif
