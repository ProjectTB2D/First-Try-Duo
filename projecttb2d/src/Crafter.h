#ifndef _included_Craft_h
#define _included_Craft_h
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Item.h"

#define NBITEM 50



struct recipe{

    Item_t result;
    int nbIron;
    int nbGold;
    int nbRuby;

};

struct storedItem{

    Item_t item;
    float dmg_mult;
    float spd_mult;
    float spr_mult;

};

class Crafter : public Entity
{
 public:

	Crafter();
	Crafter(int, sf::Vector2f, sf::Vector2f, sf::Vector2f);

	virtual void    render();
	virtual void    update();

    //void            putIn(Item*); // SUREMENT a faire dans Actor
    //void            putOut(Item*);
    bool            craft(Item_t); // true si le craft a r�ussi
    bool            craftSuper(Item_t); // DEBATTRE si on ne fait pas que les emerald ne sont plus des blocs JOKER mais seulement un bloc suppl�mentaire pr cr�er un super objet

    //sf::Vector3i&    getRessources() const;
    sf::Vector3i    getRessources() const;
    int             getEmerald() const;
    recipe          getRecipe(Item_t) const;





 protected:

    int _nbIron;
    int _nbGold;
    int _nbRuby;
    int _nbEmerald;

    std::vector<storedItem> _output;

    Item_t list[NBITEM];

    void updateCrafterData();

};
#endif
