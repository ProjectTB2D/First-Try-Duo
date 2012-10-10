#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Node
{

 public:

  Node(sf::Vector2f, Node*, Node*);


  // for every frame

  void update();
  void display();

  // setter

  void setPos(sf::Vector2f);
  void defineNode1(Node*);
  void defineNode2(Node*);

  
  // getter

  sf::Vector2f getPos() const;
  Node* getNode(unsigned short);
  float getDistanceNode(unsigned short) const;

  // other

  void computeDistance(); // définie automatiquement la distance entre 2 nodes
  void autoPath(); // définie automatiquement quelles nodes relier

 protected:

  sf::Vector2f _pos;
 
  Node* _n1;
  Node* _n2;

  float _n1_distance;
  float _n2_distance;

};
#endif
