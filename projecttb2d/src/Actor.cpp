#include <math.h>
#include "global.h"
#include "Core.h"
#include "World.h"
#include "Actor.h"

#define PI 3.14159265358979323846

Actor::Actor(sf::Vector2f pos, short nimg, sf::Vector2f ipos, sf::Vector2f idim, short life, sf::Vector2f maxspeed)
:   _frameH(idim.y),
    _frameW(idim.x),
    _life(life),
    _angle(0),
    _maxSpeed(maxspeed),
    _killed(false)

{

_objectID = g_core->getWorld()->generateUniqueID();
_spr_main.setTexture(*(g_core->getImageManager()->getImage(nimg)));
_spr_main.setPosition(pos);
_spr_main.setTextureRect(sf::IntRect(ipos.x, ipos.y, ipos.x + _frameW, ipos.y + _frameH));



}


void Actor::getAutoCollision(vector<Brick*>& mainbricks,Brick** b_up, Brick** b_right, Brick** b_down, Brick** b_left, Brick** b_downleft, Brick** b_downright, bool sfso) {


    sf::Vector2f feet       = _spr_main.getPosition();
    sf::Vector2f up         = sf::Vector2f(feet) + g_core->getRotatedVector(sf::Vector2f(0, -_frameH), -_angle);
    sf::Vector2f down       = sf::Vector2f(feet) + g_core->getRotatedVector(sf::Vector2f(0, 0), 0);
    sf::Vector2f left       = sf::Vector2f(feet) + g_core->getRotatedVector(sf::Vector2f(-_frameW*0.5, -_frameH*0.5), -_angle);
    sf::Vector2f right      = sf::Vector2f(feet) + g_core->getRotatedVector(sf::Vector2f(_frameW*0.5, -_frameH*0.5), -_angle);
    /*
    sf::Vector2f upleft     = sf::Vector2f(feet) + g_core->getRotatedVector(sf::Vector2f(-frame_width*lateral+diff, -frame_height*top+diff), -act->angle) );
    sf::Vector2f upright    = v2d_add ( feet , v2d_rotate( v2d_new(frame_width*lateral-diff, -frame_height*top+diff), -act->angle) );
    */

    sf::Vector2f downleft   = sf::Vector2f(feet) + g_core->getRotatedVector(sf::Vector2f(-_frameW*0.5, 0), -_angle);
    sf::Vector2f downright  = sf::Vector2f(feet) + g_core->getRotatedVector(sf::Vector2f(_frameW*0.5, 0), -_angle);



    if(b_up) *b_up = brick_at(mainbricks, up, sfso);
    if(b_down) *b_down = brick_at(mainbricks, down, sfso);
    if(b_left) *b_left = brick_at(mainbricks, left, sfso);
    if(b_right) *b_right = brick_at(mainbricks, right, sfso);

    if(b_downleft) *b_downleft = brick_at(mainbricks, downleft, sfso);
    if(b_downright) *b_downright = brick_at(mainbricks, downright, sfso);
    /*
    if(upleft) *upleft = brick_at(brick_list, cd_upleft);
    if(upright) *upright = brick_at(brick_list, cd_upright);

    */

    /*

    if(*b_down) g_core->getApp()->Draw(sf::Shape::Circle(down, 2, sf::Color::Green));
    else g_core->getApp()->Draw(sf::Shape::Circle(down, 2, sf::Color::Red));

    if(*b_left) g_core->getApp()->Draw(sf::Shape::Circle(left, 2, sf::Color::Green));
    else g_core->getApp()->Draw(sf::Shape::Circle(left, 2, sf::Color::Red));

    if(*b_right) g_core->getApp()->Draw(sf::Shape::Circle(right, 2, sf::Color::Green));
    else g_core->getApp()->Draw(sf::Shape::Circle(right, 2, sf::Color::Red));

    */

}

Brick* Actor::brick_at(vector<Brick*>& mainbricks, sf::Vector2f pos, bool sfso){

    if(sfso){

            for(unsigned int i = 0; i < mainbricks.size(); i++){
                if(mainbricks[i]->isSolid()){
                    float br[4];
                    br[0] = mainbricks[i]->getPos().x;
                    br[1] = mainbricks[i]->getPos().y;
                    br[2] = mainbricks[i]->getPos().x + mainbricks[i]->getFrameW();
                    br[3] = mainbricks[i]->getPos().y + mainbricks[i]->getFrameH();

                    if(g_core->dot_in_box(pos, br)){

                            return mainbricks[i]->getBrick();

                    }
            }

            }

        return NULL;

    }
    else{

        for(unsigned int i = 0; i < mainbricks.size(); i++){

            float br[4];
            br[0] = mainbricks[i]->getPos().x;
            br[1] = mainbricks[i]->getPos().y;
            br[2] = mainbricks[i]->getPos().x + mainbricks[i]->getFrameW();
            br[3] = mainbricks[i]->getPos().y + mainbricks[i]->getFrameH();

            if(g_core->dot_in_box(pos, br)){

                    return mainbricks[i]->getBrick();

            }

        }

        return NULL;

    }

}


// DEPLACEMENT

void Actor::move(sf::Vector2f delta_space){

    //if(fabs(delta_space.x) < EPSILON) delta_space.x = 0;
    _spr_main.setPosition(  _spr_main.getPosition().x + delta_space.x * cos(_angle) + delta_space.y * sin(_angle),
                            _spr_main.getPosition().y + delta_space.y * cos(_angle) - delta_space.x * sin(_angle));

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////                             OPERATORS                                                                               //////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Actor::kill(){


 _killed = true;

}

void Actor::damage(int d){

 _life -= d;
 //cout << "life : " << _life << endl;

}

void Actor::setAngle(float a){

 _angle = a;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////                             GETTERS                                                                            //////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



float Actor::getAngle() const{

 return _angle;


}


int Actor::getID() const{

 return _objectID;

}

sf::Vector2f Actor::getPos() const{

 return _spr_main.getPosition();

}

float Actor::getFrameW() const{

 return _frameW;

}


float Actor::getFrameH() const{

 return _frameH;

}

bool Actor::isKilled() const{

 return (_killed || _life <= 0);

}

Actor::~Actor(){



}
