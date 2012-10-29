#include "../include/Function.h"

//	Fonction qui renvoi l'index (en x ou y) de la position (x ou y) passé en paramètre.

std::string int_to_string(int i){

    std::string s;
    std::stringstream out;
    out << i;
    s = out.str();

    return s;

}

int convertToIndex(float a, int LARGEUR_TILE){

    return((int)(a/LARGEUR_TILE));
}

int convertToView(int a, int LARGEUR_TILE){

    return(a*LARGEUR_TILE);
}

int nbLignesCalcul(string chemin){

	int NbLignesCalcul = 0;

	ifstream fichier(chemin.c_str());

	if(fichier)
    {
        // Modifier le 100000 si le fichier peut avoir plus de 100000 lignes <<<<<<< IMPORTANT
         while(fichier.ignore(100000, '\n'))
        {
            ++NbLignesCalcul;
        }
    }

	fichier.close(); //On ferme le fichier*/

	return NbLignesCalcul;
}

int nbColonnesCalcul(string chemin){

	int NbColonnesCalcul = 0;

	ifstream fichier(chemin.c_str());

	if(fichier)
    {
		string contenu;
		getline(fichier, contenu);

		NbColonnesCalcul = contenu.length();
    }

	fichier.close(); //On ferme le fichier

	return NbColonnesCalcul;
}

bool CollisionDecorLateral(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, Character & perso, tile** map, std::vector<Object*> objet)
{
	int xmin,xmax,ymin,ymax,i,j;

	xmin = perso.getLeftSide() / LARGEUR_TILE;
	ymin = perso.getTopSide() / HAUTEUR_TILE;
	xmax = (perso.getRightSide() -1) / LARGEUR_TILE;
	ymax = (perso.getBottomSide() - 7.0f) / HAUTEUR_TILE;

	if (xmin<0 || ymin<0 || xmax >= NbColonnes || ymax >= NbLignes)		// Personnage en dehors de la map
		return true;

	for(i=xmin;i<=xmax;i++)
	{
		for(j=ymin;j<=ymax;j++)
		{
			if (map[i][j].solid){
				//cout << "collision lateral" << endl;
				return true;
			}
		}
	}

    for(int unsigned i = 0; i < objet.size(); i++){

        if(objet[i]->getSolid()){

            if(CollisionObjectCharacter(objet[i], perso))
                return true;
        }
    }

	return false;
}

int CollisionDecorLateralSide(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, Character & perso, tile** map, std::vector<Object*> objet)
{
	int xmin,xmax,ymax;

	xmin = (perso.getLeftSide() - 5.0f) / LARGEUR_TILE;
	xmax = (perso.getRightSide() + 5.0f) / LARGEUR_TILE;
	ymax = (perso.getBottomSide() - 7.0f) / HAUTEUR_TILE;


    if (map[xmin][ymax].solid){
        //cout << "collision lateral gauche" << endl;
        return 1;
    }


    if (map[xmax][ymax].solid){
        //cout << "collision lateral droite" << endl;
        return 2;
    }

    // PAS sur les objets pour le moment

    /*for(int unsigned i = 0; i < objet.size(); i++){

        if(objet[i]->getSolid()){

            if(CollisionObjectCharacter(objet[i], perso))
                return "";
        }
    }*/

    return 0;

}

bool CollisionDecorEnSaut(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, Character & perso, tile** map)
{
	int xmin,xmax,ymin,ymax,i,j;

	xmin = perso.getLeftSide() / LARGEUR_TILE;
	ymin = perso.getTopSide() / HAUTEUR_TILE;
	xmax = (perso.getRightSide() -1) / LARGEUR_TILE;
	ymax = (perso.getBottomSide() -1) / HAUTEUR_TILE;

	if (xmin<0 || ymin<0 || xmax >= NbColonnes || ymax >= NbLignes)		// Personnage en dehors de la map
		return true;

	for(i=xmin;i<=xmax;i++)
	{
		for(j=ymin;j<=ymax;j++)
		{
			if (map[i][j].solid)
				return true;

			if (map[i][j].solidBottom && !perso.getDescendre())
				return true;
		}
	}
	return false;
}


bool CollisionDecorSol(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, Character & perso, tile** map, std::vector<Object*> objet)
{
	int i, basXG, basXD, basY;
	Character test;
	test = perso;

	test.setY(test.getY() - 5.0f);

	basXG = convertToIndex(perso.getLeftSide() + 2.0f ,LARGEUR_TILE); // X MIN
	basXD = convertToIndex(perso.getRightSide() - 4.0f ,LARGEUR_TILE); // X MAX
	basY = convertToIndex(perso.getBottomSide() - 5.0f ,HAUTEUR_TILE); // Y

/*
	if (map[basXG][basY].solid)
		return true;

	if (map[basXM][basY].solid)
		return true;

	if (map[basXD][basY].solid)
		return true;

	if (map[basXG][basY].solidBottom && !perso.getDescendre() && !perso.enSaut())
		return true;

	if (map[basXM][basY].solidBottom && !perso.getDescendre() && !perso.enSaut())
		return true;

	if (map[basXD][basY].solidBottom && !perso.getDescendre() && !perso.enSaut())
		return true;

*/

    for(i=basXG;i<=basXD;i++)
	{
        if (map[i][basY].solid){
            //cout << "collision" << endl;
            return true;
        }


        if (map[i][basY].solidBottom && !perso.getDescendre() && !perso.enSaut()){
            //cout << "collision" << endl;
            return true;
        }
	}

	for(int unsigned i = 0; i < objet.size(); i++){

        if(objet[i]->getSolid()){

            if(CollisionObjectCharacter(objet[i], test))
                return true;
        }
    }


   // cout << "pas collision" << endl;
	return false;
}

bool surTerre(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, Character & perso, tile** map, std::vector<Object*> objet)
{
	int i, basXG, basXD, basY;
	Character test;
	test = perso;

	test.setY(test.getY() + 8.0f);

	basXG = convertToIndex(perso.getLeftSide() + 2.0f ,LARGEUR_TILE);
	basXD = convertToIndex(perso.getRightSide() - 4.0f ,LARGEUR_TILE);
	basY = convertToIndex(perso.getBottomSide() + 8.0f ,HAUTEUR_TILE);


	for(i=basXG;i<=basXD;i++)
	{
        if (map[i][basY].solid){
            //cout << "sur terre" << endl;
            return true;
        }


        if (map[i][basY].solidBottom && !perso.getDescendre() && !perso.enSaut()){
            //cout << "sur terre" << endl;
            return true;
        }
	}



    for(int unsigned i = 0; i < objet.size(); i++){

        if(objet[i]->getSolid()){

            if(CollisionObjectCharacter(objet[i], test))
                return true;
        }
    }

    //cout << "PAS sur terre" << endl;
	return false;
}


bool surBlockFin(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, Character & perso, tile** map)
{
	int basXG, basXM, basXD, basY;

	basXG = convertToIndex(perso.getLeftSide() + 2.0f ,LARGEUR_TILE);
	basXM = convertToIndex(perso.getMiddleSide() ,LARGEUR_TILE);
	basXD = convertToIndex(perso.getRightSide() - 4.0f ,LARGEUR_TILE);
	basY = convertToIndex(perso.getBottomSide() + 4.0f ,HAUTEUR_TILE);


	if (map[basXG][basY].endBlock)
		return true;

	if (map[basXM][basY].endBlock)
		return true;

	if (map[basXD][basY].endBlock)
		return true;


	return false;
}

bool CollisionDecorPlafond(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, Character & perso, tile** map, std::vector<Object*> objet)
{
	int i, hautXG, hautXD, hautY;

	// Il faudra rajouter plus de point en fonction du personnage (si celui devient une boule ou non) <<=== IMPORTANT !!

	hautXG = convertToIndex(perso.getLeftSide() + 2.0f ,LARGEUR_TILE); // x min
	hautXD = convertToIndex(perso.getRightSide() - 4.0f ,LARGEUR_TILE); // x max
	hautY = convertToIndex(perso.getTopSide() + 0.0f, HAUTEUR_TILE); // Y



	for(i=hautXG;i<=hautXD;i++)
	{
        if (map[i][hautY].solid){
            //cout << "collision lateral" << endl;
            return true;
        }


        if (map[i][hautY].solidBottom && !perso.getDescendre() && !perso.enSaut())
            return true;
	}

	for(int unsigned i = 0; i < objet.size(); i++){

        if(objet[i]->getSolid()){

            if(CollisionObjectCharacter(objet[i], perso))
                return true;
        }
    }

	return false;
}


bool CollisionBulletDecor(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, Bullet & bullet, tile * map[])
{
	int xmin,xmax,ymin,ymax,i,j;

	xmin = bullet.getLeftSide() / LARGEUR_TILE;
	ymin = bullet.getTopSide() / HAUTEUR_TILE;
	xmax = (bullet.getRightSide() -1) / LARGEUR_TILE;
	ymax = (bullet.getBottomSide() -1) / HAUTEUR_TILE;

	if (xmin<0 || ymin<0 || xmax >= NbColonnes || ymax >= NbLignes)		// Personnage en dehors de la map
		return true;

	for(i=xmin;i<=xmax;i++)
	{
		for(j=ymin;j<=ymax;j++)
		{
			if (map[i][j].solid)	//	Matrice[mxSaut][mySaut].solid
				return true;
		}
	}
	return false;
}

bool CollisionBulletCharacter(Bullet & bullet, Character & character)
{
	int xminBullet,xmaxBullet,yminBullet,ymaxBullet;
	int xminCharacter,xmaxCharacter,yminCharacter,ymaxCharacter;

	xminBullet = bullet.getLeftSide();
	yminBullet = bullet.getTopSide();
	xmaxBullet = bullet.getRightSide();
	ymaxBullet = bullet.getBottomSide();

	xminCharacter = character.getLeftSide();
	yminCharacter = character.getTopSide();
	xmaxCharacter = character.getRightSide();
	ymaxCharacter = character.getBottomSide();

	if (xminBullet > xmaxCharacter)
		return false;

	if (xmaxBullet < xminCharacter)
		return false;

	if (yminBullet > ymaxCharacter)
		return false;

	if (ymaxBullet < yminCharacter)
		return false;

	return true;
}

bool CollisionObjectCharacter(Object * objet, Character & character)
{
	int xminObjet,xmaxObjet,yminObjet,ymaxObjet;
	int xminCharacter,xmaxCharacter,yminCharacter,ymaxCharacter;

	xminObjet = objet->getLeftSide();
	yminObjet = objet->getTopSide();
	xmaxObjet = objet->getRightSide();
	ymaxObjet = objet->getBottomSide();

	xminCharacter = character.getLeftSide();
	yminCharacter = character.getTopSide();
	xmaxCharacter = character.getRightSide();
	ymaxCharacter = character.getBottomSide();

	if (xminObjet > xmaxCharacter)
		return false;

	if (xmaxObjet < xminCharacter)
		return false;

	if (yminObjet > ymaxCharacter)
		return false;

	if (ymaxObjet < yminCharacter)
		return false;

	return true;
}

bool CollisionObjectBullet(Object * objet, Bullet & bullet)
{
    int xminBullet,xmaxBullet,yminBullet,ymaxBullet;
	int xminObjet,xmaxObjet,yminObjet,ymaxObjet;

	xminBullet = bullet.getLeftSide();
	yminBullet = bullet.getTopSide();
	xmaxBullet = bullet.getRightSide();
	ymaxBullet = bullet.getBottomSide();

	xminObjet = objet->getLeftSide();
	yminObjet = objet->getTopSide();
	xmaxObjet = objet->getRightSide();
	ymaxObjet = objet->getBottomSide();

	if (xminBullet > xmaxObjet)
		return false;

	if (xmaxBullet < xminObjet)
		return false;

	if (yminBullet > ymaxObjet)
		return false;

	if (ymaxBullet < yminObjet)
		return false;

	return true;
}

bool CollisionObjectObject(Object * objet, Object * objet2)
{
	int xminObjet,xmaxObjet,yminObjet,ymaxObjet;
	int xminObjet2,xmaxObjet2,yminObjet2,ymaxObjet2;

	xminObjet = objet->getLeftSide() + 1.0f;
	yminObjet = objet->getTopSide() + 1.0f;
	xmaxObjet = objet->getRightSide() - 1.0f;
	ymaxObjet = objet->getBottomSide() - 1.0f;

	xminObjet2 = objet2->getLeftSide() + 1.0f;
	yminObjet2 = objet2->getTopSide() + 1.0f;
	xmaxObjet2 = objet2->getRightSide() - 1.0f;
	ymaxObjet2 = objet2->getBottomSide() - 1.0f;

	if (xminObjet2 > xmaxObjet)
		return false;

	if (xmaxObjet2 < xminObjet)
		return false;

	if (yminObjet2 > ymaxObjet)
		return false;

	if (ymaxObjet2 < yminObjet)
		return false;

	return true;
}

bool CollisionObjectDecor(int LARGEUR_TILE, int HAUTEUR_TILE, int NbColonnes, int NbLignes, int nbObject, std::vector<Object*> objet, tile** map)
{

    int xmin,xmax,ymin,ymax,i,j;

	xmin = objet[nbObject]->getLeftSide() / LARGEUR_TILE;
	ymin = objet[nbObject]->getTopSide() / HAUTEUR_TILE;
	xmax = (objet[nbObject]->getRightSide() -1) / LARGEUR_TILE;
	ymax = (objet[nbObject]->getBottomSide() -1) / HAUTEUR_TILE;

	if (xmin<0 || ymin<0 || xmax >= NbColonnes || ymax >= NbLignes)		// Personnage en dehors de la map
		return true;

	for(i=xmin;i<=xmax;i++)
	{
		for(j=ymin;j<=ymax;j++)
		{
			if (map[i][j].solid)	//	Matrice[mxSaut][mySaut].solid
				return true;
		}
	}

    int unsigned a = nbObject;

    for(int unsigned k = 0; k < objet.size(); k++){

        if(k != a){

            if(objet[k]->getSolid()){

                if(CollisionObjectObject(objet[nbObject], objet[k]))
                {
                    return true;
                }

            }
        }
    }

    return false;

}




// Il faut au moins un bot (dans un vector) et un player pour utiliser cette fonction

int idPlusProcheCharacter(Character & character, Character & player, std::vector<Character> & ennemi, const int & LARGEUR_MAP, const int & HAUTEUR_MAP)
{
	int idPlusProche = 999; // Nombre pour pas de résultats ou erreur

	int positionCharacterATester = (character.getX() + (character.GetSprite().getLocalBounds().width)/2); // On cherche le character le plus procher de ce point
	int positionSecondCharacter;
	int positionPlayer = (player.getX() + (player.GetSprite().getLocalBounds().width)/2); // Position du player

	int distancePlusProcheCharacter = LARGEUR_MAP + HAUTEUR_MAP;
	int distanceEntreCharacter;


	for(int unsigned j = 0; j < ennemi.size(); j++){
		positionSecondCharacter = (ennemi[j].getX() + (ennemi[j].GetSprite().getLocalBounds().width)/2);

		distanceEntreCharacter = positionCharacterATester - positionSecondCharacter;

		if(distanceEntreCharacter != 0){ // Pas lui meme
			if(character.getEquipe() != ennemi[j].getEquipe()){	// Pas quelqu'un de son équipe
				if((abs)(distanceEntreCharacter) <= distancePlusProcheCharacter){	// Si inférieur a la plus petite distance

					distancePlusProcheCharacter = distanceEntreCharacter;
					idPlusProche = j;
				}
			}
		}
	}

	distanceEntreCharacter = positionCharacterATester - positionPlayer;

	if(distanceEntreCharacter != 0){ // Pas lui meme
		if(character.getEquipe() != player.getEquipe()){	// Pas quelqu'un de son équipe
			if((abs)(distanceEntreCharacter) <= distancePlusProcheCharacter){	// Si inférieur a la plus petite distance

				distancePlusProcheCharacter = distanceEntreCharacter;
				idPlusProche = 666; // Nombre pour le player
			}
		}
	}


	// Egal a 666 si c'est le player

	return idPlusProche;
}
/*
void mouvementCharacter(Character & character, Character & player, int & idCharProche, int & distanceEntreCharacter, std::vector<Character> & vectorCharacter, tile** Matrice, const int & LARGEUR_TILE, const int & HAUTEUR_TILE, const int & NbColonnes, const int & NbLignes)
{


		int mxDroite = convertToIndex(character.getRightSide() + 5, LARGEUR_TILE); // largeur image + 1
		int myDroite = convertToIndex(character.getBottomSide() - 15, LARGEUR_TILE);

		int mxGauche = convertToIndex(character.getLeftSide() - 5, LARGEUR_TILE); // largeur image + 1
		int myGauche = convertToIndex(character.getBottomSide() - 15, LARGEUR_TILE);

		int mxSaut = convertToIndex(character.getLeftSide() + (character.GetSprite().GetSize().x)/2, LARGEUR_TILE);
		int mySaut = convertToIndex(character.getBottomSide() + 3, LARGEUR_TILE);

		int mxHaut = convertToIndex(character.getLeftSide() + (character.GetSprite().GetSize().x)/2, LARGEUR_TILE);
		int myHaut = convertToIndex(character.getTopSide() + 3, LARGEUR_TILE);



		// === Conditions pour le saut ==

		if(!character.enSaut()){

			if(!character.surTerre())
				character.deplacementBasY();

			if(CollisionDecorEnSaut(LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, character, Matrice)){

				character.setSurTerre(true);
			}else{
				character.setSurTerre(false);
			}

		}else{

			if(character.getClockSaut() < 0.7f){	// On fait monter le personnage pdt 0.5 sec
				if(!Matrice[mxHaut][myHaut].solid){
					character.saut();
					character.setSurTerre(false);
				}else{
					character.setEnSaut(false);
				}
			}else{
				character.setEnSaut(false);
			}
		}

		//	===================================================

		// === Conditions pour déplacer l'ennemi à gauche ou à droite ==

		if((abs)(distanceEntreCharacter) <= 80.0f){
			// pas de mouvement a gauche ni a droite
		}else if(distanceEntreCharacter > 0){
			if(!Matrice[mxGauche][myGauche].solid){
				character.deplacementGaucheX();
			}else{
				if(character.surTerre()){
					character.setEnSaut(true);
					character.setSurTerre(false);
					character.resetClockSaut();
				}
			}

			character.setDirectionGauche();
		}else if(distanceEntreCharacter < 0){
			if(!Matrice[mxDroite][myDroite].solid){
				character.deplacementDroiteX();
			}else{
				if(character.surTerre()){
					character.setEnSaut(true);
					character.setSurTerre(false);
					character.resetClockSaut();
				}
			}

			character.setDirectionDroite();
		}

		//	===================================================


		// Si le character le plus proche est plus haut que l'ennemi, il va essayer de sauter pour le toucher

		// (On rajoute une marge de 20px) <<=== A AJUSTER

		if(idCharProche == 666){
			if(player.getTopSide() + 100.0f < character.getTopSide()){
				if(character.surTerre()){
					character.setEnSaut(true);
					character.setSurTerre(false);
					character.resetClockSaut();
				}
			}
		}else{
			if(vectorCharacter[idCharProche].getTopSide() + 100.0f  < character.getTopSide()){
				if(character.surTerre()){
					character.setEnSaut(true);
					character.setSurTerre(false);
					character.resetClockSaut();
				}
			}
		}
}*/

bool EssaiDeplacementX(tile** Matrice, float & frameTime, Character & player, int speedX, const int & LARGEUR_TILE, const int & HAUTEUR_TILE, const int & NbColonnes, const int & NbLignes, std::vector<Object*> objet)
{
	Character test;
	test = player;


	test.setX(test.getX() + (int)(speedX *  frameTime));

	//cout << "SpeedX : " << (speedX *  app.GetFrameTime()) << endl;
	//cout << "Vrai SpeedX : " << speedX << endl;

	if(!CollisionDecorLateral(LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, test, Matrice, objet)){

		player = test;
		player.setX(test.getX());

		// True pas de collision
		return true;
	}

	for(int i=0;i < 3; i++){

		float signe = 0;

		if(player.getSpeed() > 0)
			signe = 2;
		else if(player.getSpeed() < 0)
			signe = -2;

		test.setX(player.getX() + signe);

		if(!CollisionDecorLateral(LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, test, Matrice, objet)){

			player = test;
			player.setX(test.getX());

			// True pas de collision
			return true;
		}

	}

	// On met la vitesse à 0 lors d'une collision
	player.setSpeed(0);

	// False car collision
	return false;
}

bool EssaiDeplacementY(tile** Matrice, float & frameTime, Character & player, int speedY, const int & LARGEUR_TILE, const int & HAUTEUR_TILE, const int & NbColonnes, const int & NbLignes, std::vector<Object*> objet)
{

	if(surBlockFin(LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, player, Matrice)){
		return true;
	}



	Character test;
	test = player;


	//test.setX(test.getX() + test.getSpeed());
	test.setY(test.getY() - (int)(speedY * frameTime));

	//cout << "SpeedY : " << (speedY *  app.GetFrameTime()) << endl;
	//cout << "Vrai SpeedY : " << speedY << endl;

	if(test.getSpeedY() < 0){
		if(!CollisionDecorSol(LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, test, Matrice, objet)){

			player = test;
			player.setY(test.getY());
            //cout << "pas collision" << endl;

		}

	}
	else{

		if(!CollisionDecorPlafond(LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, test, Matrice, objet)){

			player = test;
			player.setY(test.getY());

		}
		else{
			player.setSpeedY(0);
		}
	}

	if(surTerre(LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, player, Matrice, objet)){

		for(int i=0;i < 3; i++){

            float signe = 0;

            if(player.getSpeedY() > 0)
                signe = 0.0f;
            else if(player.getSpeedY() < 0)
                signe = -1.0f;

            test = player;
            test.setY(test.getY() - signe);

           //cout << "speed y : " << player.getSpeed()  << endl;

            if(!surTerre(LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, player, Matrice, objet)){

                cout << "Modif position : "<< i << endl;
                player = test;

                //player.setY(test.getY());

                // True pas de collision
                //return true;
            }
            else{

               //cout << "collision" << endl;

                player.setSurTerre(true);
                player.setSpeedY(0);
            }

        }








	}
	else{
		player.setSurTerre(false);
		//cout << "pas collision" << endl;
	}




	// Car pas en contact avec un block de fin

	return false;
}

void createMap(string map, tile*** Matrice, Texture & tileSet1, Texture & myInterrupteur, Texture & myDoor, Texture & myCheckpoint, Texture & reward, std::vector<Object*> &objet)
{
    // Récupération des données dans le fichier TMX (Tiled Map Editor) / Traitement XML

    TiXmlDocument document(map.c_str());
    if(!document.LoadFile()){//si on n'arrive pas à charger le fichier
        cout << "error : N°" << document.ErrorId() << " : " << document.ErrorDesc() << endl;
        //return 1;
    }
    else{
        cout << " Ouverture reussie " << endl;
    }


    TiXmlHandle handle(&document);
    string source, elemName, colonnes, lignes, largeur, hauteur;

    int nbColonnes = 0, nbLignes = 0, largeurTile = 0, hauteurTile = 0;

    // on recherche les enfants Direct de Map
    TiXmlElement *element = handle.FirstChildElement().FirstChildElement().Element();


    int i = 0;
    while (element){
        //cout << element->Value() << endl; //l'atribut nom
        //cout << element->GetText() << endl;//Le texte entre les balises

        elemName = element->Value();

       if(elemName == "layer"){

            colonnes = element->Attribute("width");
            lignes = element->Attribute("height");

            nbColonnes = atoi(colonnes.c_str());
            nbLignes = atoi(lignes.c_str());

        }
        else if(elemName == "tileset"){

            largeur = element->Attribute("tilewidth");
            hauteur = element->Attribute("tileheight");

            largeurTile = atoi(largeur.c_str());
            hauteurTile = atoi(hauteur.c_str());

        }

        element = element->NextSiblingElement(); // aller à l'élément suivant
        i++;
        //cout << i << endl;


    }

    // On crée la Matrice avec le nb de colonnes et de lignes déterminés précédemment

    cout << "nb colonnes : " << nbColonnes << " nb lignes : " << nbLignes << endl;

    (*Matrice) = 0;

    (*Matrice) = new tile*[nbColonnes];

	for(int i=0; i<nbColonnes; i++)
		(*Matrice)[i] = new tile[nbLignes];

    // ----------------------------------------------------------------------------




    // On recherche les enfants de Data (donc toutes les tiles)
    element = handle.FirstChildElement().FirstChildElement("layer").FirstChildElement("data").FirstChildElement().Element();

    i = 0;
    int j = 0;

    while (element){

        //cout << element->GetText() << endl;//Le texte entre les balises


        if(i < nbColonnes){
            //cout << element->Value() << endl; //l'atribut nom

            string value = element->Attribute("gid");
            //char* val;
            //val = (char*)value.c_str();

            (*Matrice)[i][j].id = value;
            (*Matrice)[i][j].spr = 0;

           /* cout << "i :" << i << endl;
            cout << "j :" << j << endl;
            cout << "value :" << value << endl;*/

            i++; // On passe a la tile suivante
            element = element->NextSiblingElement(); // aller à l'élément suivant
        }
        else{

            i = 0; // On repart a la premiere Tile de la ligne
            j++; // On passe a la ligne suivante

        }
    }


    // =========================================================
    // On recupere les objets de la Map
    // =========================================================

    TiXmlElement *element2 = handle.FirstChildElement().FirstChildElement("objectgroup").FirstChildElement().Element();
    TiXmlElement *element2Bis, *element2BisBis;

    while(element2)
    {
        string gid = element2->Attribute("gid");
        string Xvalue = element2->Attribute("x");
        string Yvalue = element2->Attribute("y");

        string numInte, delaiInte;

        int x, y;
        x = atoi(Xvalue.c_str());
        y = atoi(Yvalue.c_str());

        //cout << gid << "  " << Xvalue << "  " << Yvalue << endl;

        // On recherche les groupes de proprietes intitule PROPERTIES

        element2Bis = element2->FirstChildElement("properties");

        // ==================
        // On crée les objets
        // ==================

        if(!gid.compare("8")) // Comparaison entre un string et un string sur son EGALITE
        {

            objet.push_back(new Block(tileSet1, x, (y - 50), true, "none", "tilePique", false, true, "haut"));

        }
        else if(!gid.compare("9"))
        {
            // Penser a gerer les propriétés pour les décallages

            objet.push_back(new Launcher(tileSet1, x, (y - 50), "none", "launcher", true, "gauche", 2.0f, 0.0f, "ball"));

        }
        else if(!gid.compare("10"))
        {
            // Penser a gerer les propriétés pour les décallages

            objet.push_back(new Launcher(tileSet1, x, (y - 50), "none", "launcher", true, "droite", 2.0f, 0.0f, "ball"));

        }
        else if(!gid.compare("11"))
        {

            while(element2Bis)
            {
                // On recherche les PROPERTY dans ces groupes
                element2BisBis = element2Bis->FirstChildElement("property");

                while(element2BisBis)
                {
                    string name = element2BisBis->Attribute("name");
                    string value = element2BisBis->Attribute("value");

                    //cout << "Name : " << name << " Value : " << value << endl;

                    objet.push_back(new Block(tileSet1, x, (y - 50), false, "none", "blockPique", false, true, value));




                    element2BisBis = element2BisBis->NextSiblingElement();
                }

                element2Bis = element2Bis->NextSiblingElement();
            }

        }
        else if(!gid.compare("12"))
        {

            while(element2Bis)
            {
                // On recherche les PROPERTY dans ces groupes
                element2BisBis = element2Bis->FirstChildElement("property");

                while(element2BisBis)
                {
                    string name = element2BisBis->Attribute("name");

                    if(name == "delai")
                    {
                        delaiInte = element2BisBis->Attribute("value");
                    }
                    else if(name == "num")
                    {
                        numInte = element2BisBis->Attribute("value");
                    }

                    //cout << "Name : " << name << " Value : " << value << endl;

                    element2BisBis = element2BisBis->NextSiblingElement();
                }

                element2Bis = element2Bis->NextSiblingElement();
            }

            float delai = atoi(delaiInte.c_str());
            int id = atoi(numInte.c_str());

            objet.push_back(new Interrupteur(myInterrupteur, x, (y - 25), false, delai, "none", "interrupteur", false, id));

            cout << "Un interrupteur de plus avec comme id : " << numInte << " et comme delai " << delaiInte << endl;

        }
        else if(!gid.compare("14")) // Pas de 13 car ce sont les portes, elles sont traitées par la suite
        {
            // Penser a gerer les propriétés pour les décallages

            objet.push_back(new Block(myCheckpoint, x, (y - 25), false, "none", "checkpoint", false, false, "none"));

        }
        else if(!gid.compare("15"))
        {
            // Penser a gerer les propriétés pour les décallages

            objet.push_back(new Block(tileSet1, x, (y - 50), true, "none", "tileTerre", true, false, "none"));

        }
        else if(!gid.compare("16"))
        {

            while(element2Bis)
            {
                // On recherche les PROPERTY dans ces groupes
                element2BisBis = element2Bis->FirstChildElement("property");

                while(element2BisBis)
                {
                    string name = element2BisBis->Attribute("name");
                    string value = element2BisBis->Attribute("value");
                    int val = atoi(value.c_str());


                    //cout << "Name : " << name << " Value : " << value << endl;

                    for(int i = 0; i < val; i++)
                    {
                        int randomNumber1 = rand() % 2 + 1;
                        int randomNumber2;

                        if(randomNumber1 == 1)
                        {
                            randomNumber2 = rand() % 150 + 1;

                            objet.push_back(new Reward(reward, x, (y - 50), "none", "reward", false, 100.0f, randomNumber2));
                        }
                        else if(randomNumber1 == 2)
                        {
                            randomNumber2 = rand() % 150 + 1;

                            randomNumber2 = -randomNumber2;

                            objet.push_back(new Reward(reward, x, (y - 50), "none", "reward", false, 100.0f, randomNumber2));
                        }
                    }

                    element2BisBis = element2BisBis->NextSiblingElement();
                }

                element2Bis = element2Bis->NextSiblingElement();
            }

        }
        else if(!gid.compare("17")) // Comparaison entre un string et un string sur son EGALITE
        {

            objet.push_back(new Block(tileSet1, x, (y - 50), true, "none", "tilePique", false, true, "bas"));

        }
        else if(!gid.compare("18")) // Comparaison entre un string et un string sur son EGALITE
        {

            objet.push_back(new Block(tileSet1, x, (y - 50), true, "none", "tilePique", false, true, "droite"));

        }
        else if(!gid.compare("19")) // Comparaison entre un string et un string sur son EGALITE
        {

            objet.push_back(new Block(tileSet1, x, (y - 50), true, "none", "tilePique", false, true, "gauche"));

        }


        // ==================


        element2 = element2->NextSiblingElement();
    }



    element2 = handle.FirstChildElement().FirstChildElement("objectgroup").FirstChildElement().Element();

    // Boucle qui concerne uniquement les PORTES


    while(element2)
    {

        string gid = element2->Attribute("gid");
        string Xvalue = element2->Attribute("x");
        string Yvalue = element2->Attribute("y");

        int x, y;
        x = atoi(Xvalue.c_str());
        y = atoi(Yvalue.c_str());

        // On recherche les groupes de proprietes intitule PROPERTIES

        element2Bis = element2->FirstChildElement("properties");

        // ==================
        // On crée les objets
        // ==================


        if(!gid.compare("13"))
        {

            while(element2Bis)
            {
                // On recherche les PROPERTY dans ces groupes
                element2BisBis = element2Bis->FirstChildElement("property");

                while(element2BisBis)
                {
                    string name = element2BisBis->Attribute("name");
                    string value = element2BisBis->Attribute("value");

                    //cout << "Name : " << name << " Value : " << value << endl;

                    int idDoor = atoi(value.c_str());
                    Object * obj;

                    // On récupère l'objet INTERRUPTEUR ayant le meme ID que la PORTE
                    for(int unsigned i = 0; i < objet.size(); i++){

                        if(objet[i]->getId() == idDoor)
                        {
                            obj = objet[i];

                            objet.push_back(new Door(myDoor, x, (y - 50), false, "none", "door", true, obj));
                        }
                    }




                    element2BisBis = element2BisBis->NextSiblingElement();
                }

                element2Bis = element2Bis->NextSiblingElement();
            }

        }

        // ==================


        element2 = element2->NextSiblingElement();
    }












    // On obtient donc toutes les informations importantes qui sont
    // le GID, X, Y, NAME de la property et sa VALUE

    // =========================================================






    // ==============================================
    // affichage de la matrice et d'autres variables
    // ==============================================

   /* for(int j=0; j<nbLignes; j++){
		cout << endl;

		for(int i=0; i<nbColonnes; i++)
		cout << (*Matrice)[i][j].id;
	}

	cout << endl << "load completed ! " << endl;

    cout << largeurTile << endl;
    cout << hauteurTile << endl;*/


    // =============================================


    for(int j=0; j<nbLignes; j++){
		for(int i=0; i<nbColonnes; i++){

			(*Matrice)[i][j].solid = false;


			if ((*Matrice)[i][j].id == "1"){

				(*Matrice)[i][j].spr = new sf::Sprite();
				(*Matrice)[i][j].spr->setTexture(tileSet1);
				(*Matrice)[i][j].spr->setTextureRect(IntRect(0,0,50,50));
				(*Matrice)[i][j].fullblock = true;
				(*Matrice)[i][j].solid = true;
				(*Matrice)[i][j].solidBottom = false;
				(*Matrice)[i][j].endBlock = false;
				(*Matrice)[i][j].startBlock = true;

			}
			else if ((*Matrice)[i][j].id == "2"){

				(*Matrice)[i][j].spr = new sf::Sprite();
				(*Matrice)[i][j].spr->setTexture(tileSet1);
				(*Matrice)[i][j].spr->setTextureRect(IntRect(50,0,50,50));
				(*Matrice)[i][j].fullblock = true;
				(*Matrice)[i][j].solid = true;
				(*Matrice)[i][j].solidBottom = false;
				(*Matrice)[i][j].endBlock = false;
				(*Matrice)[i][j].startBlock = false;

			}
			else if ((*Matrice)[i][j].id == "3"){

				(*Matrice)[i][j].spr = new sf::Sprite();
				(*Matrice)[i][j].spr->setTexture(tileSet1);
				(*Matrice)[i][j].spr->setTextureRect(IntRect(100,0,50,50));
				(*Matrice)[i][j].fullblock = true;
				(*Matrice)[i][j].solid = true;
				(*Matrice)[i][j].solidBottom = false;
				(*Matrice)[i][j].endBlock = false;
				(*Matrice)[i][j].startBlock = false;

			}
			else if ((*Matrice)[i][j].id == "4"){

				(*Matrice)[i][j].spr = new sf::Sprite();
				(*Matrice)[i][j].spr->setTexture(tileSet1);
				(*Matrice)[i][j].spr->setTextureRect(IntRect(150,0,50,50));
				(*Matrice)[i][j].fullblock = false;
				(*Matrice)[i][j].solid = false;
				(*Matrice)[i][j].solidBottom = false;
				(*Matrice)[i][j].endBlock = false;
				(*Matrice)[i][j].startBlock = false;
			}
			else if ((*Matrice)[i][j].id == "5"){

				(*Matrice)[i][j].spr = new sf::Sprite();
				(*Matrice)[i][j].spr->setTexture(tileSet1);
				(*Matrice)[i][j].spr->setTextureRect(IntRect(200,0,50,50));
				(*Matrice)[i][j].fullblock = true;
				(*Matrice)[i][j].solid = false;
				(*Matrice)[i][j].solidBottom = true;
				(*Matrice)[i][j].endBlock = false;
				(*Matrice)[i][j].startBlock = false;
			}
			else if ((*Matrice)[i][j].id == "6"){

				(*Matrice)[i][j].spr = new sf::Sprite();
				(*Matrice)[i][j].spr->setTexture(tileSet1);
				(*Matrice)[i][j].spr->setTextureRect(IntRect(250,0,50,50));
				(*Matrice)[i][j].fullblock = true;
				(*Matrice)[i][j].solid = false;
				(*Matrice)[i][j].solidBottom = true;
				(*Matrice)[i][j].endBlock = false;
				(*Matrice)[i][j].startBlock = false;
			}
			else if ((*Matrice)[i][j].id == "7"){

				(*Matrice)[i][j].spr = new sf::Sprite();
				(*Matrice)[i][j].spr->setTexture(tileSet1);
				(*Matrice)[i][j].spr->setTextureRect(IntRect(300,0,50,50));
				(*Matrice)[i][j].fullblock = true;
				(*Matrice)[i][j].solid = false;
				(*Matrice)[i][j].solidBottom = true;
				(*Matrice)[i][j].endBlock = true;
				(*Matrice)[i][j].startBlock = false;
			}
			else{
				(*Matrice)[i][j].spr = 0;
				(*Matrice)[i][j].value = '0';
				(*Matrice)[i][j].fullblock = false;
				(*Matrice)[i][j].solid = false;
				(*Matrice)[i][j].solidBottom = false;
				(*Matrice)[i][j].endBlock = false;
				(*Matrice)[i][j].startBlock = false;
			}

			if((*Matrice)[i][j].spr != 0){
				(*Matrice)[i][j].spr->setPosition(i*largeurTile, j*hauteurTile);

			}



		}
	}


}

int nbColonnesMap(string map)
{

    // Récupération des données dans le fichier TMX (Tiled Map Editor) / Traitement XML

    TiXmlDocument document(map.c_str());
    if(!document.LoadFile()){//si on n'arrive pas à charger le fichier
        cout << "error : N°" << document.ErrorId() << " : " << document.ErrorDesc() << endl;
        //return 1;
    }
    else{
        //cout << " Ouverture reussie " << endl;
    }


    TiXmlHandle handle(&document);
    string elemName, colonnes;

    int nbColonnes = 0;

    // on recherche les enfants Direct de Map
    TiXmlElement *element = handle.FirstChildElement().FirstChildElement().Element();

    int i = 0;
    while (element){
        //cout << element->Value() << endl; //l'atribut nom
        //cout << element->GetText() << endl;//Le texte entre les balises
                elemName = element->Value();

       if(elemName == "layer"){

            colonnes = element->Attribute("width");

            nbColonnes = atoi(colonnes.c_str());

        }

        element = element->NextSiblingElement(); // aller à l'élément suivant
        i++;



    }

    return nbColonnes;

}

int nbLignesMap(string map)
{

    // Récupération des données dans le fichier TMX (Tiled Map Editor) / Traitement XML

    TiXmlDocument document(map.c_str());
    if(!document.LoadFile()){//si on n'arrive pas à charger le fichier
        cout << "error : N°" << document.ErrorId() << " : " << document.ErrorDesc() << endl;
        //return 1;
    }
    else{
        //cout << " Ouverture reussie " << endl;
    }


    TiXmlHandle handle(&document);
    string elemName, lignes;

    int nbLignes = 0;

    // on recherche les enfants Direct de Map
    TiXmlElement *element = handle.FirstChildElement().FirstChildElement().Element();

    int i = 0;
    while (element){
        //cout << element->Value() << endl; //l'atribut nom
        //cout << element->GetText() << endl;//Le texte entre les balises
                elemName = element->Value();

       if(elemName == "layer"){

            lignes = element->Attribute("height");

            nbLignes = atoi(lignes.c_str());

        }

        element = element->NextSiblingElement(); // aller à l'élément suivant
        i++;



    }

    return nbLignes;


}

int largeurTileMap(string map)
{

    // Récupération des données dans le fichier TMX (Tiled Map Editor) / Traitement XML

    TiXmlDocument document(map.c_str());
    if(!document.LoadFile()){//si on n'arrive pas à charger le fichier
        cout << "error : N°" << document.ErrorId() << " : " << document.ErrorDesc() << endl;
        //return 1;
    }
    else{
        //cout << " Ouverture reussie " << endl;
    }


    TiXmlHandle handle(&document);
    string elemName, largeur;

    int largeurTile = 0;

    // on recherche les enfants Direct de Map
    TiXmlElement *element = handle.FirstChildElement().FirstChildElement().Element();

    int i = 0;
    while (element){
        //cout << element->Value() << endl; //l'atribut nom
        //cout << element->GetText() << endl;//Le texte entre les balises
                elemName = element->Value();

       if(elemName == "tileset"){

            largeur = element->Attribute("tilewidth");

            largeurTile = atoi(largeur.c_str());

        }

        element = element->NextSiblingElement(); // aller à l'élément suivant
        i++;



    }

    return largeurTile;

}


void deleteMatrice(tile*** Mat, int nbColonnes, int nbLignes, std::vector<Object*> &objet)
{



    for(int unsigned i = 0; i < objet.size();){

        //cout << "AVANT del" << endl;
        delete objet[i];
        //cout << "APRES del" << endl;

        //cout << "Ma taille est : " << objet.size() << endl;

        objet[i] = NULL;
        objet.erase(objet.begin());


    }

    objet.clear();

    //cout << "Ma taille FINALE est : " << objet.size() << endl;
    //cout << "DELETE COMPLETED" << endl;


    for(int j=0; j<nbLignes; j++)
		for(int i=0; i<nbColonnes; i++)
			if((*Mat)[i][j].spr != 0){
				delete (*Mat)[i][j].spr;
				//cout << "Matrice[" << i << "][" << j << "] ... deleted ... " << endl;
			}

    // xmin = objet[nbObject]->getLeftSide() / LARGEUR_TILE;

}


void GoToNextMap(string & Map_EnCours, unsigned int & MapActuelle, vector<string> & Maps)
{
    if(MapActuelle + 1 < Maps.size()){
        MapActuelle++;

        Map_EnCours = Maps[MapActuelle];
    }
    else{

        cout << "Derniere Map atteinte " << endl;
    }

    cout << "MapActuelle : " << MapActuelle << endl;
    cout << "Map_EnCours : " << Map_EnCours << endl;

}


void PlayerPosition(Character & player, tile*** Matrice, int nbColonnes, int nbLignes, int largeurTile, string lieu)
{

    if(lieu == "depart"){
        cout << "test6-0" << endl;
        int iDepart = 1, jDepart = 1, xDepart, yDepart;

        for(int j=0; j<nbLignes; j++){
            for(int i=0; i<nbColonnes; i++){

                if((*Matrice)[i][j].startBlock){
                    iDepart = i;
                    jDepart = j - 4;
                }
            }
        }


        cout << "test6-1" << endl;
        xDepart = iDepart * largeurTile;
        yDepart = jDepart * largeurTile;

        cout << "x avant :" << player.getX() << endl;
        cout << "iDepart : " << iDepart << endl;
        cout << "jDepart : " << jDepart << endl;
        cout << "xDepart : " << xDepart << endl;
        cout << "yDepart : " << yDepart << endl;

        player.setInitialPosition(xDepart, yDepart);
        player.setX(xDepart);
        player.setY(yDepart);
        player.setLife(player.getInitialLife());
        player.setSpeed(player.getInitialSpeed());
        player.setEnSaut(player.enSautInitial());
        player.setSurTerre(player.surTerreInitial());

        player.setPosition();
        //cout << "x apres :" << player.getX() << endl;

        cout << "test6" << endl;
    }
    else if(lieu == "checkpoint"){

        // A implanter

    }

}

void menu(sf::RenderWindow & app, bool inLoop, bool & changementDeMap, sf::View & vue, sf::Vector2f size, bool & startGame, vector<string> & vecMap, string & Map_EnCours, unsigned int & Map_Actuelle)
{
    vue = app.getDefaultView();

    sf::RectangleShape menu;
    menu.setSize(sf::Vector2f(size.x, size.y));
    menu.setFillColor(sf::Color(55, 55, 55));
    menu.setPosition((vue.getCenter().x - (vue.getSize().x / 2)), (vue.getCenter().y - vue.getSize().y / 2));

    sf::RectangleShape start;
    start.setSize(sf::Vector2f(200, 40));

    if(inLoop)
    {
        start.setFillColor(sf::Color(100, 100, 100));
    }
    else
    {
        start.setFillColor(sf::Color(100, 100, 100, 100));
    }

    start.setPosition((vue.getCenter().x - (start.getSize().x / 2)), (vue.getCenter().y));
    start.setOutlineColor(sf::Color::Black);
    start.setOutlineThickness(1);

    sf::RectangleShape buttonChoixMap;
    buttonChoixMap.setSize(sf::Vector2f(200, 40));
    buttonChoixMap.setFillColor(sf::Color(100, 100, 100));
    buttonChoixMap.setPosition((vue.getCenter().x - (buttonChoixMap.getSize().x / 2)), (vue.getCenter().y + 50.0f));
    buttonChoixMap.setOutlineColor(sf::Color::Black);
    buttonChoixMap.setOutlineThickness(1);

    sf::RectangleShape buttonQuitterMenu;
    buttonQuitterMenu.setSize(sf::Vector2f(200, 40));
    buttonQuitterMenu.setFillColor(sf::Color(100, 100, 100));
    buttonQuitterMenu.setPosition((vue.getCenter().x - (buttonQuitterMenu.getSize().x / 2)), (vue.getCenter().y + 100.0f));
    buttonQuitterMenu.setOutlineColor(sf::Color::Black);
    buttonQuitterMenu.setOutlineThickness(1);

    sf::Text titreText;
    titreText.setPosition((vue.getCenter().x - 120.0f), (vue.getCenter().y - 250.0f));
    titreText.setString("Another");
    titreText.setCharacterSize(64);

    sf::Text startText;
    startText.setPosition((start.getPosition().x + 55.0f), (start.getPosition().y + 5.0f));
    startText.setString("Continuer");
    startText.setCharacterSize(20);

    sf::Text choixMapText;
    choixMapText.setPosition((buttonChoixMap.getPosition().x + 25.0f), (buttonChoixMap.getPosition().y + 5.0f));
    choixMapText.setString("Choix de la map");
    choixMapText.setCharacterSize(20);

    sf::Text quitterText;
    quitterText.setPosition((buttonQuitterMenu.getPosition().x + 65.0f), (buttonQuitterMenu.getPosition().y + 5.0f));
    quitterText.setString("Quitter");
    quitterText.setCharacterSize(20);

    app.setView(vue);

    while(!startGame)
    {
        app.clear();
        app.draw(menu);
        app.draw(start);
        app.draw(buttonChoixMap);
        app.draw(buttonQuitterMenu);
        app.draw(titreText);
        app.draw(startText);
        app.draw(choixMapText);
        app.draw(quitterText);

        Event event;

        while (app.pollEvent(event)) // Permet le bon fonctionnement de la boucle ainsi que de recup les events
        {
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

                            if(inLoop)
                                startGame = true;

                            break;

                        default:
                            break;
                    }
                }

                default:
                    break;
            }
        }



        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Vector2i souris = Mouse::getPosition(app);

            if(start.getGlobalBounds().contains(souris.x, souris.y))
            {
                if(inLoop)
                    startGame = true;
            }

            if(buttonChoixMap.getGlobalBounds().contains(souris.x, souris.y))
            {
                menuMap(app, inLoop, changementDeMap, vue, size, startGame, vecMap, Map_EnCours, Map_Actuelle);
            }

            if(buttonQuitterMenu.getGlobalBounds().contains(souris.x, souris.y))
            {
                app.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) // New Game
        {
            startGame = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) // Start
        {
            app.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // Start
        {
            menuMap(app, inLoop, changementDeMap, vue, size, startGame, vecMap, Map_EnCours, Map_Actuelle);
        }


        app.display();
    }
}

void menuMap(sf::RenderWindow & app, bool inLoop, bool & changementDeMap, sf::View & vue, sf::Vector2f size, bool & startGame, vector<string> & vecMap, string & Map_EnCours, unsigned int & Map_Actuelle)
{

    sf::RectangleShape menuChoixMap;
    menuChoixMap.setSize(sf::Vector2f(size.x, size.y));
    menuChoixMap.setFillColor(sf::Color(55, 55, 55));
    menuChoixMap.setPosition((vue.getCenter().x - (vue.getSize().x / 2)), (vue.getCenter().y - vue.getSize().y / 2));

    sf::RectangleShape buttonQuitterMenu;
    buttonQuitterMenu.setSize(sf::Vector2f(200, 40));
    buttonQuitterMenu.setFillColor(sf::Color(100, 100, 100));
    buttonQuitterMenu.setPosition((vue.getCenter().x - (buttonQuitterMenu.getSize().x / 2)), (vue.getCenter().y + 200.0f));
    buttonQuitterMenu.setOutlineColor(sf::Color::Black);
    buttonQuitterMenu.setOutlineThickness(1);

    sf::Text quitterText;
    quitterText.setPosition((buttonQuitterMenu.getPosition().x + 65.0f), (buttonQuitterMenu.getPosition().y + 5.0f));
    quitterText.setString("Retour");
    quitterText.setCharacterSize(20);


    bool choixMap = false;



    app.setView(vue);

    while(!choixMap)
    {
        app.clear();
        app.draw(menuChoixMap);
        app.draw(buttonQuitterMenu);
        app.draw(quitterText);

        vector<sf::RectangleShape> vectorBouton;
        int lastMap = 1;

        Event event;

        while (app.pollEvent(event)) // Permet le bon fonctionnement de la boucle ainsi que de recup les events
        {
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

                            choixMap = true;
                            break;

                        default:
                            break;
                    }
                }

                default:
                    break;
            }
        }




        TiXmlDocument doc;

        if(doc.LoadFile("sauvegarde.xml")) // Si on arrive a ouvrir le fichier
        {
            TiXmlElement* root = doc.FirstChildElement();

            if(root == NULL)
                cout << "Erreur d'ouverture du fichier" << endl;

            TiXmlElement* elem = root->FirstChildElement("LastMap");

            lastMap = atoi(elem->Attribute("lastMap"));

            int i = 0;

            //cout << "Last map : " << lastMap << endl;

            for(TiXmlElement* elem = root->FirstChildElement("Maps")->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
            {
                i++; // Map actuelle

                sf::RectangleShape mapShape;
                mapShape.setSize(sf::Vector2f(100, 100));

                if(i <= lastMap) // Map accessible
                {
                    mapShape.setFillColor(sf::Color(255, 255, 255));
                    mapShape.setOutlineColor(sf::Color::Black);
                }
                else // Map non accessible
                {
                    mapShape.setFillColor(sf::Color(0, 0, 0));
                    mapShape.setOutlineColor(sf::Color::Red);
                }


                mapShape.setPosition((vue.getCenter().x - 490 + (i % 9 * 110)), (vue.getCenter().y - 150 + (((int)((i) / 9)) * 110)));
                mapShape.setOutlineThickness(1);

                sf::Text levelText, scoreText, tempsText;
                ostringstream string1, string2, string3;

                string1 << "Level : " << i;
                string2 << "Score : " << atoi(elem->Attribute("score"));
                string3 << "Temps : " << atoi(elem->Attribute("temps"));

                levelText.setPosition((mapShape.getPosition().x + 3.0f), mapShape.getPosition().y);
                levelText.setString(string1.str());
                levelText.setCharacterSize(14);

                scoreText.setPosition((mapShape.getPosition().x + 3.0f), (mapShape.getPosition().y + 15.0f));
                scoreText.setString(string2.str());
                scoreText.setCharacterSize(14);

                tempsText.setPosition((mapShape.getPosition().x + 3.0f), (mapShape.getPosition().y + 30.0f));
                tempsText.setString(string3.str());
                tempsText.setCharacterSize(14);

                if(i <= lastMap) // Map accessible
                {
                    levelText.setColor(Color(0,0,0,255));
                    scoreText.setColor(Color(0,0,0,255));
                    tempsText.setColor(Color(0,0,0,255));
                }
                else // Map non accessible
                {
                    levelText.setColor(Color(255,0,0,255));
                    scoreText.setColor(Color(255,0,0,255));
                    tempsText.setColor(Color(255,0,0,255));
                }

                app.draw(mapShape);
                app.draw(levelText);
                app.draw(scoreText);
                app.draw(tempsText);

                vectorBouton.push_back(mapShape);
            }


        }
        else // Si le fichier n'existe pas
        {
            // On crée le fichier

            TiXmlElement* root = new TiXmlElement("root");
            doc.LinkEndChild(root);

            TiXmlElement* LastMap = new TiXmlElement("LastMap");
            root->LinkEndChild(LastMap);
            LastMap->SetAttribute("lastMap", "1");

            TiXmlElement* Maps = new TiXmlElement("Maps");
            root->LinkEndChild(Maps);

            for(int j = 1; j < 21; j++)
            {
                TiXmlElement* Maps1 = new TiXmlElement("Map");
                Maps->LinkEndChild(Maps1);
                Maps1->SetAttribute("num", j);
                Maps1->SetAttribute("temps", "0");
                Maps1->SetAttribute("score", "0");
            }

            bool success = doc.SaveFile("sauvegarde.xml");
            doc.Clear();
            if(success)
                cout << "Success" << endl;
            else
                cout << "Fail" << endl;




            // On l'analyse pour afficher les Maps

            doc.LoadFile("sauvegarde.xml");

            root = doc.FirstChildElement();

            if(root == NULL)
                cout << "Erreur d'ouverture du fichier" << endl;

            TiXmlElement* elem = root->FirstChildElement("LastMap");

            lastMap = atoi(elem->Attribute("lastMap"));

            int i = 0;

            for(TiXmlElement* elem = root->FirstChildElement("Maps")->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
            {
                i++; // Map actuelle

                sf::RectangleShape mapShape;
                mapShape.setSize(sf::Vector2f(75, 75));

                if(i <= lastMap) // Map accessible
                {
                    mapShape.setFillColor(sf::Color(0, 0, 0));
                }
                else // Map non accessible
                {
                    mapShape.setFillColor(sf::Color(69, 69, 69));
                }

                mapShape.setPosition((vue.getCenter().x - 490 + (i % 9 * 110)), (vue.getCenter().y - 150 + (((int)((i) / 9)) * 110)));
                mapShape.setOutlineColor(sf::Color::Red);
                mapShape.setOutlineThickness(1);

                sf::Text levelText, scoreText, tempsText;
                ostringstream string1, string2, string3;

                string1 << "Level : " << i;
                string2 << "Score : " << atoi(elem->Attribute("score"));
                string3 << "Temps : " << atoi(elem->Attribute("temps"));

                levelText.setPosition((mapShape.getPosition().x + 3.0f), mapShape.getPosition().y);
                levelText.setColor(Color(255,0,0,255));
                levelText.setString(string1.str());
                levelText.setCharacterSize(14);

                scoreText.setPosition((mapShape.getPosition().x + 3.0f), (mapShape.getPosition().y + 15.0f));
                scoreText.setColor(Color(255,0,0,255));
                scoreText.setString(string2.str());
                scoreText.setCharacterSize(14);

                tempsText.setPosition((mapShape.getPosition().x + 3.0f), (mapShape.getPosition().y + 30.0f));
                tempsText.setColor(Color(255,0,0,255));
                tempsText.setString(string3.str());
                tempsText.setCharacterSize(14);

                app.draw(mapShape);
                app.draw(levelText);
                app.draw(scoreText);
                app.draw(tempsText);

                vectorBouton.push_back(mapShape);
            }

        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Vector2i souris = Mouse::getPosition(app);

            for(unsigned int y = 0; y < vectorBouton.size(); y++)
            {
                if(vectorBouton[y].getGlobalBounds().contains(souris.x, souris.y))
                {
                    //cout << "Collision : " << y << endl;

                    if((y + 1) <= lastMap) // Si on clique sur une Map Débloquée
                    {
                        Map_Actuelle = y;
                        Map_EnCours = vecMap[Map_Actuelle];
                        choixMap = true;
                        startGame = true;
                        cout << "test y : " << Map_Actuelle << vecMap[Map_Actuelle] << endl;

                        if(inLoop)
                        {
                            changementDeMap = true;
                        }
                    }
                    else
                    {
                        cout << "Non debloquee" << endl;
                    }
                }
            }

            if(buttonQuitterMenu.getGlobalBounds().contains(souris.x, souris.y))
            {
                choixMap = true;
            }
        }

        //cout << "tab : " << vectorBouton.size() << endl;

        app.display();
    }
}

void save(int numMap, int score, float temps)
{
    TiXmlDocument doc;

    if(doc.LoadFile("sauvegarde.xml")) // Si on arrive a ouvrir le fichier
    {
        TiXmlElement* root = doc.FirstChildElement();

        if(root == NULL)
            cout << "Erreur d'ouverture du fichier" << endl;

        cout << "====TEST====" << endl;

        TiXmlElement* elem = root->FirstChildElement("LastMap");

        if(numMap > atoi(elem->Attribute("lastMap")))
            elem->SetAttribute("lastMap", numMap);


        cout << "====TEST====" << endl;

        int i = 0;
        //const char* tempsVar;
        //const char* scoreVar;

        for(TiXmlElement* elem = root->FirstChildElement("Maps")->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
        {
            i++; // Map actuelle

            //tempsVar = elem->Attribute("temps");
            //scoreVar = elem->Attribute("score");

            if((numMap - 1) == i) // Si on est entrain de sauvegarder la map actuelle
            {
                if(atoi(elem->Attribute("temps")) == 0)
                   elem->SetAttribute("temps", temps);
                else if(temps < atoi(elem->Attribute("temps")))
                    elem->SetAttribute("temps", temps);

                if(score > atoi(elem->Attribute("score")))
                    elem->SetAttribute("score", score);
            }

            //cout << i << " " << tempsVar << " " << scoreVar << endl;
        }


        bool success = doc.SaveFile("sauvegarde.xml");
        doc.Clear();
        if(success)
            cout << "Success" << endl;
        else
            cout << "Fail" << endl;

        cout << "====TEST====" << endl;

    }
    else // Si le fichier n'existe pas
    {
        TiXmlElement* root = new TiXmlElement("root");
        doc.LinkEndChild(root);

        TiXmlElement* LastMap = new TiXmlElement("LastMap");
        root->LinkEndChild(LastMap);
        LastMap->SetAttribute("lastMap", numMap);

        TiXmlElement* Maps = new TiXmlElement("Maps");
        root->LinkEndChild(Maps);

        TiXmlElement* Maps1 = new TiXmlElement("Map");
        Maps->LinkEndChild(Maps1);
        Maps1->SetAttribute("num", "1");
        Maps1->SetAttribute("temps", temps);
        Maps1->SetAttribute("score", score);

        for(int j = 2; j < 21; j++)
        {
            TiXmlElement* Maps1 = new TiXmlElement("Map");
            Maps->LinkEndChild(Maps1);
            Maps1->SetAttribute("num", j);
            Maps1->SetAttribute("temps", "0");
            Maps1->SetAttribute("score", "0");
        }

        bool success = doc.SaveFile("sauvegarde.xml");
        doc.Clear();
        if(success)
            cout << "Success" << endl;
        else
            cout << "Fail" << endl;
    }
}





