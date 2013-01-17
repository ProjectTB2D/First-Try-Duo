#include <fstream>
#include "Core.h"
#include "global.h"
#include "World.h"
#include "Bullet.h"
#include "tinyxml.h"

#define zoneAffichable 5


World::World()
: _nextUniqueID(0)
{




}

int World::generateUniqueID() {


    return ++_nextUniqueID;


}

void World::createWorld(const char* lvlname){

   /* int nbColonnes = 20;
    int nbLignes = 20;

    _matrice = new tile*[nbColonnes];

	for(int i=0; i<nbColonnes; i++)
		_matrice[i] = new tile[nbLignes];

    for(int i = 0; i < nbColonnes; i++)
        for(int j = 0; j < nbLignes; j ++){

            _matrice[i][j].spr.setTexture(*(g_core->getImageManager()->getImage(1)));
            _matrice[i][j].spr.setPosition(i*100, j*100);
            //spr.setTextureRect(sf::IntRect(ipos.x, ipos.y, ipos.x + _frameW, ipos.y + _frameH));
            //spr.setOrigin(idim.x / 2, idim.y / 2);

        }*/

    printf("test1\n");
    parseMapTmx("map/Map1.tmx", &_matrice);

}

void World::createPlayer() {

    printf("s1\n");

    _team1.p = NULL;




    _team1.p = new Player(Actor(Entity(0, sf::Vector2f(0, 0), sf::Vector2f(0,0), sf::Vector2f(50,50)),
                                100,
                               200));



}

/////////////////////////////////// ADD ////////////////////////////////////////

void World::addBullet(Item_t it,sf::Vector2f pos,  float angle, float dmgmult){

    int img_id;

    switch(it){

        case IT_PISTOL : img_id = 2; break;
        case IT_THROW_AXE : img_id = 2; break;
        case IT_SHOTGUN : img_id = 2; break;
        case IT_SMG : img_id = 2; break;
        case IT_PLASMA : img_id = 2; break;
        case IT_RPG : img_id = 2; break;

        default : img_id = 2;
    }

    _team1.proj.push_back(Bullet(Entity(img_id, pos, sf::Vector2f(0,0), sf::Vector2f(25,25)), it, angle, dmgmult));

}



void World::update(){

    _team1.p->update();

    // UPDATE BULLET

    for (list<Bullet>::iterator it = _team1.proj.begin(); it != _team1.proj.end(); ++it){

        it->update();

    }

}

//////////////////////////////////////////////////////////////// PURGE THE UNDEAD //////////////////////////////////////////////////////////////////////////:

void World::disolve_dead_bullet(){

    for (list<Bullet>::iterator it = _team1.proj.begin(); it != _team1.proj.end();){

        if(it->getKilled()){

            it = _team1.proj.erase(it);

        }
        else
        ++it;

  }


}

void World::disolve_dead_NPC(){


}

void World::disolve_dead_drop(){

}


///////////////////////////////////////////////////////////////////// RENDER ///////////////////////////////////////////////////////////////////////////

void World::render(){

    renderWorld();
    _team1.p->render();

        centerCamera();

    for (list<Bullet>::iterator it = _team1.proj.begin(); it != _team1.proj.end(); ++it){

        it->render();

    }


}

    int convertToIndex(float a, int LARGEUR_TILE){
        return((int)(a/LARGEUR_TILE));
    }

    int convertToView(int a, int LARGEUR_TILE){
        return(a*LARGEUR_TILE);
    }

void World::renderWorld() {

    int indexPlayerI = convertToIndex(_team1.p->getPos().x, 100);
    int indexPlayerJ = convertToIndex(_team1.p->getPos().y, 100);

    /* Les nombre en dessous permettent de déterminer la distance ou lon affiche la map autour du héro */

    float visionI = zoneAffichable, visionJ = zoneAffichable;

    int idPImoins = indexPlayerI - visionI;
    int idPIplus = indexPlayerI + visionI;
    int idPJmoins = indexPlayerJ - visionJ;
    int idPJplus = indexPlayerJ + visionJ;

    if(idPImoins < 0)
        idPImoins = 0;

    if(idPIplus > 20)
        idPIplus = 20;

    if(idPJmoins < 0)
        idPJmoins = 0;

    if(idPJplus > 20)
        idPJplus = 20;

    for(int j=idPJmoins; j<idPJplus; j++)
            for(int i=idPImoins; i<idPIplus; i++)
                    g_core->getApp()->draw(_matrice[i][j].spr);

}


void World::centerCamera() {

g_core->getView()->setCenter(getTeam1()->p->getPos());

}

void World::disolve(){

        ////////////////////////////////////
  //          PURGE                 //
  ////////////////////////////////////

  disolve_dead_drop();
disolve_dead_NPC();
disolve_dead_bullet();



}

///////////////////////////////////////////////////////////// EPURAGE /////////////////////////////////////////////////////////////////////////////////////////


bool World::insideScreen(int x, int y, int w, int h, int margin) const
{
    //v2d_t cam = level_editmode() ? editor_camera : camera_get_position();
    float a[4] = { x, y, x+w, y+h };
    float b[4] = {
        g_core->getView()->getCenter().x - g_core->getWinSize().x/2 - margin,
        g_core->getView()->getCenter().y - g_core->getWinSize().y/2 - margin,
        g_core->getView()->getCenter().x + g_core->getWinSize().x/2 + margin,
        g_core->getView()->getCenter().y + g_core->getWinSize().y/2 + margin
    };


    //sf::Shape rect(sf::Shape::Rectangle(b[0],b[1],b[2],b[3],sf::Color::Blue,3,sf::Color::Blue));
    //rect.EnableFill(false);
    //g_core->getApp()->Draw(rect);

    return g_core->bounding_box(a,b);
}


 Player*         World::getPlayerTeam1(){return NULL;}
 Player*         World::getPlayerTeam2(){return NULL;}

 team*   World::getTeam1(){return &_team1;}
 team*   World::getTeam2(){return NULL;}

 NPC*   World::getNPCTeam1(int a){return NULL;}
 NPC*   World::getNPCTeam2(int a){return NULL;}




void World::parseMapTmx(string map, tile*** Matrice){

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

            (*Matrice)[i][j].num = atoi(value.c_str());

            i++; // On passe a la tile suivante
            element = element->NextSiblingElement(); // aller à l'élément suivant
        }
        else{

            i = 0; // On repart a la premiere Tile de la ligne
            j++; // On passe a la ligne suivante

        }
    }



    for(int j=0; j<nbLignes; j++){
		for(int i=0; i<nbColonnes; i++){

		    (*Matrice)[i][j].spr.setTexture(*(g_core->getImageManager()->getImage(4)));
		    (*Matrice)[i][j].spr.setPosition(i*largeurTile, j*hauteurTile);

			if ((*Matrice)[i][j].num == 1){

				(*Matrice)[i][j].spr.setTextureRect(sf::IntRect(0,0,100,100));
			}
			else if ((*Matrice)[i][j].num == 2){

				(*Matrice)[i][j].spr.setTextureRect(sf::IntRect(100,0,100,100));
			}
			else if ((*Matrice)[i][j].num == 3){

				(*Matrice)[i][j].spr.setTextureRect(sf::IntRect(200,0,100,100));
			}
		}
    }

}

World::~World(){

    delete _team1.p;



}
