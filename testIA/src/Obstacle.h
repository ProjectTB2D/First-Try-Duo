#ifndef OBSCLE_HPP_INCLUDED
#define OBSCLE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Node.h"
#include "Character.hpp"

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
  sf::FloatRect getRect() const;

  Node* getNodeList();
  Node* getNodeProcheDe(sf::Vector2f); // Plus proche du player ET plus proche de la destination

  bool  collisionCircle(sf::Vector2f, float) const;
  bool  collisionPoint(sf::Vector2f) const;

  // other

  void makeRoad(Character*);
  void computeNodeDistance();
  void autoNodeLinking();
  void displayNodeMap();

  // destructor

  ~Obstacle();

 protected:

  sf::Sprite _spr;

  Node* _nodeList;
  int _nb_node;

  // Collision

  float _radius;

};
#endif
