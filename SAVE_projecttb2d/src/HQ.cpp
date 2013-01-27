#include "HQ.h"
#include "Core.h"
#include "global.h"
#include "World.h"
#include <math.h>
#include <time.h>

////////////////////////////////// HQ ///////////////////////////////////////////


/////////////////////////////// RESSOURCE SPAWNER ////////////////////////////////


RessourceSpawner::RessourceSpawner(){
}

RessourceSpawner::RessourceSpawner(int a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d, Item_t it, int types)
:   Entity(a,b,c,d),
    _it(it),
    _spawn(types)
{
    srand ( time(NULL) );

    for(int i = 0; i < 9; i++)
        _matrice[i] = NULL;

    addRessource();

    printf("--- matrice ----- \n");

    for(int i = 0; i < 9; i++){

        if(_matrice[i] != NULL)
            printf("%p\n", _matrice[i]);

    }

}

void RessourceSpawner::update(){

    if(_timer.getElapsedTime().asSeconds() > IRON_SPAWN_RATE){
        printf("SPAWN !\n");
        if(rand()%100 <= EMRLD_SPAWN_RAND_I)
            addEmerald();
        else
            addRessource();
    }

}

void RessourceSpawner::render(){}

void RessourceSpawner::addRessource(){

    for(int i = 0; i < 9; i++){

        if(!_matrice[i] && i!=4){

            float px = getPos().x + (i % 3) * (30 + DISTANCE);
            float py = getPos().y + ((int)(i / 3))* (30 + DISTANCE);

            sf::Vector2f pos(px,py);

            if(_timer.getElapsedTime().asSeconds() > IRON_SPAWN_RATE){
                _timer.restart();
                _matrice[i] = g_core->getWorld()->addDrop(pos, _it, true);
            }

        }
    }

}

void RessourceSpawner::addEmerald(){

    printf("SPAWN EMERALD :) \n");

    if(!_matrice[4]){

        float px = getPos().x + (4 % 3) * (30 + DISTANCE);
        float py = getPos().y + ((int)(4 / 3))* (30 + DISTANCE);

        sf::Vector2f pos(px,py);

        if(_timer.getElapsedTime().asSeconds() > IRON_SPAWN_RATE){
            _timer.restart();
            _matrice[4] = g_core->getWorld()->addDrop(pos, IT_EMERALD, true);
        }




    }
}

Drop** RessourceSpawner::getMatrice(){
    return _matrice;
}
