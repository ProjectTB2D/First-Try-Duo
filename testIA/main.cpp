#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;


const Vector2f WINDOW_SIZE(800,600);


int main()
{
    // Fen�tre
    RenderWindow app(VideoMode((int)WINDOW_SIZE.x, (int)WINDOW_SIZE.y, 32), "Projet de test de l'IA");

	// Frames Per Second (FPS)
        app.setFramerateLimit(60); // limite la fen�tre � 60 images par seconde

        // NE PAS mettre les deux en meme temps
        //app.setVerticalSyncEnabled(true);



    Texture rock;

    if (!rock.loadFromFile("images/rocher.png")) // Si le chargement a �chou�
    {
        cerr<<"Erreur durant le chargement de l'image"<<endl;
    }



	Clock clockFrame; // Permettra de calculer les FPS

	RectangleShape background(Vector2f((int)WINDOW_SIZE.x, (int)WINDOW_SIZE.y));
    background.setFillColor(sf::Color(100,125,180));

    // Cr�ation d'un rocher

    RectangleShape rocher(Vector2f(144.0f, 135.0f));
    rocher.setTexture(&rock);
    rocher.setPosition(350.0f, 250.0f);
    //rocher.setTextureRect(IntRect(0, 0, 50, 50));

    // Cr�ation des personnages (cercles)

    vector<CircleShape*> vectorCharacter;

    CircleShape * selection = NULL;

    CircleShape c1(10.0f);
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
    c4.setPosition(150.0f, 350.0f);


    vectorCharacter.push_back(&c1);
    vectorCharacter.push_back(&c2);
    vectorCharacter.push_back(&c3);
    vectorCharacter.push_back(&c4);



    // Boucle principale
    while (app.isOpen())
    {
        app.clear();

        // On r�cup�re le temps de rafraichissement entre chaque frame pour ajuster la vitesse du jeu
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
            selection = NULL; // On supprime le pointeur de cercle

            for(int unsigned i = 0; i < vectorCharacter.size(); i++){

                vectorCharacter[i]->setFillColor(sf::Color::Blue); // On met tous les cercles en bleu (deselectionne)
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            // le bouton gauche est enfonc�


            Vector2i souris = Mouse::getPosition(app);

            cout << "X : " << souris.x << " Y : " << souris.y << endl;


            for(int unsigned i = 0; i < vectorCharacter.size(); i++){

                if(souris.x >= vectorCharacter[i]->getPosition().x && souris.x <= (vectorCharacter[i]->getPosition().x + 20.0f))
                {
                    if(souris.y >= vectorCharacter[i]->getPosition().y && souris.y <= (vectorCharacter[i]->getPosition().y + 20.0f))
                    {
                        if(selection != NULL) // On change la couleur du pr�c�dent selectionn�
                            selection->setFillColor(sf::Color::Blue);

                        selection = vectorCharacter[i]; // On SAVE le pointeur du cercle

                        selection->setFillColor(sf::Color::Red); // On le met en Rouge
                    }
                }


            }
        }


		app.setView(app.getDefaultView());

        app.draw(background);

        app.draw(c1);
        app.draw(c2);
        app.draw(c3);
        app.draw(c4);

        app.draw(rocher);

        // Affichage de la fen�tre � l'�cran
        app.display();
    }

    return EXIT_SUCCESS;
}

