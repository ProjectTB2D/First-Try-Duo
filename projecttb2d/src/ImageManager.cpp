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


    _storage[0]->loadFromFile("images/character.png");
    _storage[1]->loadFromFile("images/tileTest.png");
    _storage[2]->loadFromFile("images/bullet1.png");
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


