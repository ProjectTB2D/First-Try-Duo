#include <iostream>
#include "Node.h"
#include <math.h>

Node::Node()
{

  _pos = sf::Vector2f(0,0);
  _n1 = NULL;
  _n2 = NULL;

}

Node::Node(sf::Vector2f pos, Node* n1, Node* n2) : _pos(pos), _n1(n1), _n2(n2)
{

  std::cout << "Init Node" << std::endl;


}

// FOR EVERY FRAME


void Node::update(){


}

void Node::display(sf::RenderWindow &app){

  sf::CircleShape shape(3);
  shape.setFillColor(sf::Color::Green);
  shape.setPosition(_pos);

  app.draw(shape);

}

// SETTERS

void Node::setPos(sf::Vector2f pos){

  _pos = pos;

}

void Node::defineNode1(Node* n){

  _n1 = n;

}

void Node::defineNode2(Node* n){

  _n2 = n;

}

// GETTER

sf::Vector2f Node::getPos() const{

  return _pos;

}

Node* Node::getNode(unsigned short i){

  switch(i){
    
  case 0 : return this;
  case 1 : return _n1;
  case 2 : return _n2;
  default : return NULL;


  }

}

float Node::getDistanceNode(unsigned short i) const{

 
  if(i == 1)
    return _n1_distance;
  else
    return _n2_distance;
 
}


// OTHER

void Node::computeDistance(){

  if(getNode(1) == NULL || getNode(2) == NULL){
    std::cout << "undefined link" << std::endl;
    exit(-1);
  }
  
  sf::Vector2f pos0(getPos());
  sf::Vector2f pos1(getNode(1)->getPos());
  sf::Vector2f pos2(getNode(2)->getPos());

  float dis1x = pos0.x - pos1.x;
  float dis1y = pos0.y - pos1.y;

  float dis2x = pos0.x - pos2.x;
  float dis2y = pos0.y - pos2.y;

  _n1_distance = sqrt((dis1x*dis1x) + (dis1y*dis1y));

  _n2_distance = sqrt((dis2x*dis2x) + (dis2y*dis2y));
  

}



// DESTROYER

Node::~Node(){

}
