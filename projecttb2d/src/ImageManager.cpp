#include "ImageManager.h"

ImageManager::ImageManager()
{

    cout << "creation du ImageManager" << endl;

    for(int i=0; i<NBIMAGE; i++)
        _storage[i] = NULL;

    for(int i=0; i<NBIMAGE; i++){
        _storage[i] = new sf::Texture();
        _storage[i]->setSmooth(false);
    }


    _storage[0]->loadFromFile("images/imgUndefined.png");
    _storage[1]->loadFromFile("images/tileTest.png");
    _storage[2]->loadFromFile("images/bullet1.png");
    _storage[3]->loadFromFile("images/plasmaGun.png");
    _storage[4]->loadFromFile("images/tileset2.png");
    _storage[5]->loadFromFile("images/HUD_crafter.png");
    _storage[6]->loadFromFile("images/HUD_weapon.png");
    _storage[7]->loadFromFile("images/Arrow_Hud_Crafter.png");
    _storage[8]->loadFromFile("images/Batte.png");
    _storage[9]->loadFromFile("images/Pistol.png");
    _storage[10]->loadFromFile("images/Axe.png");
    _storage[11]->loadFromFile("images/Chainsaw.png");
    _storage[12]->loadFromFile("images/Shotgun.png");
    _storage[13]->loadFromFile("images/Smg.png");
    _storage[14]->loadFromFile("images/Katana.png");
    _storage[15]->loadFromFile("images/PlasmaGunV2.png");
    _storage[16]->loadFromFile("images/RPG.png");
    _storage[17]->loadFromFile("images/character.png");
    _storage[18]->loadFromFile("images/bullet2.png");
    _storage[19]->loadFromFile("images/iron.png");
    _storage[20]->loadFromFile("images/gold.png");
    _storage[21]->loadFromFile("images/ruby.png");
    _storage[22]->loadFromFile("images/emerald.png");
    _storage[23]->loadFromFile("images/R_Spawner.png");
    //_storage[0]->createMaskFromColor(sf::Color(255,255,255));



}

int ImageManager::returnId() const{

        return 0;

}

sf::Texture * ImageManager::getImage(short a){



    return _storage[a];


}


ImageManager::~ImageManager(){

 cout << "destruction du Image Manager" << endl;




 for(int i=0; i<NBIMAGE; i++)
    if(_storage[i] != 0){
        delete _storage[i];
        cout << "image " << i << " deleted " << endl;

    }

 cout << "image manager destroyed.." << endl;


}


