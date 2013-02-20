#ifndef _included_team_hpp
#define _included_team_hpp

#include <list>

#define MAXNPC 10

class Player;
class NPC;
class Bullet;
class Crafter;

struct team{

    int id;
    Player * p;
    NPC * ai[MAXNPC];
    std::list<Bullet> proj;
    //HQ base;
    Crafter* crafter;

};
#endif
