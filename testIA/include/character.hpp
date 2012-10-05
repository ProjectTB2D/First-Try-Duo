#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED


#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Character
{

    public:

        Character(float, float);

        sf::CircleShape & getShape(); // pas de const pour pas rajouter des methodes inutilement (Pour un test evidemment)

        bool getDeplacement() const ;
        sf::Vector2f getPositionActuelle() const;
        sf::Vector2f getDestination() const;

        void setDeplacement(bool);
        void setDestination(sf::Vector2f);

    protected:

        sf::CircleShape _cs;
        bool _enDeplacement;
        sf::Vector2f _destination;


};

#endif // CHARACTER_HPP_INCLUDED
