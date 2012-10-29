#include "include/Function.h"

// Vitesse du personnage
const int PLAYER_SPEED = 0;

// Vitesse du personnage
const int ENNEMI_SPEED = 400;

// Vitesse de la balle
const int BULLET_SPEED = 1200;

// Taille de l'écran
//const Vector2f WINDOW_SIZE(1200,600);
const Vector2f WINDOW_SIZE(1000,600);

// chemin de la feuille de sprite
const string SPRITES_FILE_PATH_PLAYER = "images/characterV1.png";

const string SPRITES_FILE_PATH_ENNEMI = "images/samus_v2.png";

const string SPRITES_FILE_PATH_ENNEMI_2 = "images/equipe_rouge.png";

// chemin de la feuille de sprite
const string SPRITES_FILE_PATH_BULLET = "images/bullet.png";

// Image du bonus de santé

const string SPRITES_FILE_PATH_LIFEBONUS = "images/box_life.png";



int main()
{

    // On aura TOUJOURS comme première fichier map "Map1.tmx" puis un nombre de map a définir

    string etatMap = "start";
    int nbMap = 20;

    // Tableau des différentes Maps
    vector<string> Maps;

    for(int i = 1; i < (nbMap + 1); i++)
    {
        string nomMap = "map/Map";
        nomMap.append(int_to_string(i));
        nomMap.append(".tmx");

        Maps.push_back(nomMap);

        //cout << "la map " << nomMap << " a ete pushe" << endl;
    }

    string Map_EnCours = Maps[0];


    unsigned int Map_Actuelle = 0;

    tile** Matrice;
    //tile** MatriceTest;



    //int LARGEUR_MAP = NbColonnes * LARGEUR_TILE;
    //int HAUTEUR_MAP = NbLignes * HAUTEUR_TILE;

    bool debugMode = true;



    // Fenêtre
    RenderWindow app(VideoMode((int)WINDOW_SIZE.x, (int)WINDOW_SIZE.y, 32), "Another : Beta v0.2");

	// Frames Per Second (FPS)
    //app.setFramerateLimit(60); // limite la fenêtre à 60 images par seconde

    // NE PAS mettre les deux en meme temps

    app.setVerticalSyncEnabled(true);

	Texture myTile, myEchelle, myBullet, myEnnemi, myEnnemi2, myPlayer, myPlayer2, lifeBonus,
	myEndBlock, tileSet1, myInterrupteur, myDoor, myCheckpoint, reward;

	if (!myBullet.loadFromFile(SPRITES_FILE_PATH_BULLET)) // Si le chargement a échoué
    {
        cerr<<"Erreur durant le chargement de l'image"<<endl;
    }
    else
    {
        //myBullet.SetSmooth(false);
    }

	if (!myEnnemi.loadFromFile(SPRITES_FILE_PATH_ENNEMI)) // Si le chargement a échoué
    {
        cerr<<"Erreur durant le chargement de l'image"<<endl;
    }
    else
    {
        //myEnnemi.SetSmooth(false);
    }

	if (!myEnnemi2.loadFromFile(SPRITES_FILE_PATH_ENNEMI_2)) // Si le chargement a échoué
    {
        cerr<<"Erreur durant le chargement de l'image"<<endl;
    }
    else
    {
        //myEnnemi2.SetSmooth(false);
    }

	if (!myPlayer.loadFromFile(SPRITES_FILE_PATH_PLAYER)) // Si le chargement a échoué
    {
        cerr<<"Erreur durant le chargement de l'image"<<endl;
    }
    else
    {
        //myPlayer.SetSmooth(false);
    }

	if (!lifeBonus.loadFromFile(SPRITES_FILE_PATH_LIFEBONUS)) // Si le chargement a échoué
    {
        cerr<<"Erreur durant le chargement de l'image"<<endl;
    }
    else
    {
        //lifeBonus.SetSmooth(false);
    }

	if (!myTile.loadFromFile("images/blocTerre.png")) // Si le chargement a échoué
	{
		cerr<<"Erreur durant le chargement de l'image"<<endl;
	}
    else
    {
        //myTile.SetSmooth(false);
    }

	if (!myEchelle.loadFromFile("images/blocEchelle.png")) // Si le chargement a échoué
	{
		cerr<<"Erreur durant le chargement de l'image"<<endl;
	}
    else
    {
        //myEchelle.SetSmooth(false);
    }

	if (!myEndBlock.loadFromFile("images/blocFin.png")) // Si le chargement a échoué
	{
		cerr<<"Erreur durant le chargement de l'image"<<endl;
	}
    else
    {
        //myEndBlock.SetSmooth(false);
    }

    if (!tileSet1.loadFromFile("map/tileset1.png")) // Si le chargement a échoué
    {
        cerr<<"Erreur durant le chargement de l'image"<<endl;
    }
    else
    {
        //tileSet1.SetSmooth(false);
    }

    if (!myInterrupteur.loadFromFile("images/interrupteur.png")) // Si le chargement a échoué
	{
		cerr<<"Erreur durant le chargement de l'image"<<endl;
	}
    else
    {
        //myInterrupteur.SetSmooth(false);
    }

    if (!myDoor.loadFromFile("images/porteCoulissante.png")) // Si le chargement a échoué
	{
		cerr<<"Erreur durant le chargement de l'image"<<endl;
	}
    else
    {
        //myDoor.SetSmooth(false);
    }

	if (!myCheckpoint.loadFromFile("images/checkpoint.png")) // Si le chargement a échoué
	{
		cerr<<"Erreur durant le chargement de l'image"<<endl;
	}
    else
    {
        //myCheckpoint.SetSmooth(false);
    }

    if (!reward.loadFromFile("images/reward.png")) // Si le chargement a échoué
	{
		cerr<<"Erreur durant le chargement de l'image"<<endl;
	}
    else
    {
        //reward.SetSmooth(false);
    }

    vector<Bullet> vectorBullet;
	vector<Character> vectorCharacter;
	vector<Object*> vectorObject;




	// ====== Variable importante !! =======

//	int x = 150;
//	int y = 150;
	int controleSaut = false; /* Booléen qui va permettre de ne pas relancer un second saut avant d'avoir relaché la touche */
	float transparence = 0;
	float transparenceInverse = 255;
	Clock clockTempsMap;
	Clock clockFrame;
	bool startGame = false;
	bool changementDeMap = false;

	/*string etatMap = "start";

	// Tableau des différentes Maps
    vector<string> Maps;



    for(int i = 1; i < (nbMap + 1); i++)
    {
        string nomMap = "map/Map";
        nomMap.append(int_to_string(i));
        nomMap.append(".tmx");

        Maps.push_back(nomMap);

        //cout << "la map " << nomMap << " a ete pushe" << endl;
    }*/

	// =====================================
	// =====================================




	// Création et positionnement du joueur au lancement du jeu



	// =========================


	// Création d'une vue qui suivra les déplacements du joueur

	View vue = app.getDefaultView();
	View hud;

	// =========================================================

	// Création des barres de vie et d'énergie du joueur et du rectangle de fondu

    sf::RectangleShape hud1;
    hud1.setSize(sf::Vector2f(150, 140));
    hud1.setFillColor(sf::Color(190, 200, 200));
    hud1.setOutlineColor(sf::Color::Black);
    hud1.setOutlineThickness(1);

    sf::RectangleShape barLife;
    barLife.setSize(sf::Vector2f(50, 10));
    barLife.setFillColor(sf::Color::Red);
    barLife.setOutlineColor(sf::Color::Black);
    barLife.setOutlineThickness(1);

    sf::RectangleShape barPower;
    barPower.setSize(sf::Vector2f(50, 10));
    barPower.setFillColor(sf::Color(0, 150, 255));
    barPower.setOutlineColor(sf::Color::Black);
    barPower.setOutlineThickness(1);

    sf::RectangleShape fondu;
    fondu.setSize(sf::Vector2f(WINDOW_SIZE.x, WINDOW_SIZE.y));

	// ===============================================================
	// Menu

    menu(app, false, changementDeMap, hud, WINDOW_SIZE, startGame, Maps, Map_EnCours, Map_Actuelle);

    createMap(Map_EnCours, &Matrice, tileSet1, myInterrupteur, myDoor, myCheckpoint, reward, vectorObject);

    int NbColonnes = nbColonnesMap(Map_EnCours);
    int NbLignes = nbLignesMap(Map_EnCours);

    int LARGEUR_TILE = largeurTileMap(Map_EnCours);
    int HAUTEUR_TILE = largeurTileMap(Map_EnCours);

    Player player(myPlayer, 0, 0, PLAYER_SPEED, "bleu", "normal");
	PlayerPosition(player, &Matrice, NbColonnes, NbLignes, LARGEUR_TILE, "depart");

	clockTempsMap.restart();

    cout << "Map en cours avant main" << Map_EnCours << endl;
    cout << "Map Actuelle avant main" << Map_Actuelle << endl;

    // Boucle principale
    while (app.isOpen())
    {
		// Remplissage de l'écran (couleur noire par défaut)
        app.clear();

        //vue.setSize(WINDOW_SIZE.x, WINDOW_SIZE.y);
        app.setView(vue);
        hud = app.getDefaultView();


        // On récupère le temps de rafraichissement entre chaque frame pour ajuster la vitesse du jeu
        float frameTime = clockFrame.restart().asSeconds();

        bool actionElement = false;

        // On modifier la valeur du temps de la map

        /*if(clockTempsMap.getElapsedTime().asSeconds() > 0.1f)
        {
            tempsMap += 0.1f;
            clockTempsMap.restart();
        }*/


		/* Gestion de l'affichage d'un certain nombre de tile autour du player, et non toute la map */

		int indexPlayerI = convertToIndex(player.getLeftSide(), LARGEUR_TILE);
		int indexPlayerJ = convertToIndex(player.getBottomSide(), LARGEUR_TILE);

		/* Les nombre en dessous permettent de déterminer la distance ou lon affiche la map autour du héro */

		float visionI = 20, visionJ = 10;

		int idPImoins = indexPlayerI - visionI;
		int idPIplus = indexPlayerI + visionI;
		int idPJmoins = indexPlayerJ - visionJ;
		int idPJplus = indexPlayerJ + visionJ;

		if(idPImoins < 0)
			idPImoins = 0;

		if(idPIplus > NbColonnes)
			idPIplus = NbColonnes;

		if(idPJmoins < 0)
			idPJmoins = 0;

		if(idPJplus > NbLignes)
			idPJplus = NbLignes;

        for(int j=idPJmoins; j<idPJplus; j++)
                for(int i=idPImoins; i<idPIplus; i++)
                    if(Matrice[i][j].spr != 0)
                        app.draw(*Matrice[i][j].spr);


		//=================================================



		/* REGENERATION du POWER */

		player.setPower(player.getPower() + 0.2f);

		if(player.getPower() > 100.0f)
			player.setPower(100.0f);

		if(player.getPower() < 0)
			player.setPower(0);

		if(player.getPower() > 50.0f)
			player.setSurchauffe(false);

		/* ===================== */



		/* == LIFE == */

		if(player.getLife() <= 100)
			player.upLife(0.05f);

		if(player.getLife() > 200.0f)
			player.setLife(200.0f);

		if(player.getLife() < 0)
			player.setLife(0);

		/* ===================== */



		// Dès que la vitesse descend en dessous de 0 alors le joueur n'est plus en saut

		if(player.getSpeedY() < 0)
			player.setEnSaut(false);

		/* ===================== */


		/* GRAVITE : On diminue la vitesse verticale si pas sur Terre */

		if(!player.surTerre()){

			player.setSpeedY(player.getSpeedY() - 30.0f);

			/* Effet de resistance de l'air */
			if((CollisionDecorLateralSide(LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, player, Matrice, vectorObject) == 1)
                || (CollisionDecorLateralSide(LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, player, Matrice, vectorObject) == 2)
            )
            {
                if(player.getSpeedY() < -400.0f)
                    player.setSpeedY(-400.0f);
            }
            else
            {
               if(player.getSpeedY() < -800.0f)
                    player.setSpeedY(-800.0f);
            }


		}

		/* ===================== */



		/* On enleve la GRAVITE lorsque l'on est au sol */

		if(player.surTerre()){
			player.setSpeedY(0);
		}

		/* ===================== */


		/* CLOCK du freeze Time */

		if(player.getFreeze()){

			if(player.getClockFreeze() > 1.5f){
				player.setFreeze(false);
				player.setSpeedY(0);
			}
		}

		// ======================

		Event event;

        while (app.pollEvent(event))
        {

			if(event.type == sf::Event::KeyReleased && event.key.code == Keyboard::Space){

				//player.setEnSaut(false);
				controleSaut = false;
			}

			if(event.type == sf::Event::KeyReleased && event.key.code == Keyboard::Down){

				player.setDescendre(false);
			}

			if(event.type == sf::Event::KeyReleased && event.key.code == Keyboard::Right){

				player.setDeplacement(false);
				player.setMouvementDroite(false);
			}

			if(event.type == sf::Event::KeyReleased && event.key.code == Keyboard::Left){

				player.setDeplacement(false);
				player.setMouvementGauche(false);
			}
			if(event.type == sf::Event::KeyReleased && event.key.code == Keyboard::LShift){

				player.notShooting();
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

                            if(player.surTerre())
                            {
                                startGame = false;
                                menu(app, true, changementDeMap, hud, WINDOW_SIZE, startGame, Maps, Map_EnCours, Map_Actuelle);

                                if(changementDeMap)
                                {
                                    clockTempsMap.restart();
                                    player.setScore(0);

                                    deleteMatrice(&Matrice, NbColonnes, NbLignes, vectorObject);

                                    createMap(Map_EnCours, &Matrice, tileSet1, myInterrupteur, myDoor, myCheckpoint, reward, vectorObject);

                                    NbColonnes = nbColonnesMap(Map_EnCours);
                                    NbLignes = nbLignesMap(Map_EnCours);

                                    PlayerPosition(player, &Matrice, NbColonnes, NbLignes, LARGEUR_TILE, "depart");


                                    changementDeMap = false;
                                }
                            }
                            else
                            {
                                cout << "Vous devez etre sur terre pour aller dans le menu. (En cas de probleme, sautez !)" << endl;
                            }
							break;

                        default:
                            break;
					}
				}



				default:
                    break;
			}


        }



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(!player.getMouvementDroite()){

                player.setMouvementGauche(true);

                if(!player.getFreeze()){
                //	if(!Matrice[mxGauche][myGauche].solid){
                        if(!player.getFreeze())
                            //if(player.getSpeed() > -15.0f)
                                player.deplacementGaucheX();

                //	}

                    player.setDeplacement(true);
                }

                player.setDirectionGauche();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(!player.getMouvementGauche()){

                player.setMouvementDroite(true);

                if(!player.getFreeze()){
                    //if(!Matrice[mxDroite][myDroite].solid){
                        if(!player.getFreeze())
                            //if(player.getSpeed() < 15.0f)
                                player.deplacementDroiteX();

                    //}

                    player.setDeplacement(true);
                }

                player.setDirectionDroite();
		    }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if(!controleSaut && !player.getFreeze() && player.surTerre()){
					player.setSpeedY(650.0f);
					player.setEnSaut(true);
					controleSaut = true;
            }

            if(!controleSaut && !player.getFreeze() && !player.surTerre())
            {
                if(CollisionDecorLateralSide(LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, player, Matrice, vectorObject) == 1)
                {
                    player.setSpeedY(850.0f);
                    player.setSpeed(700.0f);
					player.setEnSaut(true);
					controleSaut = true;
                    //cout << "saut gauche" << endl;
                }
                else if(CollisionDecorLateralSide(LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, player, Matrice, vectorObject) == 2)
                {
                    player.setSpeedY(850.0f);
                    player.setSpeed(-700.0f);
					player.setEnSaut(true);
					controleSaut = true;
                    //cout << "saut droite" << endl;
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if(!player.getSurchauffe()){
				player.teleport();
				player.setFreeze(false);
			}
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            actionElement = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            etatMap = "end";
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            if(!player.getFreeze())
				player.freezeTime();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if(player.getClockBullet() > 0.2f){
				if(player.getDirection() == "droite"){
					vectorBullet.push_back(Bullet(myBullet, (player.getRightSide() - 10), (player.getTopSide() + 12.0f), (BULLET_SPEED * frameTime), player.getDirection(), player.getEquipe(), "ball"));
				}else if(player.getDirection() == "gauche"){
					vectorBullet.push_back(Bullet(myBullet, (player.getLeftSide() - 20), (player.getTopSide() + 12.0f), (BULLET_SPEED * frameTime), player.getDirection(), player.getEquipe(), "ball"));
				}

				player.resetClockBullet();
			}

            player.shootAnimation();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            player.setDescendre(true);
        }



		//	===================================================
		//  =============== AFFICHAGE DES TESTS ===============
		//	===================================================

		/*if(CollisionDecorPlafond(LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, player, Matrice))
			cout << " COLLISION PLAFOND  " << endl;
		else
			cout << " PAS COLLISION PLAFOND  " << endl;

		if(CollisionDecorSol(LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, player, Matrice))
			cout << " COLLISION SOL  " << endl;
		else
			cout << " PAS COLLISION SOL  " << endl;	*/


		/*if(player.surTerre())
			cout << " SUR TERRE  " << endl;
		else
			cout << " PAS SUR TERRE  " << endl;
*/
		//cout << player.getSpeed() << endl;
		/*
			cout << vectorCharacter.size() << endl;
			cout << vectorBullet.size() << endl;
			cout << vectorObject.size() << endl;*/


      // cout << "speed y :" << player.getSpeedY() << endl;



		//	===================================================


	//	===================================================


		/* Friction / Ralentissement de la vitesse latérale */

		if(!player.getDeplacement()){

			if(player.getSpeed() > 1500.0f){
				player.setSpeed(player.getSpeed() - 500.0f);
			}else if(player.getSpeed() < -1500.0f){
				player.setSpeed(player.getSpeed() + 500.0f);
			}

			if(player.getSpeed() > 0){
				if(player.getSpeed() < 150.00f){
					player.setSpeed(0);
				}
				else{
					player.setSpeed(player.getSpeed() - 50.00f);
				}

			}else if(player.getSpeed() < 0){
				if(player.getSpeed() > -150.0f){
					player.setSpeed(0);
				}
				else{
					player.setSpeed(player.getSpeed() + 50.00f);
				}
			}

		}

		/* Lorsque le joueur n'est pas Freeze on effectue les essai de mouvement sur X et Y pour on application la nouvelle position */

		if(!player.getFreeze()){

			EssaiDeplacementX(Matrice, frameTime, player, player.getSpeed(), LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, vectorObject);

			if(EssaiDeplacementY(Matrice, frameTime, player, player.getSpeedY(), LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, vectorObject)){

				// Si true, alors le joueur est en contact avec un bloc de fin de niveau
                cout << "ERREUR" << endl;
                cout << Map_Actuelle << " " << Map_EnCours << endl;
				etatMap = "end";
			}



			player.setPosition();

		}







		//	===========================================================================
		//  =========== Double boucle testant chaque balles si elle est en  ===========
		//	===========	collision avec un ennemi, un player, un mur ou rien ===========
		//	===========================================================================


		for(int unsigned i = 0; i < vectorBullet.size(); i++){

			if(CollisionBulletDecor(LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, vectorBullet[i], Matrice)){
					vectorBullet[i].kill();
				}

			if(vectorBullet[i].getDirection() == "droite"){
				vectorBullet[i].deplacementDroiteX();
			}else if(vectorBullet[i].getDirection() == "gauche"){
				vectorBullet[i].deplacementGaucheX();
			}

			vectorBullet[i].drawBullet(app);

			// Collision des balles et des ennemis
			for(int unsigned j = 0; j < vectorCharacter.size(); j++){

				float degatDeal;

				// On test si l'équipe de la balle est la meme que celle du character, si non, on peut tester la collision
				if(vectorBullet[i].getEquipe() != vectorCharacter[j].getEquipe()){
					if(!vectorBullet[i].isKilled()){
						if(CollisionBulletCharacter(vectorBullet[i], vectorCharacter[j])){

							degatDeal = vectorBullet[i].getDegat();
							vectorCharacter[j].downLife(degatDeal);

							vectorBullet[i].kill();
						}
					}
				}

			}

			// Collision des balles et des objet

            for(int unsigned j = 0; j < vectorObject.size(); j++){

                if(vectorObject[j]->getSolid()){

                    if(CollisionObjectBullet(vectorObject[j], vectorBullet[i])){
                        vectorBullet[i].kill();

                        if(vectorObject[j]->getBreakable()){
                           vectorObject[j]->kill();
                        }
                    }
                }
            }

			// Collision des balles et du joueur

			if(vectorBullet[i].getEquipe() != player.getEquipe()){
				if(!vectorBullet[i].isKilled()){
					if(CollisionBulletCharacter(vectorBullet[i], player)){

						float degatDeal = vectorBullet[i].getDegat();
						player.downLife(degatDeal);

						vectorBullet[i].kill();
					}
				}
			}

		}

		//	===========================================================================



		//	===================================================
		//  ============== Boucle sur les objets ==============
		//	===================================================

		for(int unsigned i = 0; i < vectorObject.size(); i++){

			for(int unsigned j = 0; j < vectorCharacter.size(); j++){

				if(CollisionObjectCharacter(vectorObject[i], vectorCharacter[j])){

					float life = vectorObject[i]->getLife();
					vectorCharacter[j].upLife(life);

					vectorObject[i]->kill();
				}

			}

			if(CollisionObjectCharacter(vectorObject[i], player)){

                if(vectorObject[i]->getType() == "lifeBonus"){
                    float life = vectorObject[i]->getLife();
                    player.upLife(life);

                    vectorObject[i]->kill();
                }
                else if(vectorObject[i]->getType() == "interrupteur"){

                    if(actionElement){
                        if(vectorObject[i]->getEstActive() == false){
                            vectorObject[i]->setActive();
                            vectorObject[i]->resetClockInt();
                        }
                    }

                }
                else if(vectorObject[i]->getType() == "tilePique"){

                    if(vectorObject[i]->getDeadly()){
                        player.kill();
                    }

                }
                else if(vectorObject[i]->getType() == "checkpoint"){

                    if(!vectorObject[i]->getActive()){
                        vectorObject[i]->setActive(true);

                        player.setInitialPosition(vectorObject[i]->getX(), vectorObject[i]->getY());

                        for(int unsigned j = 0; j < vectorObject.size(); j++){

                            if(vectorObject[j]->getType() == "checkpoint"){
                                if(j != i)
                                {
                                    if(vectorObject[j]->getActive()){
                                        vectorObject[j]->setActive(false);
                                    }
                                }
                            }
                        }

                    }
                }
                else if(vectorObject[i]->getType() == "blockPique"){

                    if(vectorObject[i]->getDeadly()){
                        player.kill();
                    }

                }
                else if(vectorObject[i]->getType() == "reward"){
                    int val = vectorObject[i]->getValeur();
                    player.setScore(player.getScore() + val);

                    vectorObject[i]->kill();
                }
			}

            //cout << "test 1030 et taille de  : " << vectorObject.size() << endl;


			if((vectorObject[i]->getType() == "interrupteur") && (vectorObject[i]->getEstActive())){

                if(vectorObject[i]->getClockInt() > vectorObject[i]->getDelai()){

                    vectorObject[i]->setNotActive();
                }

			}
			else if(vectorObject[i]->getType() == "door"){

                if(vectorObject[i]->buttonIsActive()){

                    vectorObject[i]->setOpen(true);
                }
                else{

                    if(!CollisionObjectCharacter(vectorObject[i], player))
                        vectorObject[i]->setOpen(false);
                }

			}
			else if(vectorObject[i]->getType() == "launcher"){

                if(!vectorObject[i]->getIsReady()){
                    if(vectorObject[i]->getClock() > vectorObject[i]->getDecallage()){

                        vectorObject[i]->resetClock();
                        vectorObject[i]->setReady(true);

                    }
                }
                else{
                    if(vectorObject[i]->getClock() > vectorObject[i]->getInterval()){

                        vectorObject[i]->resetClock();

                        float x, y;

                        if(vectorObject[i]->getDirection() == "gauche")
                        {
                            x = (vectorObject[i]->getLeftSide()) - 5.0f;
                            y = (vectorObject[i]->getTopSide()) + 15.0f;

                            vectorBullet.push_back(Bullet(myBullet, x, y, (BULLET_SPEED * frameTime), vectorObject[i]->getDirection(), vectorObject[i]->getEquipe(), vectorObject[i]->getAmmoType()));
                        }
                        else if(vectorObject[i]->getDirection() == "droite")
                        {
                            x = (vectorObject[i]->getRightSide()) - 15.0f;
                            y = (vectorObject[i]->getTopSide()) + 15.0f;

                            vectorBullet.push_back(Bullet(myBullet, x, y, (BULLET_SPEED * frameTime), vectorObject[i]->getDirection(), vectorObject[i]->getEquipe(), vectorObject[i]->getAmmoType()));
                        }



                    }

                }

			}
			else if(vectorObject[i]->getType() == "blockPique"){

               // if(EssaiDeplacementY(Matrice, app, player, player.getSpeedY(), LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, vectorObject)){

                if(CollisionObjectDecor(LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, i, vectorObject, Matrice))
                {

                    if(vectorObject[i]->getDirection() == "gauche"){

                        vectorObject[i]->setDirection("droite");
                    }
                    else if(vectorObject[i]->getDirection() == "droite"){

                        vectorObject[i]->setDirection("gauche");
                    }
                    else if(vectorObject[i]->getDirection() == "haut"){

                        vectorObject[i]->setDirection("bas");
                    }
                    else if(vectorObject[i]->getDirection() == "bas"){

                        vectorObject[i]->setDirection("haut");
                    }
                }

                if(vectorObject[i]->getDirection() == "gauche"){

                    vectorObject[i]->deplacementGaucheX();
                }
                else if(vectorObject[i]->getDirection() == "droite"){

                    vectorObject[i]->deplacementDroiteX();
                }
                else if(vectorObject[i]->getDirection() == "haut"){

                    vectorObject[i]->deplacementHautY();
                }
                else if(vectorObject[i]->getDirection() == "bas"){

                    vectorObject[i]->deplacementBasY();
                }

			}
			else if(vectorObject[i]->getType() == "reward"){

                if(CollisionObjectDecor(LARGEUR_TILE, HAUTEUR_TILE, NbColonnes, NbLignes, i, vectorObject, Matrice))
                {
                    vectorObject[i]->deplacement(true, frameTime);

                }
                else
                {
                    vectorObject[i]->deplacement(false, frameTime);

                }



			}

			vectorObject[i]->drawObject(app);
		}


        /** A AJUSTER */

		vue.setCenter((int)(player.getX() + (player.GetSprite().getLocalBounds().width)/2), (int)(player.getY() + (player.GetSprite().getLocalBounds().height)/2));


        player.drawPlayer(app);

		// == Boucle permettant de supprimer du Vector les balles qui sont "killed" après une collision

		for(int unsigned i = 0; i < vectorBullet.size();){
			if(vectorBullet[i].isKilled())
				vectorBullet.erase(vectorBullet.begin()+i);
			else
				i++;
		}

		// == Boucle permettant de supprimer du Vector les Ennemis qui sont "killed" lorsqu'il n'ont plus de points de vie

/*		// == Ou plutot de faire respawn le Character

		for(int unsigned i = 0; i < vectorCharacter.size();){
			if(vectorCharacter[i].isKilled()){

				vectorCharacter[i].setX(vectorCharacter[i].getInitialX());
				vectorCharacter[i].setY(vectorCharacter[i].getInitialY());
				vectorCharacter[i].setLife(vectorCharacter[i].getInitialLife());
				vectorCharacter[i].setSpeed(vectorCharacter[i].getInitialSpeed());
				vectorCharacter[i].setEnSaut(vectorCharacter[i].enSautInitial());
				vectorCharacter[i].setSurTerre(vectorCharacter[i].surTerreInitial());

				vectorCharacter[i].setPosition();

			//	vectorCharacter.erase(vectorCharacter.begin()+i);
			}else
				i++;
		}*/

		// == Boucle permettant de supprimer du Vector les objets qui sont "killed" lorsqu'ils ont été utilisés

		for(int unsigned i = 0; i < vectorObject.size();){
			if(vectorObject[i]->isKilled())
				vectorObject.erase(vectorObject.begin()+i);
			else
				i++;
		}



		// == Test permettant de voir si le player est Killed, et de le faire respawn en conséquence

		// systeme de CHECKPOINT ici

		if(player.isKilled()){

				player.setX(player.getInitialX());
				player.setY(player.getInitialY());
				player.setLife(player.getInitialLife());
				player.setSpeed(player.getInitialSpeed());
				player.setEnSaut(player.enSautInitial());
				player.setSurTerre(player.surTerreInitial());
				player.revive();

				player.setPosition();

			//	vectorCharacter.erase(vectorCharacter.begin()+i);
		}



        app.setView(hud); // IMPORTANT <<

        // On affiche le block hud1

        hud1.setPosition((hud.getCenter().x - (hud.getSize().x / 2)), (hud.getCenter().y - (hud.getSize().y / 2)));
        app.draw(hud1);

        // Permet d'afficher les FPS en mode debug

		if(debugMode){
			sf::Text fpsMessage;
			int FPS;
			ostringstream oss;

			FPS = 1 / frameTime;
			oss << "FPS : " << FPS;

            fpsMessage.setPosition((hud.getCenter().x - (hud.getSize().x / 2) + 20.0f), (hud.getCenter().y - (hud.getSize().y / 2) + 110.0f));
            fpsMessage.setColor(Color(255,0,0,255));
            fpsMessage.setString(oss.str());
            fpsMessage.setCharacterSize(14);

			app.draw(fpsMessage);
		}

        // On Affiche le Score

        sf::Text score;
        ostringstream oss2;

        oss2 << "Score : " << player.getScore();

        score.setColor(Color(0,0,0,255));
        score.setPosition((hud.getCenter().x - (hud.getSize().x / 2) + 20.0f), (hud.getCenter().y - (hud.getSize().y / 2) + 90.0f));
        score.setCharacterSize(14);
        score.setString(oss2.str());

        app.draw(score);

        // On Affiche le temps

        sf::Text tpsMaps;
        ostringstream oss3;

        oss3 << "Temps : " << clockTempsMap.getElapsedTime().asSeconds();

        tpsMaps.setColor(Color(0,0,0,255));
        tpsMaps.setPosition((hud.getCenter().x - (hud.getSize().x / 2) + 20.0f), (hud.getCenter().y - (hud.getSize().y / 2) + 70.0f));
        tpsMaps.setCharacterSize(14);
        tpsMaps.setString(oss3.str());


        app.draw(tpsMaps);


		// Affichage d'un message "surcharge" si l'energie est basse

		sf::Text txtSurcharge;

		txtSurcharge.setString("Overheating !");
		txtSurcharge.setColor(Color(255,0,0,255));
		txtSurcharge.setCharacterSize(14);
		txtSurcharge.setPosition((hud.getCenter().x - (hud.getSize().x / 2) + 20.0f), (hud.getCenter().y - (hud.getSize().y / 2) + 50.0f));

		if(player.getSurchauffe())
			app.draw(txtSurcharge);

		// Variations des barres de vies et de power

		barLife.setSize(sf::Vector2f(player.getLife(), 10.0f));
		barPower.setSize(sf::Vector2f(player.getPower(), 10.0f));

		barLife.setPosition((hud.getCenter().x - (hud.getSize().x / 2) + 20.0f), (hud.getCenter().y - (hud.getSize().y / 2) + 10.0f));
		barPower.setPosition((hud.getCenter().x - (hud.getSize().x / 2) + 20.0f), (hud.getCenter().y - (hud.getSize().y / 2) + 30.0f));

		if(player.getSurchauffe()){

			barPower.setFillColor(sf::Color(0, 25, 100));
		}
		else{

			barPower.setFillColor(sf::Color(0, 150, 255));
		}

        app.draw(barLife);
		app.draw(barPower);

        //cout << "x now :" << player.getX() << endl;
        //cout << "speed Y :" << player.getSpeedY() << endl;


		if(etatMap == "end"){


			/* Systeme de fondu pour fin de niveau // Le rectangle suit le joueur pour éviter tout problème visuel */

			fondu.setPosition((hud.getCenter().x - (hud.getSize().x / 2)), (hud.getCenter().y - (hud.getSize().y / 2)));
			fondu.setFillColor(sf::Color(0,0,0,transparence));

			app.draw(fondu);

			// La transparence s'effectue a 0.5 par frame ( a modifier si besoin !)

			if(transparence < 255){
				transparence += 1.0f;
			}


			if(transparence >= 255){

                save((Map_Actuelle + 2), player.getScore(), clockTempsMap.getElapsedTime().asSeconds());
                // MapActuelle + 2 car pour le niveau 1 mapActuelle = 0 et que l'on veux save le dernier niveau que l'on
                //a atteint donc fin du 1 = 0 + 2 = 2

                clockTempsMap.restart();
                player.setScore(0);

                deleteMatrice(&Matrice, NbColonnes, NbLignes, vectorObject);

                GoToNextMap(Map_EnCours, Map_Actuelle, Maps);

                createMap(Map_EnCours, &Matrice, tileSet1, myInterrupteur, myDoor, myCheckpoint, reward, vectorObject);

                NbColonnes = nbColonnesMap(Map_EnCours);
                NbLignes = nbLignesMap(Map_EnCours);


				// On repositionne le joueur en fonction des valeurs initiales

				// =========
// IMPORTANT	// Les valeurs "initiales" varieront en fonction des checkpoint et des changement de niveau
				// =========



				// ========================

                PlayerPosition(player, &Matrice, NbColonnes, NbLignes, LARGEUR_TILE, "depart");




				// =================================

				etatMap = "transition"; // TEMPORAIRE
				transparence = 0;

			}

		}

		if(etatMap == "transition"){

			// On réalise un fondu (inverse) pour réafficher le jeu

			fondu.setPosition((hud.getCenter().x - (hud.getSize().x / 2)), (hud.getCenter().y - (hud.getSize().y / 2)));
			fondu.setFillColor(sf::Color(0,0,0,transparenceInverse));

			app.draw(fondu);

			if(transparenceInverse > 0){
				transparenceInverse -= 2.0f;
			}


			if(transparenceInverse <= 0)
			{
			    etatMap = "start";
			    transparenceInverse = 255;
			}

		}

        // Affichage de la fenêtre à l'écran
        app.display();
    }

	deleteMatrice(&Matrice, NbColonnes, NbLignes, vectorObject);

    return EXIT_SUCCESS;


}











