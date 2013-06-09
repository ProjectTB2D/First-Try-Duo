#ifndef _included_NPC_h
#define _included_NPC_h

#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Item.h"
#include "HQ.h"

#define HEAL_RADIUS 20

enum npc_type{NPC_SCOUT, NPC_SOLDIER, NPC_MEDIC, NPC_CYBORG};

enum npc_action{ACT_IDLE,
                ACT_COLLECTING,
                ACT_CRAFT,
                ACT_DEF_PLAYER,
                ACT_DEF_HQ,
                ACT_ATK_ENEMY,
                ACT_ATK_BUILD,
                ACT_TAKING_DROP};

class NPC : public Actor
{

 public:

    NPC(const Actor&, npc_type = NPC_SOLDIER);
    ~NPC();

 	void render();
	void update();

	Actor*    getTarget();
	void      setTarget(Actor*);

	void      dotest();

    Item*     getBestWeapon();
    Item*     getWeakestWeapon();

    bool      search();

	// ORDERS ...

    RessourceSpawner* ai_get_spawner(const Item_t&);    // npc recherche spawner plus proche
    Drop* ai_chose_spawner_drop();                      // npc choisit drop sur spawner
    bool ai_get_drop(Drop*);                      // npc ramasse le drop
    bool ai_move();                         // npc bouge position paramètre
    void ai_drop();                                     // npc drop item en main
    //Item_t ai_chose_craft();
    void ai_craft(Item_t);
    bool ai_alloc();
    bool ai_take_drop();


 protected:

    npc_type    _type;
    npc_action  _action;
    npc_action  _prev_act;
    Actor*      _target;

    bool        _strafLeft;
    sf::Clock   _LOSTimer;
    sf::Clock   _strafTimer;
    sf::Clock   _checkWeapon;
    float       _straf_time;

    sf::Vector2f _destination;
    RessourceSpawner* _rs;
    bool              _freeStyle;
    Item_t            _weap_craft;
    Item_t            _ress;

    int               _alloc;

};
#endif
