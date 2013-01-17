#include "HQ.h"
#include "Core.h"
#include "global.h"
#include "World.h"
#include <math.h>

////////////////////////////////// HQ ///////////////////////////////////////////


/////////////////////////////// RESSOURCE SPAWNER ////////////////////////////////


RessourceSpawner::RessourceSpawner(){
}

RessourceSpawner::RessourceSpawner(int a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d, Item_t it, int types)
:   Entity(a,b,c,d),
    _it(it),
    _spawn(types)
{
    for(int i = 0; i < 9; i++)
        _matrice[i] = NULL;

    addRessource();


}

void RessourceSpawner::update(){}

void RessourceSpawner::render(){}

void RessourceSpawner::addRessource(){

    for(int i = 0; i < 9; i++){

        if(!_matrice[i] && i!=4){

            float px = getPos().x + (i % 3) * (30 + DISTANCE);
            float py = getPos().y + ((int)(i / 3))* (30 + DISTANCE);

            sf::Vector2f pos(px,py);

            g_core->getWorld()->addDrop(pos, _it);
        }
    }

}
