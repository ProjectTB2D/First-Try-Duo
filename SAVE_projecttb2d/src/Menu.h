#ifndef _included_MENU_h
#define _included_MENU_h
#include <SFML/Graphics.hpp>
#include "Item.h"

enum Etat_menu {
        CRAFTER_OFF = 0,
        CRAFTER_START = 1,
        CRAFTER_WEAPON = 2,
        CRAFTER_SUPERWEAPON = 3};

class Menu
{
 public:

	Menu();
	Menu(int, sf::Vector2f, int, int, float);

	void render();

    void update();

    void enable();
    void disable();

    Etat_menu getEtat() const;

 protected:

    sf::Sprite _spr;
    sf::Sprite _spr_dart;

    int _dart_position;

	sf::Vector2f _pos;
	int _type;
	int _width, _height;
	float _outline;
	Etat_menu _etatMenu;

	sf::Clock _timer;

	Item_t getItemFromId(void) const;

	};
#endif
