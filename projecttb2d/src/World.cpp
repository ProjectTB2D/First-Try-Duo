#include <fstream>
#include "Core.h"
#include "global.h"
#include "World.h"
#include "Bullet.h"



World::World()
: _nextUniqueID(0)
{




}

int World::generateUniqueID() {


    return ++_nextUniqueID;


}

void World::createWorld(const char* lvlname){

    int nbColonnes = 20;
    int nbLignes = 20;

    _matrice = new tile*[nbColonnes];

	for(int i=0; i<nbColonnes; i++)
		_matrice[i] = new tile[nbLignes];

    for(int i = 0; i < nbColonnes; i++)
        for(int j = 0; j < nbLignes; j ++){

            _matrice[i][j].spr.setTexture(*(g_core->getImageManager()->getImage(1)));
            _matrice[i][j].spr.setPosition(i*100, j*100);
            //spr.setTextureRect(sf::IntRect(ipos.x, ipos.y, ipos.x + _frameW, ipos.y + _frameH));
            //spr.setOrigin(idim.x / 2, idim.y / 2);

        }


}

void World::createPlayer() {

    printf("s1\n");

    _team1.p = NULL;




    _team1.p = new Player(Actor(Entity(0, sf::Vector2f(0, 0), sf::Vector2f(0,0), sf::Vector2f(50,50)),
                                100,
                               3));

    _team1.b = new Bullet(Entity(2, sf::Vector2f(0, 0), sf::Vector2f(0,0), sf::Vector2f(25,25)), B_PISTOL, 0, 0.5, 1, 1);

}




void World::update(){

    _team1.p->update();
    _team1.b->update();
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

    renderWorld();
    _team1.p->render();
    _team1.b->render();
    centerCamera();
}


void World::renderWorld() {

    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 20; j ++){

            g_core->getApp()->draw(_matrice[i][j].spr);

        }

}


void World::centerCamera() {

g_core->getView()->setCenter(getTeam1()->p->getPos());

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

 team*   World::getTeam1(){return &_team1;}
 team*   World::getTeam2(){return NULL;}

 NPC*   World::getNPCTeam1(int a){return NULL;}
 NPC*   World::getNPCTeam2(int a){return NULL;}



World::~World(){

    delete _team1.p;



}
