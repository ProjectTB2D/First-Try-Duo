#ifndef FUNCTION_H
#define FUNCTION_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../include/Player.h"
#include "../include/Ennemi.h"
#include "../include/Character.h"
#include "../include/Bullet.h"
#include "../include/Object.h"
#include "../include/LifeBonus.h"
#include "../include/Interrupteur.h"
#include "../include/Door.h"
#include "../include/Block.h"
#include "../include/Launcher.h"
#include "../include/Reward.h"

#include "../include/tinyxml.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

struct tile{

    string id;
	char value;
	sf::Sprite * spr;
	bool solid;
	bool fullblock;
	bool solidBottom;
	bool endBlock;
	bool startBlock;

};

std::string int_to_string(int i);

int convertToIndex(float a, int LARGEUR_TILE);

int convertToView(int a, int LARGEUR_TILE);

int nbLignesCalcul(string chemin);

int nbColonnesCalcul(string chemin);

bool CollisionDecorLateral(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, Character & perso, tile** map, std::vector<Object*> objet);

int CollisionDecorLateralSide(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, Character & perso, tile** map, std::vector<Object*> objet);

bool CollisionDecorSol(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, Character & perso, tile** map, std::vector<Object*> objet);

bool surTerre(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, Character & perso, tile** map, std::vector<Object*> objet);

bool surBlockFin(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, Character & perso, tile** map);

bool CollisionDecorPlafond(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, Character & perso, tile** map, std::vector<Object*> objet);

bool CollisionDecorEnSaut(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, Character & perso, tile** map);

bool CollisionBulletDecor(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, Bullet & perso, tile * map[]);

bool CollisionBulletCharacter(Bullet & bullet, Character & character);

bool CollisionObjectCharacter(Object * objet, Character & character);

bool CollisionObjectBullet(Object * objet, Bullet & bullet);

bool CollisionObjectObject(Object * objet, Object * objet2);

bool CollisionObjectDecor(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, int nbObject, std::vector<Object*> objet, tile** map);

int idPlusProcheCharacter(Character & character, Character & player, std::vector<Character> & ennemi, const int & LARGEUR_MAP, const int & HAUTEUR_MAP);

//void mouvementCharacter(Character & character, Character & player, int & idCharProche, int & distanceEntreCharacter, std::vector<Character> & ennemi, tile** Matrice, const int & LARGEUR_TILE, const int & HAUTEUR_TILE, const int & NbColonnes, const int & NbLignes);

bool EssaiDeplacementX(tile** Matrice, float & frameTime, Character & player, int speedX, const int & LARGEUR_TILE, const int & HAUTEUR_TILE, const int & NbColonnes, const int & NbLignes, std::vector<Object*> objet);

bool EssaiDeplacementY(tile** Matrice, float & frameTime, Character & player, int speedY, const int & LARGEUR_TILE, const int & HAUTEUR_TILE, const int & NbColonnes, const int & NbLignes, std::vector<Object*> objet);

void createMap(string map, tile*** Matrice, Texture & tileSet1, Texture & myInterrupteur, Texture & myDoor, Texture & myCheckpoint, Texture & reward, std::vector<Object*> &objet);

int nbColonnesMap(string map);

int nbLignesMap(string map);

int largeurTileMap(string map);

void deleteMatrice(tile*** Matrice, int nbColonnes, int nbLignes, std::vector<Object*> &objet);

void GoToNextMap(string & Map_EnCours, unsigned int & MapActuelle, vector<string> & Maps);

void PlayerPosition(Character & player, tile*** Matrice, int nbColonnes, int nbLignes, int largeurTile, string lieu);

void fondu(Character & player, const Vector2f & WINDOW_SIZE, Shape & fondu, int transparence, string sens);

void menu(sf::RenderWindow & app, bool inLoop, bool & changementDeMap, sf::View & vue, sf::Vector2f size, bool & startGame, vector<string> & vecMap, string & Map_EnCours, unsigned int & Map_Actuelle);

void menuMap(sf::RenderWindow & app, bool inLoop, bool & changementDeMap, sf::View & vue, sf::Vector2f size, bool & startGame, vector<string> & vecMap, string & Map_EnCours, unsigned int & Map_Actuelle);

void save(int numMap, int score, float temps);

#endif // FUNCTION_H
