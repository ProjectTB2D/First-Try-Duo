#ifndef OBSCLE_HPP_INCLUDED
#define OBSCLE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Node.h"

class Obstacle
{

 public:

  Obstacle(sf::Vector2f);
  Obstacle(sf::Texture& , sf::Vector2f);

  // Init

  void initNodes();

  // for every frame

  void update();
  void display(sf::RenderWindow &);

  // setter

  void setPos(sf::Vector2f);
  
  // getter

  sf::Vector2f getPos() const;
  
  Node* getNodeList();
  

  // other

  void computeNodeDistance();
  void autoNodeLinking();
  void displayNodeMap();

  // destructor

  ~Obstacle();

 protected:

  sf::Sprite _spr;
 
  Node* _nodeList;
  int _nb_node;

};
#endif
