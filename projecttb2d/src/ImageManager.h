#ifndef _included_imagemanager_h
#define _included_imagemanager_h
#include <SFML/Graphics.hpp>
#include <iostream>

#define NBIMAGE 24

using namespace std;

class ImageManager{

private :


    sf::Texture * _storage[NBIMAGE];

    short int _indice;




public :

ImageManager();

int returnId() const;

sf::Texture * getImage(short);

~ImageManager();



};

#endif
