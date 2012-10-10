#include "Node.h"
#include <iostream>

Node::Node(sf::Vector2f pos, Node* n1, Node* n2) : _pos(pos), _n1(n1), _n2(n2)
{

  std::cout << "Init Node" << std::endl;


}

// FOR EVERY FRAME


void Node::update(){


}

void Node::display(){


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

  if(i == 1)
    return _n1;
  else
    return _n2;

}

float Node::getDistanceNode(unsigned short i) const{

  if(i == 1)
    return _n1_distance;
  else
    return _n2_distance;

}


// OTHER

void Node::computeDistance(){

}

void Node::autoPath(){


}
