#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "src/character.hpp"
#include "src/Node.h"
#include "src/Obstacle.h"

using namespace std;
using namespace sf;

const float vitesseChara = 2.0f;
const Vector2f WINDOW_SIZE(800,600);


int main()
{
    // Fenêtre
    RenderWindow app(VideoMode((int)WINDOW_SIZE.x, (int)WINDOW_SIZE.y, 32), "Projet de test de l'IA");

	// Frames Per Second (FPS)
        app.setFramerateLimit(60); // limite la fenêtre à 60 images par seconde

        // NE PAS mettre les deux en meme temps
        //app.setVerticalSyncEnabled(true);



    Texture rock;

    if (!rock.loadFromFile("ressource/images/rocher.png")) // Si le chargement a échoué
    {
        cerr<<"Erreur durant le chargement de l'image"<<endl;
    }



	Clock clockFrame; // Permettra de calculer les FPS

	RectangleShape background(Vector2f((int)WINDOW_SIZE.x, (int)WINDOW_SIZE.y));
    background.setFillColor(sf::Color(100,125,180));

    // Création d'un rocher

    //RectangleShape rocher(Vector2f(144.0f, 135.0f));
    //rocher.setTexture(&rock);
    //rocher.setOutlineColor(sf::Color(255,0,0));
    //rocher.setPosition(350.0f, 250.0f);

    Obstacle obs(rock, sf::Vector2f(350, 250));

    //rocher.setTextureRect(IntRect(0, 0, 50, 50));

    // Création des personnages (cercles)

    vector<Character*> vectorCharacter;

    Character * selection = NULL;

    /*CircleShape c1(10.0f);
    CircleShape c2(10.0f);
    CircleShape c3(10.0f);
    CircleShape c4(10.0f);

    c1.setFillColor(sf::Color::Blue);
    c1.setPosition(25.0f, 50.0f);

    c2.setFillColor(sf::Color::Blue);
    c2.setPosition(50.0f, 150.0f);

    c3.setFillColor(sf::Color::Blue);
    c3.setPosition(75.0f, 250.0f);

    c4.setFillColor(sf::Color::Blue);
    c4.setPosition(150.0f, 350.0f);*/

    Character c1(25.0f, 50.0f);
    Character c2(50.0f, 150.0f);
    Character c3(75.0f, 250.0f);
    Character c4(150.0f, 350.0f);
    Character c5(200.0f, 375.0f);


    vectorCharacter.push_back(&c1);
    vectorCharacter.push_back(&c2);
    vectorCharacter.push_back(&c3);
    vectorCharacter.push_back(&c4);
    vectorCharacter.push_back(&c5);

    // Boucle principale
    while (app.isOpen())
    {
        app.clear();

        // On récupère le temps de rafraichissement entre chaque frame pour ajuster la vitesse du jeu
        //float frameTime = clockFrame.restart().asSeconds();


		Event event;

        while (app.pollEvent(event))
        {

			if(event.type == sf::Event::KeyReleased && event.key.code == Keyboard::Space){

			}

			if(event.type == sf::Event::KeyReleased && event.key.code == Keyboard::Down){

			}

			if(event.type == sf::Event::KeyReleased && event.key.code == Keyboard::Right){

			}

			if(event.type == sf::Event::KeyReleased && event.key.code == Keyboard::Left){

			}
			if(event.type == sf::Event::KeyReleased && event.key.code == Keyboard::LShift){

			}


            switch(event.type)
			{
				case Event::Closed : // Croix de fermeture
					app.close();
					break;

				case Event::KeyPressed : // Appui sur une touche
				{
					switch(event.key.code)
					{
						case Keyboard::Escape : // Touche echap
							app.close();
							break;

                        default:
                            break;
					}
				}



				default:
                    break;
			}

        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {

            if(selection != NULL)
            {
                selection->getShape().setFillColor(sf::Color::Blue);
                selection = NULL; // On supprime le pointeur de cercle
            }


            /*for(int unsigned i = 0; i < vectorCharacter.size(); i++){

                vectorCharacter[i]->setFillColor(sf::Color::Blue); // On met tous les cercles en bleu (deselectionne)
            }*/
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            // le bouton gauche est enfoncé


            Vector2i souris = Mouse::getPosition(app);

            //cout << "X : " << souris.x << " Y : " << souris.y << endl;


            for(int unsigned i = 0; i < vectorCharacter.size(); i++){

                // Selection

                if(selection == NULL)
                {
                    if(souris.x >= (vectorCharacter[i]->getShape().getPosition().x - 10.0f) && souris.x <= (vectorCharacter[i]->getShape().getPosition().x + 10.0f))
                    {
                        if(souris.y >= (vectorCharacter[i]->getShape().getPosition().y - 10.0f) && souris.y <= (vectorCharacter[i]->getShape().getPosition().y + 10.0f))
                        {

                            selection = vectorCharacter[i]; // On SAVE le pointeur du cercle

                            selection->getShape().setFillColor(sf::Color::Red); // On le met en Rouge
                        }
                    }
                }



                // On définit la destination avec un clique gauche

                if(selection != NULL) // cad un objet selectioné
                {
                    for(int unsigned j = 0; j < vectorCharacter.size(); j++){

                        if(souris.x < vectorCharacter[j]->getShape().getPosition().x || souris.x > (vectorCharacter[j]->getShape().getPosition().x + 20.0f))
                        {
                            if(souris.y < vectorCharacter[j]->getShape().getPosition().y || souris.y > (vectorCharacter[j]->getShape().getPosition().y + 20.0f))
                            {
                                Vector2f desti(souris.x, souris.y);
                                selection->setDestination(desti);
                                selection->setDeplacement(true);
                            }
                        }
                    }
                }

            }
        }

        for(int unsigned i = 0; i < vectorCharacter.size(); i++)
        {
            // Deplacement


            if(vectorCharacter[i]->getDeplacement())
            {

              // calcul de deplacement selon 2 points

              float disx = vectorCharacter[i]->getPositionActuelle().x - vectorCharacter[i]->getDestination().x;
              float disy = vectorCharacter[i]->getPositionActuelle().y - vectorCharacter[i]->getDestination().y;

              float angle_rad = atan2(disy, disx);

              //cout << "angle rad = " << angle_rad << endl;
              //cout << "angle deg = " << angle_rad*180/3.14 << endl;

              vectorCharacter[i]->getShape().move(-vitesseChara*cos(angle_rad), -vitesseChara*sin(angle_rad));

              float distance = sqrt((disx*disx) + (disy*disy));

              if(distance <  3.0f)
              {
                  if(vectorCharacter[i]->getNbDestination() > 1)
                  {
                    vectorCharacter[i]->destinationSuivante();
                  }
                  else
                  {
                    vectorCharacter[i]->setDeplacement(false);
                  }
              }


              //cout << "distance left = " << distance << endl;

                    //vectorCharacter[i]->getShape().move(xMove * vitesseChara, yMove * vitesseChara);

                    //cout << "Je suis l'objet " << i << " et ma destination est " << vectorCharacter[i]->getDestination().x << " " << vectorCharacter[i]->getDestination().y << endl;
            }



            // Collision

            if(vectorCharacter[i]->getRect().intersects(obs.getRect()))
            {
               //cout << "COLLISION " << i << " : " << vectorCharacter[i]->getShape().getLocalBounds().left << endl;

                // Calcul du chemin a prendre (On ne le fait que a la premiere collision
               if(!vectorCharacter[i]->getInObstacle())
               {
                obs.makeRoad(vectorCharacter[i]);

                vectorCharacter[i]->setInObstacle(true);
               }

            }
            else
            {
                if(vectorCharacter[i]->getInObstacle())
                    vectorCharacter[i]->setInObstacle(false);
            }





        }



		app.setView(app.getDefaultView());

        app.draw(background);

        app.draw(c1.getShape());
        app.draw(c2.getShape());
        app.draw(c3.getShape());
        app.draw(c4.getShape());
        app.draw(c5.getShape());

        obs.display(app);

        // Affichage de la fenêtre à l'écran
        app.display();
    }

    return EXIT_SUCCESS;
}

