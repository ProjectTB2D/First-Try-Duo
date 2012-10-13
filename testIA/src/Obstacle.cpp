#include "Obstacle.h"
#include <math.h>
#include <iostream>
#include <stdio.h>

#define PI 3.141592654

Obstacle::Obstacle(sf::Vector2f pos)
{

  _spr.setPosition(pos);

}

Obstacle::Obstacle(sf::Texture& img, sf::Vector2f pos)
{

  
  std::cout << "[0] pos x = " << pos.x << std::endl;

  _spr.setTexture(img);

  _spr.setPosition(pos);
  _spr.setOrigin(144/2, 135/2);

  initNodes();


}

// INIT

void Obstacle::initNodes(){

   std::cout << "[2] pos x = " << getPos().x << std::endl;

  _nb_node = 12;

  _nodeList = new Node[_nb_node];
  
  for(unsigned int i = 0; i < _nb_node; i++){

    _nodeList[i].setPos(sf::Vector2f(getPos().x + 100*cos(i*1.04f/2), getPos().y + 100*sin(i*1.04f/2)));
    
 

  }
  
  autoNodeLinking();
  computeNodeDistance();
  displayNodeMap();


}


void Obstacle::update(){

  
}

void Obstacle::display(sf::RenderWindow & app){

  app.draw(_spr);

  for(unsigned int i = 0; i < _nb_node; i++){

    _nodeList[i].display(app);


  }

}

// SETTER


void Obstacle::setPos(sf::Vector2f pos){

  _spr.setPosition(pos);


}

// GETTER

sf::Vector2f Obstacle::getPos() const{

  return _spr.getPosition();

}

Node* Obstacle::getNodeList(){

  return _nodeList;

}

void Obstacle::computeNodeDistance() {


  for(unsigned int i = 0; i < _nb_node; i++){

    _nodeList[i].computeDistance();

  }



}

void Obstacle::autoNodeLinking() {

  // LINK du chemin 1

  for(unsigned int i = 0; i < _nb_node - 1; i++){

    _nodeList[i].defineNode1(&_nodeList[i+1]);
    
  }

   _nodeList[_nb_node - 1].defineNode1(&_nodeList[0]);

   // LINK du chemin 2

   for(unsigned int i = _nb_node - 1; i > 0; i--){

     _nodeList[i].defineNode2(&_nodeList[i-1]);
    
   }

   _nodeList[0].defineNode2(&_nodeList[_nb_node - 1]);

}

void Obstacle::displayNodeMap() {

  std::cout << "---------------------------P1--------------------------" << std::endl;
   
 
  for(unsigned int i = 0; i < _nb_node; i++){

    Node* mthis = _nodeList[i].getNode(0);
    Node* n1 = _nodeList[i].getNode(1);

    float dist1 = _nodeList[i].getDistanceNode(1);

    printf("node : %p linked to %p | dist : %f\n", mthis, n1, dist1);
 
  }

  std::cout << "---------------------------P2--------------------------" << std::endl;
  for(unsigned int i = 0; i < _nb_node; i++){

    Node* mthis = _nodeList[i].getNode(0);
    Node* n2 = _nodeList[i].getNode(2);

    float dist2 = _nodeList[i].getDistanceNode(2);

    printf("node : %p linked to %p | dist : %f\n", mthis, n2, dist2);
  }

}

Obstacle::~Obstacle(){


}
