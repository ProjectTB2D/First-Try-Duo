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

  _radius = 68;

  initNodes();


}

// INIT

void Obstacle::initNodes(){

   std::cout << "[2] pos x = " << getPos().x << std::endl;

  _nb_node = 12;

  _nodeList = new Node[_nb_node];

  for( int i = 0; i < _nb_node; i++){

    _nodeList[i].setPos(sf::Vector2f(getPos().x + 85*cos(i*1.04f/2), getPos().y + 85*sin(i*1.04f/2)));



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

  sf::CircleShape cs(_radius);
  cs.setFillColor(sf::Color(255,0,0,100));
  cs.setPosition(getPos().x - 144/2, getPos().y - 135/2);
  app.draw(cs);

     sf::RectangleShape rectangle;
     rectangle.setSize(sf::Vector2f(_spr.getLocalBounds().width + 32, _spr.getLocalBounds().height + 42));
     //     rectangle.setOutlineColor(sf::Color::Red);
     //rectangle.setOutlineThickness(5);
     rectangle.setFillColor(sf::Color(255,255,0,50));
     rectangle.setPosition(_spr.getPosition().x - 85, _spr.getPosition().y - 85);
     app.draw(rectangle);
}

// SETTER


void Obstacle::setPos(sf::Vector2f pos){

  _spr.setPosition(pos);


}

// GETTER

sf::Vector2f Obstacle::getPos() const{

  return _spr.getPosition();

}

sf::FloatRect Obstacle::getRect() const
{
    sf::FloatRect box((_spr.getPosition().x - 85), (_spr.getPosition().y - 85), (_spr.getLocalBounds().width + 32), (_spr.getLocalBounds().height + 42));
    // J'ai fais qql ajustements pour augmenter la taille

    return box;
}

Node* Obstacle::getNodeList(){

  return _nodeList;

}

Node* Obstacle::getNodeProcheDe(sf::Vector2f pos)
{
    float disx, disy, distance, plusPetiteDist;
    Node* nodePlusProche;

    disx = pos.x - _nodeList[0].getPos().x;
    disy = pos.y - _nodeList[0].getPos().y;
    plusPetiteDist = sqrt((disx*disx) + (disy*disy));
    nodePlusProche = &_nodeList[0];

    for(unsigned int i = 0; i < _nb_node; i++){

        disx = pos.x - _nodeList[i].getPos().x;
        disy = pos.y - _nodeList[i].getPos().y;
        distance = sqrt((disx*disx) + (disy*disy));

        if(distance < plusPetiteDist)
        {
            plusPetiteDist = distance;
            nodePlusProche = &_nodeList[i];
        }
    }

    return nodePlusProche;
}

////////////// COLLISION ////////////////////////////////////

bool  Obstacle::collisionCircle(sf::Vector2f pos, float r) const{

  int d2 = (getPos().x-pos.x)*(getPos().x-pos.x) + (getPos().y-pos.y)*(getPos().y-pos.y);
  if (d2 > (_radius + r)*(_radius + r))
    return false;
  else
    return true;
  
}

bool  Obstacle::collisionPoint(sf::Vector2f pos) const{

  int d2 = (pos.x - getPos().x ) * (pos.x - getPos().x) + ( pos.y - getPos().y ) * (pos.y - getPos().y);
  if (d2 > _radius * _radius)
    return false;
   else
     return true;
  
}

void Obstacle::makeRoad(Character* perso)
{
    Node* depart = getNodeProcheDe(perso->getPositionActuelle());
    Node* arrive = getNodeProcheDe(perso->getDestination());

    Node* test = depart;
    Node* test2 = depart;

    float distance1 = 0, distance2 = 0;

    int i = 0;

    while(test != arrive)
    {
        distance1 += test->getDistanceNode(1);
        test = test->getNode(1);
        i++;
        std::cout << " i : " << i << " distance :  " << test->getDistanceNode(1) << std::endl;
    }

    while(test2 != arrive)
    {
        distance2 += test2->getDistanceNode(2);
        test2 = test2->getNode(2);
    }

    std::cout << "d1 : " << distance1 << std::endl;
    std::cout << "d2 : " << distance2 << std::endl;

    if(distance1 < distance2) // Chemin 1
    {
        while(arrive != depart) // chemin inverse car on empile dans un vector par la fin, le dernier element sera le point de depart
        {
            perso->ajoutDest(arrive->getPos());
            arrive = arrive->getNode(2); // sens inverse
        }

        perso->ajoutDest(depart->getPos());
    }
    else // chemin 2
    {
        while(arrive != depart) // chemin inverse car on empile dans un vector par la fin, le dernier element sera le point de depart
        {
            perso->ajoutDest(arrive->getPos());
            arrive = arrive->getNode(1); // sens inverse
        }

        perso->ajoutDest(depart->getPos());
    }

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
