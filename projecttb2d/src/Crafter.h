#ifndef _included_Craft_h
#define _included_Craft_h
#include <SFML/Graphics.hpp>
#include "src/Entity.h"
#include "Item.h"

#define NBITEM 50;



struct recipe{

    int nbIron;
    int nbGold;
    int nbRuby;

    Item_t result;
};

struct storedItem{

    Item_t item;
    float dmg_mult;
    float spd_mult;
    float spr_mult;

};

class HQ : public Entity
{
 public:

	Crafter();
	Crafter(int, sf::Vector2f, sf::Vector2f, sf::Vector2f);

	virtual void    render();
	virtual void    update();

    //        void    putIn(Item*);
    //void            putOut(Item*);
    bool            craft(Item_t);

    sf::Vector3i&    getRessources() const;





 protected:

    int nbIron;
    int nbGold;
    int nbRuby;

    std::vector<storedItem> _output;

    Item_t list[NBITEM];

    void updateCrafterData();

};
#endif
