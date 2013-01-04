#include <fstream>
#include "Core.h"
#include "global.h"
#include "World.h"




World::World()
: _nextUniqueID(0)
{


}

int World::generateUniqueID() {


    return ++_nextUniqueID;


}

void World::createWorld(const char* lvlname){


}

void World::createPlayer() {



}




void World::update(){

}

//////////////////////////////////////////////////////////////// PURGE THE UNDEAD //////////////////////////////////////////////////////////////////////////:

void World::disolve_dead_bullet(){


}

void World::disolve_dead_NPC(){


}

void World::disolve_dead_drop(){

}


///////////////////////////////////////////////////////////////////// RENDER ///////////////////////////////////////////////////////////////////////////

void World::render(){


}


void World::renderWorld() {


}


void World::centerCamera() {

//g_core->getView()->setCenter(getPlayer()->getPos());

}

void World::disolve(){

        ////////////////////////////////////
  //          PURGE                 //
  ////////////////////////////////////

  disolve_dead_drop();
disolve_dead_NPC();
disolve_dead_bullet();



}

///////////////////////////////////////////////////////////// EPURAGE /////////////////////////////////////////////////////////////////////////////////////////


bool World::insideScreen(int x, int y, int w, int h, int margin) const
{
    //v2d_t cam = level_editmode() ? editor_camera : camera_get_position();
    float a[4] = { x, y, x+w, y+h };
    float b[4] = {
        g_core->getView()->getCenter().x - g_core->getWinSize().x/2 - margin,
        g_core->getView()->getCenter().y - g_core->getWinSize().y/2 - margin,
        g_core->getView()->getCenter().x + g_core->getWinSize().x/2 + margin,
        g_core->getView()->getCenter().y + g_core->getWinSize().y/2 + margin
    };


    //sf::Shape rect(sf::Shape::Rectangle(b[0],b[1],b[2],b[3],sf::Color::Blue,3,sf::Color::Blue));
    //rect.EnableFill(false);
    //g_core->getApp()->Draw(rect);

    return g_core->bounding_box(a,b);
}


 Player*         World::getPlayerTeam1(){return NULL;}
 Player*         World::getPlayerTeam2(){return NULL;}

 team*   World::getTeam1(){return NULL;}
 team*   World::getTeam2(){return NULL;}

 NPC*   World::getNPCTeam1(int a){return NULL;}
 NPC*   World::getNPCTeam2(int a){return NULL;}



World::~World(){


}
