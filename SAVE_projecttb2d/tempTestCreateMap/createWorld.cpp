void createMap(string map, tile*** Matrice, std::vector<Object*> &objet)
{
    // Récupération des données dans le fichier TMX (Tiled Map Editor) / Traitement XML


    // ================= OUVERTURE ======================

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


    // ==== On récupère les informations sur la Map (colonnes, lignes) et les tiles (taille) =====

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

    }

    // On crée la Matrice avec le nb de colonnes et de lignes déterminés précédemment

    cout << "nb colonnes : " << nbColonnes << " nb lignes : " << nbLignes << endl;

    (*Matrice) = 0;

    (*Matrice) = new tile*[nbColonnes];

	for(int i=0; i<nbColonnes; i++)
		(*Matrice)[i] = new tile[nbLignes];

    // ----------------------------------------------------------------------------


    // ======== On recherche les enfants de Data (donc toutes les tiles) ==========
    element = handle.FirstChildElement().FirstChildElement("layer").FirstChildElement("data").FirstChildElement().Element();

    i = 0;
    int j = 0;

    while (element){

        if(i < nbColonnes){

            string value = element->Attribute("gid"); // Numéro de la Tile

            (*Matrice)[i][j].id = value;
            (*Matrice)[i][j].spr = 0;

            i++; // On passe a la tile suivante
            element = element->NextSiblingElement(); // aller à l'élément suivant
        }
        else{

            i = 0; // On repart a la premiere Tile de la ligne
            j++; // On passe a la ligne suivante

        }
    }


    // =========================================================
    // ======    On recupere les objets de la Map    ===========
    // =========================================================

    // On se positionne sur la liste des objets

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




    // ============================================================
    // Création du contenu de la matrice avec les différentes Tiles
    // ============================================================

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