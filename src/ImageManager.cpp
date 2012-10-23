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

    _storage[0]->loadFromFile("image/hero3_v4_stand.png");
    //_storage[0]->createMaskFromColor(sf::Color(255,0,255));


    _storage[1]->loadFromFile("image/bricksheet2.png");
    //_storage[1]->createMaskFromColor(sf::Color(255,0,255));

    _storage[2]->loadFromFile("image/enemie2_v4_stand.png");
    //_storage[2]->createMaskFromColor(sf::Color(255,0,255));

    _storage[3]->loadFromFile("image/magic_sheet.png");
    //_storage[3]->createMaskFromColor(sf::Color(0,0,0));

    _storage[4]->loadFromFile("image/button_v2.png");
    //_storage[4]->createMaskFromColor(sf::Color(0,0,0));

    _storage[5]->loadFromFile("image/electricfence_v3.png");
    //_storage[5]->createMaskFromColor(sf::Color(0,0,0));

    _storage[6]->loadFromFile("image/effectsheet2.png");
    //_storage[6]->createMaskFromColor(sf::Color(255,0,255));


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


