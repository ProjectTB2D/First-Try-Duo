#include <math.h>
#include "global.h"
#include "Core.h"
#include "World.h"
#include "Menu.h"
#include "Item.h"
#include "ImageManager.h"

#define NBSTART 1
#define NBWEAPON 8
#define POSDARTY 8
#define POSDARTX 10

Menu::Menu()
{

}

Menu::Menu(int type, sf::Vector2f pos, int width = 100, int height = 20, float outline = 0.5f)
: 	_pos(pos),
    _type(type),
    _width(width),
    _height(height),
    _outline(outline),
    _etatMenu(CRAFTER_START)
{
    _spr.setTexture(*(g_core->getImageManager()->getImage(5)));
    _spr.setPosition(0,0);
    _spr_dart.setTexture(*(g_core->getImageManager()->getImage(7)));
    _spr_dart.setPosition(POSDARTX,POSDARTY);
    _dart_position = 0;
    _etatMenu = CRAFTER_OFF;

}

void Menu::enable(){

    _etatMenu = CRAFTER_START;
    _dart_position = 0;
    _spr_dart.setPosition(POSDARTX,POSDARTY);
}

void Menu::disable(){

    _etatMenu = CRAFTER_OFF;

}

bool Menu::update(){

if(_timer.getElapsedTime().asSeconds() > 0.1){

_timer.restart();

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){

    if(_etatMenu == CRAFTER_START){
        if(_dart_position == 0)
            _dart_position = NBSTART;
        else
            _dart_position--;
    }
    else
    if(_etatMenu == CRAFTER_WEAPON){
        if(_dart_position == 0)
            _dart_position = NBWEAPON;
        else
            _dart_position--;
    }
    else
    if(_etatMenu == CRAFTER_SUPERWEAPON){
        if(_dart_position == 0)
            _dart_position = NBWEAPON;
        else
            _dart_position--;
    }


    _spr_dart.setPosition(POSDARTX, _dart_position * 21 + POSDARTY);

}


if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){

    if(_etatMenu == CRAFTER_START){
        if(_dart_position == NBSTART)
            _dart_position = 0;
        else
            _dart_position++;
    }
    else
    if(_etatMenu == CRAFTER_WEAPON){
        if(_dart_position == NBWEAPON)
            _dart_position = 0;
        else
            _dart_position++;
    }
    else
    if(_etatMenu == CRAFTER_SUPERWEAPON){
        if(_dart_position == NBWEAPON)
            _dart_position = 0;
        else
            _dart_position++;
    }


    _spr_dart.setPosition(POSDARTX, _dart_position * 21 + POSDARTY);
}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){

    _dart_position = 0;
    _spr_dart.setPosition(POSDARTX,POSDARTY);

    if(_etatMenu != CRAFTER_START)
        _etatMenu = CRAFTER_START;


}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){

    Item*   aux;

    printf("pos : %d\n", _dart_position);

    if(_etatMenu == CRAFTER_START){

        _dart_position = 0;
        _spr_dart.setPosition(POSDARTX,POSDARTY);
        switch(_dart_position){

            case 0 :    _etatMenu = CRAFTER_WEAPON;break;
            case 1 :    _etatMenu = CRAFTER_SUPERWEAPON;break;
            default :   break;

        }

    }
    else{


        switch(_etatMenu){

            case CRAFTER_WEAPON : {

            printf("craft...\n");

            if(!(aux = g_core->getWorld()->getTeam1()->crafter->craft(getItemFromId()))){

                printf("echec du craft de l'item\n");

            }
            else{

                printf("craft ok\n");
                g_core->getWorld()->getTeam1()->p->setHandItem(aux);

            }
            break;
            }

            case CRAFTER_SUPERWEAPON : printf("lol1\n");break;
            default : printf("lol2\n");break;
        }

    }


}
}

    return true;
}

void Menu::render(){

    switch(_etatMenu){

        case CRAFTER_START : _spr.setTexture(*(g_core->getImageManager()->getImage(5)));break;
        case CRAFTER_WEAPON: _spr.setTexture(*(g_core->getImageManager()->getImage(6)));break;
        case CRAFTER_SUPERWEAPON: _spr.setTexture(*(g_core->getImageManager()->getImage(6)));break;
        default: break;
    }
g_core->getApp()->draw(_spr);
g_core->getApp()->draw(_spr_dart);

}

Item_t Menu::getItemFromId(void) const{

    if(_etatMenu == CRAFTER_WEAPON){

        switch(_dart_position){

            case 0 : return IT_BAT;
            case 1 : return IT_PISTOL;
            case 2 : return IT_THROW_AXE;
            case 3 : return IT_CHAINSAW;
            case 4 : return IT_SHOTGUN;
            case 5 : return IT_SMG;
            case 6 : return IT_KATANA;
            case 7 : return IT_PLASMA;
            case 8 : return IT_RPG;
            default : return IT_BAT;
        }

    }

    if(_etatMenu == CRAFTER_SUPERWEAPON){

        switch(_dart_position){

            case 0 : return IT_BAT_SUPER;
            case 1 : return IT_PISTOL_SUPER;
            case 2 : return IT_THROW_AXE_SUPER;
            case 3 : return IT_CHAINSAW_SUPER;
            case 4 : return IT_SHOTGUN_SUPER;
            case 5 : return IT_SMG_SUPER;
            case 6 : return IT_KATANA_SUPER;
            case 7 : return IT_PLASMA_SUPER;
            case 8 : return IT_RPG_SUPER;
            default : return IT_BAT_SUPER;
        }

    }
return IT_BAT_SUPER;
}

Etat_menu Menu::getEtat() const{

    return _etatMenu;

}

