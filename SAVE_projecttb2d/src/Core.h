#ifndef _included_Core_hpp
#define _included_Core_hpp
#include <SFML/Graphics.hpp>
#include "ImageManager.h"
#include "Menu.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


class World;

class Core
{

protected:

// ---------- main ressources ------------------

sf::View*           _view;
sf::RenderWindow*   _app;
World*              _world;
ImageManager*       _imgMan;
sf::Clock           _clockFrame;
float               _frameTime;
Menu*               _menu;

// ----------------------------------


int                 _win_H;
int                 _win_W;

// ------------------- debug ----------------------

bool                _displayFPS;
int                 _item_counter;


public:

// CONSTRUCTOR

Core();


// ---------- ENGINE ------------------

void                initApp(int, int);
void                initWorld(const char*);
void                initView();
void                run();
void                render();

// -------- GENERIC  ----------

bool                dot_in_box(sf::Vector2f a, float b[4]);
bool                bounding_box(float a[4], float b[4], bool = false);
bool                dot_in_circle(sf::Vector2f a, sf::Vector2f b, float r);

sf::Vector2f        rotate_vector(sf::Vector2f, float);

// ---------- SETTER ------------------


// ---------- GETTER -------------------

World*              getWorld();
sf::RenderWindow*   getApp();
sf::View*           getView();
ImageManager*       getImageManager();
Menu*               getMenu(){return _menu;}
void                getInfo();
sf::Vector2f        getRotatedVector(sf::Vector2f, float) const;
sf::Vector2i        getWinSize() const;
float               getFrameTime() const;

//  --------- DEBBUGER -------------------

void                countItemGenerated();

// DESTRUCTOR

~Core();

};
#endif
