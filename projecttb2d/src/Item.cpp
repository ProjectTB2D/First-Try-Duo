
#include "global.h"
#include "Core.h"
#include "Entity.h"
#include "Item.h"

Item::Item()
{


}

Item::Item(const Entity& ent, Item_t type, bool s)
:   Entity(ent),
    _it(type),
    _super(s)
{

}

bool Item::getSuper() const{

    return _super;

}

Item_t Item::getItemType() const{

    return _it;

}

void Item::setInfo(float angle, sf::Vector2f pos){

    _carrier_angle = angle;
    _carrier_pos = pos;

}

Item::~Item(){

}
