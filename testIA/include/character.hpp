#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED


#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Character
{

    public:

        Character(float, float);

        sf::CircleShape getShape();

    protected:

        sf::CircleShape _cs;
        bool _enDeplacement;
        sf::Vector2f _destination;


};

#endif // CHARACTER_HPP_INCLUDED
