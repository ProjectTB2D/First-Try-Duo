#include <math.h>
#include "global.h"
#include "Core.h"
#include "World.h"
#include "Entity.h"

#define PI 3.14159265358979323846

Entity::Entity()
{
	printf("Construction Entity default\n");
}

Entity::Entity(int idImage, sf::Vector2f pos, sf::Vector2f ipos, sf::Vector2f idim)
: 	_frameH(idim.y),
    _frameW(idim.x),
	_angle(0),
	_killed(false)
{
	_id = g_core->getWorld()->generateUniqueID();
	_spr.setTexture(*(g_core->getImageManager()->getImage(idImage)));
	_spr.setPosition(pos);
	_spr.setTextureRect(sf::IntRect(ipos.x, ipos.y, ipos.x + _frameW, ipos.y + _frameH));
}

Entity::~Entity(){

printf("entity deleted\n");

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Entity::render(){

}
void Entity::update(){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////                             GETTERS                                                                            //////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float Entity::getFrameH() const{

	return _frameH;

}

float Entity::getFrameW() const{

	return _frameW;

}

sf::Vector2f Entity::getPos() const{

	return _spr.getPosition();

}

sf::Sprite * Entity::getSpr(){

	return &_spr;

}

unsigned int Entity::getID() const{

	return _id;

}

float Entity::getAngle() const{

	return _angle;

}

bool Entity::getKilled() const{

	return _killed;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////                             OPERATORS                                                                               //////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Entity::setPos(sf::Vector2f& pos){

	_spr.setPosition(pos);

}

void Entity::setSpr(int idImg){

	_spr.setTexture(*(g_core->getImageManager()->getImage(idImg)));
}

void Entity::setFrame(sf::Vector2f& f){

	_frameW = f.x;
	_frameH = f.y;
}

void Entity::setAngle(float a){

	_angle = a;
}

void Entity::kill(){

 _killed = true;
}
