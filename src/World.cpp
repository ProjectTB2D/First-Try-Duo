#include <fstream>
#include "Core.h"
#include "global.h"
#include "Brick.h"
#include "Enemy.h"
#include "Enemy_soldier.h"
#include "Item.h"
#include "Item_magic.h"
#include "World.h"




World::World()
: _nextUniqueID(0)
{

    _player = NULL;

}

int World::generateUniqueID() {


    return ++_nextUniqueID;


}

void World::createWorld(const char* lvlname){


// chargement de la bibliothèque de block :


    int nbBlock = 0;
    char useless[255];

    ifstream fichier;
    fichier.open("block/blockID.blk");


    if(!fichier){
        cout << "bad file" << endl;
        exit(1);
    }

    do{

        fichier >> useless;
        if(strcmp(useless, "start") == 0){
            nbBlock++;
        }

    }
    while(strcmp(useless, "end") != 0);

    fichier.close();

    cout << "nb block = " << nbBlock << endl;

    fichier.open("block/blockID.blk");

    BlockInfo* blockInfoList;



    blockInfoList = new BlockInfo[nbBlock];


    for(int i=0; i<nbBlock; i++){

            do{

            fichier >> useless;

            }
            while(strcmp(useless, "start") == 0);

            fichier >> blockInfoList[i].name;
            fichier >> blockInfoList[i].img;
            fichier >> blockInfoList[i].x;
            fichier >> blockInfoList[i].y;
            fichier >> blockInfoList[i].w;
            fichier >> blockInfoList[i].h;
            fichier >> useless;

            if(strcmp(useless, "LADDER") == 0)
                blockInfoList[i].type = B_LADDER;
            else
            if(strcmp(useless, "DOOR") == 0)
                blockInfoList[i].type = B_DOOR;
            else
                blockInfoList[i].type = B_OBSTACLE;

            cout << "-------------------------------" << endl;
            cout << "#" << blockInfoList[i].name << " | img = " << blockInfoList[i].img;
            cout << " | pos x = " << blockInfoList[i].x << " | pos y = " << blockInfoList[i].y;
            cout << " | width = " << blockInfoList[i].w << " | height = " << blockInfoList[i].h;
            cout << " | type = " << blockInfoList[i].type << endl;
    }

    fichier.close();


    fichier.open(lvlname);

    if(!fichier){
        cout << "bad file" << endl;
        exit(1);
    }

    int gravity = 0;

    int block_Id = 0;
    int block_x = 0;
    int block_y = 0;

    char xblock_Id[255];
    char xblock_x[255];
    char xblock_y[255];

    bool isend = false;

    while(!isend){

        fichier >> xblock_Id;
        fichier >> xblock_x;
        fichier >> xblock_y;

        cout << "blk_id = " << xblock_Id << endl;
        cout << "blk_x = " << xblock_x << endl;
        cout << "blk_y = " << xblock_y << endl;
        cout << "---------------------------------------------" << endl;

    if((strcmp(xblock_Id, "end") != 0) && (strcmp(xblock_x, "end") != 0) && (strcmp(xblock_y, "end") != 0)){

        cout << "blk_id = " << xblock_Id << endl;
        cout << "blk_x = " << xblock_x << endl;
        cout << "blk_y = " << xblock_y << endl;

        block_Id = atoi(xblock_Id);
        block_x = atoi(xblock_x);
        block_y = atoi(xblock_y);

        _brickList.push_back(new Brick(sf::Vector2f(block_x, block_y), blockInfoList[block_Id].type, block_Id, blockInfoList[block_Id].img,
        sf::Vector2f(blockInfoList[block_Id].x, blockInfoList[block_Id].y), sf::Vector2f(blockInfoList[block_Id].w, blockInfoList[block_Id].h)));

        cout << " OK " << endl;

    }
    else
        isend = true;

    }


    fichier.close();

    cout << "exit 1 ok " << endl;


// position, type de la brick, angle, id image, pos image (sheet), dim image (sheet)


_buttonList.push_back(new Button(50, 360));
_buttonList.push_back(new Button(20, 360));
_buttonList.push_back(new Button(140, 360));

//_brickList[0]->getDoor()->addButton(_buttonList[0]);
//_brickList[0]->getDoor()->addButton(_buttonList[2]);

addEFence(sf::Vector2f(0,-22));



setGravity(1200);

delete[] blockInfoList;

cout << "lvl done..." << endl;



}

void World::createPlayer() {

// position / n° image / pos image (sheet) / dim image (sheet) / life / maxspeed

    _player = new Player(Actor(sf::Vector2f(100,70), 0, sf::Vector2f(0,0), sf::Vector2f(25,42), 100, sf::Vector2f(200,400)));

    // ---------- init view -----------

sf::Vector2f Center(150, 70);
sf::Vector2f Size(g_core->getWinSize().x, g_core->getWinSize().y);

//_enemiesList.push_back(new Enemy_soldier(Actor(sf::Vector2f(270,50), 2, sf::Vector2f(0,0), sf::Vector2f(25,42), 100, sf::Vector2f(200,400))));

    //Enemy* ene = new Enemy_soldier(Actor(sf::Vector2f(150,70), 0, sf::Vector2f(0,0), sf::Vector2f(33,40), 100, sf::Vector2f(200,400)));

//Item aux(Actor(sf::Vector2f(300,100), 3, sf::Vector2f(0,0), sf::Vector2f(20,20), 100, sf::Vector2f(200,400)),IT_GENERIC);

//Item_magic* aux = new Item_magic(Actor(sf::Vector2f(300,100), 3, sf::Vector2f(0,0), sf::Vector2f(20,20), 100, sf::Vector2f(200,400)),IT_GENERIC,MT_FIRE_BALL);

//addItem(aux);


}

void World::addItem(Item* i){

 _itemList.push_back(i);

}

void World::addEFence(sf::Vector2f pos){

_itemList.push_back(new E_fence(Actor(pos, 5, sf::Vector2f(0,0), sf::Vector2f(60,50), 100, sf::Vector2f(200,400)),IT_ELECTRIC_FENCE));

}

void World::addEffect(Effect e){

 _effectList.push_back(e);

}

void World::update(){

  if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && _tick.getElapsedTime().asSeconds() > 0.5){

      _tick.restart();
      sf::Vector2i globalPosition = sf::Mouse::getPosition();
      sf::View*  tmpview = g_core->getView();
      sf::Vector2f cc = g_core->getApp()->convertCoords(globalPosition, *tmpview);


      _enemiesList.push_back(new Enemy_soldier(Actor(sf::Vector2f(cc.x,cc.y), 2, sf::Vector2f(0,0), sf::Vector2f(25,42), 100, sf::Vector2f(200,400))));

  }





SelectBoxBricks(2 * g_core->getWinSize().x);


SelectBoxEnemy(2 * g_core->getWinSize().x);

  ////////////////////////////////////////
  //            UPDATE WORLD            //
  ////////////////////////////////////////


  for(unsigned int i = 0; i < _brickreduced.size(); i++){

        if(_brickreduced[i]->getDoor()){
            _brickreduced[i]->getDoor()->update();
        }

  }


  ////////////////////////////////////////
  //            UPDATE ENEMIES           //
  ////////////////////////////////////////

  for(unsigned int i = 0; i < _enemyreduced.size(); i++){
        _enemyreduced[i]->update(_brickreduced);

  }

  ////////////////////////////////////////
  //            UPDATE PLAYER           //
  ////////////////////////////////////////


 _player->update(_brickreduced, _enemyreduced, _buttonList);


  ////////////////////////////////////////
  //            UPDATE ITEMS            //
  ////////////////////////////////////////

//  list<Item*> aux;

  //test(_itemList);


//  SelectBoxItem(2 * g_core->getWinSize().x, aux);

  for (list<Item*>::iterator it = _itemList.begin(); it != _itemList.end(); ++it){

        (*it)->update(_brickreduced, _enemyreduced, sf::Vector2f(0,0), true);

  }

}

//////////////////////////////////////////////////////////////// PURGE THE UNDEAD //////////////////////////////////////////////////////////////////////////:

void World::disolve_dead_items(){


  for (list<Item*>::iterator it = _itemList.begin(); it != _itemList.end();){

        if((*it)->isKilled()){

            delete (*it);
            (*it) = NULL;
            it = _itemList.erase(it);

        }
        else
        ++it;

  }



}

void World::disolve_dead_enemies(){


  for(unsigned int i = 0; i < _enemiesList.size(); ){

    if(_enemiesList[i]->isKilled()){


        this->addEffect(Effect(_enemiesList[i]->getPos() - sf::Vector2f(0,24), sf::Vector2f(256,306), 350, 50, 0.05,1,false));
        this->addEffect(Effect(_enemiesList[i]->getPos() - sf::Vector2f(0,21), sf::Vector2f(0,64), 1024, 64, 0.03, 1,true,sf::Color(255,0,0,150)));
        delete _enemiesList[i];
        _enemiesList[i] = NULL;
        _enemiesList.erase(_enemiesList.begin()+i);
    }
    else
        ++i;

    }


    for (list<Effect>::iterator it = _effectList.begin(); it != _effectList.end();){

           if(it->getSeq()){
                it = _effectList.erase(it);
           }

        else
        ++it;

    }

}


///////////////////////////////////////////////////////////////////// RENDER ///////////////////////////////////////////////////////////////////////////

void World::render(){


centerCamera();
 renderWorld();

 for(unsigned int i = 0; i < _buttonList.size(); ++i){

    _buttonList[i]->render();

 }
  renderEnemies();
  renderPlayer();
 renderItems();

}


void World::renderWorld() {


    // render background


    // render bricks

    //cout << g_core->getWinSize().x << endl;

    vector<Brick*> brickreduced;
    brickreduced = SelectBoxBricksRender();

    for(unsigned int i = 0; i<brickreduced.size(); ++i){

        brickreduced[i]->render();

    }


}

void World::renderEnemies() {

    vector<Enemy*> enemyreduced;
    enemyreduced = SelectBoxEnemyRender();

for(unsigned int i = 0; i < enemyreduced.size(); ++i){

    enemyreduced[i]->render();


}


}


void World::renderPlayer() {


    _player->render();


}

void World::renderItems() {


    for (list<Item*>::iterator it = _itemList.begin(); it != _itemList.end(); ++it){

        (*it)->render();

    }

    for (list<Effect>::iterator it = _effectList.begin(); it != _effectList.end(); ++it){

        it->render();

    }


}


void World::centerCamera() {

g_core->getView()->setCenter(getPlayer()->getPos());

}

void World::disolve(){

        ////////////////////////////////////
  //          PURGE                 //
  ////////////////////////////////////

  disolve_dead_items();
  disolve_dead_enemies();



}

///////////////////////////////////////////////////////////// EPURAGE /////////////////////////////////////////////////////////////////////////////////////////

void World::SelectBoxBricks(int margin){

    _brickreduced.clear();

    for(unsigned int i = 0; i < _brickList.size(); i++) {

        if(insideScreen(_brickList[i]->getPos().x,_brickList[i]->getPos().y,_brickList[i]->getFrameW(),_brickList[i]->getFrameH(),margin)){

            _brickreduced.push_back(_brickList[i]->getBrick());

        }
    }
}

vector<Brick*> World::SelectBoxBricksRender(){

    vector<Brick*> brickreduced;

    for(unsigned int i = 0; i < _brickreduced.size(); i++) {

        if(insideScreen(_brickreduced[i]->getPos().x,_brickreduced[i]->getPos().y,_brickreduced[i]->getFrameW(),_brickreduced[i]->getFrameH(),0)){

            brickreduced.push_back(_brickreduced[i]->getBrick());

        }
    }

    return brickreduced;
}

void World::SelectBoxEnemy(int margin){

    _enemyreduced.clear();

    for(unsigned int i = 0; i < _enemiesList.size(); i++) {

        if(insideScreen(_enemiesList[i]->getPos().x,_enemiesList[i]->getPos().y,_enemiesList[i]->getFrameW(),_enemiesList[i]->getFrameH(),margin)){

            _enemyreduced.push_back(_enemiesList[i]);

        }
    }

}

vector<Enemy*> World::SelectBoxEnemyRender(){

    vector<Enemy*> enemyreduced;

    for(unsigned int i = 0; i < _enemyreduced.size(); i++) {

        if(insideScreen(_enemyreduced[i]->getPos().x,_enemyreduced[i]->getPos().y,_enemyreduced[i]->getFrameW(),_enemyreduced[i]->getFrameH(),0)){

            enemyreduced.push_back(_enemyreduced[i]);

        }
    }

    return enemyreduced;
}

void World::SelectBoxItem(int margin, list<Item*>& aux){

/*

    for(unsigned int i = 0; i < _itemList.size(); i++) {

        if(insideScreen(_itemList[i]->getPos().x,_itemList[i]->getPos().y,_itemList[i]->getFrameW(),_itemList[i]->getFrameH(),margin)){

            aux.push_back(_itemList[i]);

        }
    }

*/

}

void World::setGravity(int g){

 _gravity = g;

}

int World::getGravity() const{

 return _gravity;

}

bool World::insideScreen(int x, int y, int w, int h, int margin)
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

Player* World::getPlayer(){

 return _player;

}

Enemy* World::getEnemy(int id, std::vector<Enemy*>& main_en){


    for(unsigned int i = 0; i < main_en.size(); i++)
        if (main_en[i]->getID() == id)
            return main_en[i];

    return NULL;

}

void  World::getValueFromParser(char* line){



}

World::~World(){

delete _player;

for(unsigned int i = 0; i < _brickList.size(); ){

    delete _brickList[i];
    _brickList[i] = NULL;
    _brickList.erase(_brickList.begin()+i);
    //cout << "enemy " << i << " deleted " << endl;

}

for(unsigned int i = 0; i < _enemiesList.size(); ){

    delete _enemiesList[i];
    _enemiesList[i] = NULL;
    _enemiesList.erase(_enemiesList.begin()+i);
    //cout << "enemy " << i << " deleted " << endl;

}

for (list<Item*>::iterator it = _itemList.begin(); it != _itemList.end();){

          //cout << "occurence ! " << endl;
            delete (*it);
            (*it) = NULL;
            it = _itemList.erase(it);


}

for(unsigned int i = 0; i < _buttonList.size();){

    delete _buttonList[i];
    _buttonList[i] = NULL;
    _buttonList.erase(_buttonList.begin()+i);
    cout << "button " << i << "deleted" << endl;

}

}
