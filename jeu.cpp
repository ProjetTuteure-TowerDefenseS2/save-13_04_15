
#include "constante.h"

using namespace sf;
using namespace std;


bool jeu(RenderWindow &window, string nomMap, Font font, Sprite tile[NB_TILE])
{

    vector <View> tabView;

    for(int i = 0 ; i < NB_NIVEAU ; i++)
    {
        tabView.push_back(window.getDefaultView());
    }

    // dans la pile
	Texture texture;
	// ptrTexture est dans la pile, et un objet de type texture est dans le tas
	//Texture* ptrTexture = new Texture ();
	// delete ptrTexture;
	//std::unique_ptr<Texture> monUniquePtr = make_unique(Texture)
	texture.loadFromFile("./img/dragRoug2.png");
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(0,0);

	Ennemi ennemi("Dragon", sprite, 150);

    /*Ennemi tabEnnemi[NB_ENNEMI];

	for(int i = 0 ; i < NB_ENNEMI ; i++)
    {
        tabEnnemi[i].creerEnnemi("Dragon", sprite, 100);
        tabEnnemi[i].setPos(-32 * i , 0);
        tabEnnemi[i].nouvelEndroit(0, 0);
    }*/

    ennemi.newSprite(sprite);
	ennemi.creerEnnemi("Dragon", sprite, 50, 50);
	ennemi.setPos(-40, 0);
    ennemi.nouvelEndroit(0, 0);

	Texture textureTour;
	textureTour.loadFromFile("./image/text.png");

	int x = 0;
	int etape =0;
	double deplacement = 0.01;



	/*Tour tour;
	tour.initialiserTour("./image/tirBase.png", "./image/tirBase2.png", "./image/tirBase3.png");*/

	Tour tabTour[NB_TOUR];
	int nb_tourActu = 0;

	Tour tourTempoAchat;

    Clock temps;
    temps.restart();

    bool moving = false;;
    Clock clock;
    Clock tabClock[NB_ENNEMI];
    Vector2f target, velocity;


    bool depClique = true;

    Texture textureTile;
	textureTile.loadFromFile("./maps/herbe.png");
	Sprite mySprite;
	mySprite.setTexture(textureTile);

	int tabOuAller[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2];
	int nbCase;


	Sprite Barricade;


    Texture textureBaricade;
    textureBaricade.loadFromFile("./img/barricade.png");

    Barricade.setTexture(textureBaricade);

    int imageActu = 0;
    int a, b;

    int zoneArriverX = 12, zoneArriverY = 6;

    int endroitMonstreX = 0, endroitMonstreY = 0;

    bool dep = false, cliqueGauche = false;

    Joueur player;

    Carte mapNum1(nomMap, 0, 0);
    mapNum1.ReinitialiserCarte();

    Texture textureMagasin;
    textureMagasin.loadFromFile("./img/Magasin.png");

    Sprite spriteMagasin;
	spriteMagasin.setTexture(textureMagasin);
	spriteMagasin.setPosition(1000,0);

	bool poserBarricade = false;
	bool poserTabTour = false;



	sf::Text textOr;

    // choix de la police à utiliser
    textOr.setFont(font); // font est un sf::Font
    // choix de la taille des caractères
    textOr.setCharacterSize(20); // exprimée en pixels, pas en points !
    // choix de la couleur du texte
    textOr.setColor(Color::Black);
    textOr.setPosition(850, 0);
    textOr.setString(player.changerAffichageOr());



    bool enJeu = true;

    int nbCaseTempo;
    int tabOuAllerTempo[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2];
    int mapTempo[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP];


    if(dijkstra(0, 0, zoneArriverX, zoneArriverY, mapTempo, tabOuAllerTempo, nbCaseTempo))
    {
        while (window.isOpen() && enJeu)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                gestionEvent(event, window, dep, mapNum1, imageActu, poserBarricade, poserTabTour, ennemi, clock, enJeu);
            }
            //, endroitMonstreX, endroitMonstreY

            for(int i = 0 ; i < nb_tourActu ; i++)
            {
                /*if (ennemi.getPosition().x < tabTour[i].getGlobalBoundsW() + tabTour[i].getZone() &&
                    ennemi.getPosition().x + texture.getSize().x + tabTour[i].getZone() > tabTour[i].getGlobalBoundsW() &&
                    ennemi.getPosition().y < tabTour[i].getGlobalBoundsH() + tabTour[i].getZone() &&
                    ennemi.getPosition().y + texture.getSize().y + tabTour[i].getZone() > tabTour[i].getGlobalBoundsH())*/
                if(((ennemi.getPosition().x < tabTour[i].getPosX() + 32 + tabTour[i].getZone() && ennemi.getPosition().x > tabTour[i].getPosX() - tabTour[i].getZone()) ||
                    (ennemi.getPosition().x + 32 < tabTour[i].getPosX() + 32 + tabTour[i].getZone() && ennemi.getPosition().x + 32 > tabTour[i].getPosX() - tabTour[i].getZone())) &&
                   ((ennemi.getPosition().y < tabTour[i].getPosY() + 32 + tabTour[i].getZone() && ennemi.getPosition().y > tabTour[i].getPosY() - tabTour[i].getZone()) ||
                    (ennemi.getPosition().y + 32 < tabTour[i].getPosY() + 32 + tabTour[i].getZone() && ennemi.getPosition().y + 32 > tabTour[i].getPosY() - tabTour[i].getZone())))
                {
                    if(tabTour[i].getClock().getElapsedTime().asSeconds() > 1.5)
                    {
                        try{
                            tabTour[i].creationTir(textureTour, ennemi.getPosition(), 1, 3);
                        }
                        catch(string msg)
                        {
                            cout << msg << endl;
                        }
                    }
                }

                if(tabTour[i].getTirTirer())
                {
                    if(tabTour[i].deplacementTir(texture, ennemi.getPosition()) && ennemi.getPVRestant() > 0)
                    {
                        cout << endl << "TOUCHER !!" << endl;
                        ennemi.supprimerPV(tabTour[i].getDegatTir());
                        cout << "PV restant a l'ennemi : " << ennemi.getPVRestant() << endl;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)//MouseButtonReleased pour relacher
            {
                if (event.mouseButton.button == sf::Mouse::Left && !cliqueGauche)
                {
                    cliqueGauche = true;
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    if(poserBarricade)
                    {
                        poserBarricade = false;
                    }
                    else if(poserTabTour)
                    {
                        poserTabTour = false;
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased )//MouseButtonReleased pour relacher
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    cliqueGauche = false;
                }
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                if(poserBarricade)
                {
                    Barricade.setPosition(event.mouseMove.x - (LARGEUR_TILE / 2), event.mouseMove.y  - (HAUTEUR_TILE / 2));
                }
                else if(poserTabTour)
                {
                    tourTempoAchat.setPosition(event.mouseMove.x - (LARGEUR_TILE / 2), event.mouseMove.y  - (HAUTEUR_TILE / 2));
                }
            }



            if(cliqueGauche)
            {
                if(trouveA_B(event.mouseButton.x, event.mouseButton.y, a, b))
                {
                    if (mapNum1.getNumCaseMapNiveau2(a, b) == BARRICADE && poserTabTour)
                    {
                        int valTempo = 0;
                        bool positionDejaPrise = false;
                        while(!positionDejaPrise && valTempo < nb_tourActu)
                        {
                            if(tabTour[valTempo].getPosX() == a * LARGEUR_TILE && tabTour[valTempo].getPosY() == b * HAUTEUR_TILE)
                            {
                                positionDejaPrise = true;
                            }
                            valTempo++;
                        }
                        if(!positionDejaPrise)
                        {
                            cout << endl << "placer tour" << endl;
                            tabTour[nb_tourActu].initialiserTour(tourTempoAchat.getZone(), tourTempoAchat.getPrix(), tourTempoAchat.getDegatTir(), tourTempoAchat.getNom(0), tourTempoAchat.getNom(1), tourTempoAchat.getNom(2), tourTempoAchat.getNom(3), tourTempoAchat.getNom(4), tourTempoAchat.getNom(5));
                            tabTour[nb_tourActu].setPosition(a * LARGEUR_TILE, b * HAUTEUR_TILE);
                            player.retirerOr(tourTempoAchat.getPrix());

                            nb_tourActu++;

                            textOr.setString(player.changerAffichageOr());
                            poserTabTour = false;
                        }
                    }
                    else if (mapNum1.getNumCaseMapNiveau2(a, b) == VIDE && poserBarricade) //enlever le 3 plus tard
                    {
                        if(!collisionTourEnnemi(ennemi, a, b))
                        {
                            cout << endl << "POSITIONNEMENT BARRICADE" << endl;
                            //poserBarricade = false;


                            int valX = 0, valY;

                            bool cheminPossible = true;
                            int numTemp = mapNum1.getNumCaseMap(a, b);


                            mapNum1.initialiserMap();

                            mapNum1.setNumCaseMap(a, b, BARRICADE);
                            mapNum1.setNumCaseMapNiveau2(a, b, BARRICADE);

                            for(int i = 0; i < MAX_LARGEUR_MAP; i++)
                            {
                                for(int j = 0 ; j < MAX_HAUTEUR_MAP; j++)
                                {
                                    mapTempo[i][j] = mapNum1.getNumCaseMap(i, j);
                                    if(mapNum1.getNumCaseMapNiveau2(i, j) != VIDE)
                                    {
                                        mapTempo[i][j] = mapNum1.getNumCaseMapNiveau2(i, j);
                                    }
                                    cout << mapTempo[i][j] << " ";
                                }
                                cout << endl;
                            }

                            if(trouveA_B(ennemi.getPosition().x + (LARGEUR_TILE / 2), ennemi.getPosition().y + (HAUTEUR_TILE / 2), valX, valY))
                            {
                                ennemi.nouvelEndroit(valX, valY);
                            }

                            if(dijkstra(zoneArriverX, zoneArriverY, ennemi, mapNum1))
                            {
                                if(dijkstra(0, 0, zoneArriverX, zoneArriverY, mapTempo, tabOuAllerTempo, nbCaseTempo))
                                {
                                    mapNum1.setNumCaseMapNiveau2(a, b, BARRICADE);
                                    ennemi.setEtape(1);

                                    player.retirerOr(10);
                                    textOr.setString(player.changerAffichageOr());
                                }
                                else
                                {
                                    mapNum1.setNumCaseMapNiveau2(a, b, VIDE);
                                }
                            }
                            else
                            {
                                mapNum1.setNumCaseMapNiveau2(a, b, VIDE);
                            }
                            mapNum1.setNumCaseMap(a, b, numTemp);

                        }
                        else
                        {
                            cout << endl << "ERREUR : TOUR EN COLLISION AVEC UN ENNEMI" << endl;
                        }
                    }
                }
                else if(event.mouseButton.x > 1010 && event.mouseButton.x < 1045 &&
                        event.mouseButton.y > 65 && event.mouseButton.y < 100 && player.getOr() >= 10)
                {
                    Barricade.setPosition(event.mouseButton.x - (LARGEUR_TILE / 2), event.mouseButton.y  - (HAUTEUR_TILE / 2));
                    poserBarricade = true;
                    poserTabTour = false;
                }
                else if(poserBarricade)
                {
                    poserBarricade = false;
                }
                else if(event.mouseButton.x > 1010 && event.mouseButton.x < 1045 &&
                        event.mouseButton.y > 118 && event.mouseButton.y < 153 && player.getOr() >= 30)
                {
                    if(nb_tourActu < NB_TOUR)
                    {
                        tourTempoAchat.initialiserTour(60, 30, 2, "./img/tour.png", "./image/flamme_1.png", "./image/flamme_2.png", "./image/flamme_3.png");
                        tourTempoAchat.setPosition(event.mouseButton.x - (LARGEUR_TILE / 2), event.mouseButton.y  - (HAUTEUR_TILE / 2));
                        poserTabTour = true;
                        poserBarricade = false;
                    }
                }
                else if(event.mouseButton.x > 1010 && event.mouseButton.x < 1045 &&
                        event.mouseButton.y > 171 && event.mouseButton.y < 206 && player.getOr() >= 40)
                {
                    if(nb_tourActu < NB_TOUR)
                    {
                        tourTempoAchat.initialiserTour(80, 40, 2, "./img/tourArcher.png", "./image/tirBase.png", "./image/tirBase2.png", "./image/tirBase3.png");
                        tourTempoAchat.setPosition(event.mouseButton.x - (LARGEUR_TILE / 2), event.mouseButton.y  - (HAUTEUR_TILE / 2));
                        poserTabTour = true;
                        poserBarricade = false;
                    }
                }
                else if(poserTabTour)
                {
                    poserTabTour = false;
                }
                cliqueGauche = false;
            }





            if(!ennemi.getMoving() && dep)
            {
                if(ennemi.getEtape() == 0)
                {
                    mapNum1.initialiserMap();

                    dijkstra(zoneArriverX, zoneArriverY, ennemi, mapNum1);
                    ennemi.increEtape();
                }
                if(ennemi.getNbCase() - ennemi.getEtape() >= 0)
                {
                    ennemi.choixZone(texture, window, clock, ennemi.getTabOuAller(ennemi.getNbCase() - ennemi.getEtape(), 0) * LARGEUR_TILE, ennemi.getTabOuAller(ennemi.getNbCase() - ennemi.getEtape(), 1) * HAUTEUR_TILE);
                    ennemi.increEtape();
                }
                else
                {
                    cout << endl << "REMISE A ZERO !!!!!!!!!!!" << endl << endl;

                    ennemi.nouvelEndroit(endroitMonstreX, endroitMonstreY);
                    ennemi.setEtape(0);
                    ennemi.setPos(LARGEUR_TILE * endroitMonstreX, HAUTEUR_TILE * endroitMonstreY);
                }
            }
            /*for(int i = 0 ; i < NB_ENNEMI ; i++)
            {
                if(!tabEnnemi[i].getMoving() && dep)
                {
                    if(tabEnnemi[i].getEtape() == 0)
                    {
                        mapNum1.initialiserMap();

                        dijkstra(zoneArriverX, zoneArriverY, tabEnnemi, i, mapNum1);
                        cout << endl << "posX : " << tabEnnemi[i].getPosition().x << "posY: " << tabEnnemi[i].getPosition().y << endl;
                        tabEnnemi[i].increEtape();
                    }
                    //cout << endl << "nbCase: " << tabEnnemi[i].getNbCase() << endl;
                    if(tabEnnemi[i].getNbCase() - tabEnnemi[i].getEtape() >= 0)
                    {
                        tabEnnemi[i].choixZone(texture, window, tabClock[i], tabEnnemi[i].getTabOuAller(tabEnnemi[i].getNbCase() - tabEnnemi[i].getEtape(), 0) * LARGEUR_TILE, tabEnnemi[i].getTabOuAller(tabEnnemi[i].getNbCase() - tabEnnemi[i].getEtape(), 1) * HAUTEUR_TILE);
                        tabEnnemi[i].increEtape();
                    }
                    else
                    {
                        cout << endl << "REMISE A ZERO !!!!!!!!!!!" << endl << endl;

                        tabEnnemi[i].nouvelEndroit(endroitMonstreX, endroitMonstreY);
                        tabEnnemi[i].setEtape(0);
                        tabEnnemi[i].setPos(LARGEUR_TILE * endroitMonstreX, HAUTEUR_TILE * endroitMonstreY);
                    }
                }
            }*/


            ///mettre en pause le clock
            if(!ennemi.deplacement(clock, mapNum1, ennemi.getEtape()))///Seulement si la fenetre a le focus
            {
                //cout << endl << "PAS DEPLACEMENT" << endl;
                if(trouveA_B(ennemi.getPosition().x + (LARGEUR_TILE / 2), ennemi.getPosition().y + (HAUTEUR_TILE / 2), a, b) && ennemi.getEtape() > 1)
                {
                    cout << "ERREUR !!! L'ennemie ne peut plus bouger." << endl;

                    ennemi.nouvelEndroit(a, b);
                    ennemi.setEtape(0);

                }
            }

            /*for(int i = 0 ; i < NB_ENNEMI ; i++)
            {
                if(!tabEnnemi[i].deplacement(tabClock[i], mapNum1, tabEnnemi[i].getEtape()))///Seulement si la fenetre a le focus
                {
                    cout << endl << endl << "Ennemi : " << i << endl;
                    //cout << endl << "PAS DEPLACEMENT" << endl;
                    if(trouveA_B(tabEnnemi[i].getPosition().x + (LARGEUR_TILE / 2), tabEnnemi[i].getPosition().y + (HAUTEUR_TILE / 2), a, b) && tabEnnemi[i].getEtape() > 1)
                    {
                        cout << endl << "ERREUR !!! L'ennemie ne peut plus bouger." << endl;

                        tabEnnemi[i].nouvelEndroit(a, b);
                        tabEnnemi[i].setEtape(0);
                    }
                }
            }*/

            ///Affichage

            window.clear(sf::Color(127,127,127));

            window.draw(spriteMagasin);

            afficherViewMap(window, tabView, 0, mapNum1, tile);
            afficherViewMapNiveau2(window, tabView, 1, mapNum1, tile);
            afficherViewMapNiveau3(window, tabView, 2, mapNum1, tile);


            for(int i = 0 ; i < nb_tourActu ; i++)
            {
                if(tabTour[i].getAfficher())
                {
                    tabTour[i].draw(window);
                    tabTour[i].afficheTir(window);
                }
            }

            /*tour.draw(window);
            tour.afficheTir(window);*/

            ennemi.afficheEnnemi(window);

            /*for(int i = 0 ; i < NB_ENNEMI ; i++)
            {
                tabEnnemi[i].afficheEnnemi(window);
            }*/

            if(poserBarricade)
            {
                window.draw(Barricade);
            }
            else if(poserTabTour)
            {
                tourTempoAchat.draw(window);
            }
            // puis, dans la boucle de dessin, entre window.clear() et window.display()
            window.draw(textOr);


            window.display();
        }
    }
    else
    {
        throw(string("ERREUR !!! Impossible d'atteindre la base ennemi"));
    }


    return enJeu;
}
