#ifndef CONSTANTE
#define CONSTANTE

#include "ennemis.h"
#include <vector>

#include <sstream>


bool jeu(sf::RenderWindow &window, std::string nomMap, sf::Font font, sf::Sprite tile[NB_TILE]);

void chargerMap(std::string level, int map[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP], bool tileBloquant[NB_TILE]);
bool trouveA_B(int posSouris_X, int posSouris_Y, int &case_X, int &case_Y);
bool dijkstra(int numDepartX, int numDepartY, int numATrouverX, int numATrouverY, int tabOuAller[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2], int &nbCase, Carte &mapCarte);
bool dijkstra(int numDepartX, int numDepartY, int numATrouverX, int numATrouverY, int mapNum[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP], int tabOuAller[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2], int &nbCase);
bool dijkstra(int numATrouverX, int numATrouverY, Ennemi tabEnnemiActu[NB_ENNEMI], int numEnnemi, Carte &mapCarte);
bool dijkstra(int numATrouverX, int numATrouverY, Ennemi& ennemi, Carte &mapCarte);
void trouveNewCase(int noeudPetitI, int noeudPetitJ, int noeudPetitIBase, int noeudPetitJBase, int &nbValeur2, int map[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP][2], int tabPredes[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP], int tabATeste[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2], int valCase);
bool testMap(int val);

void gestionEvent(sf::Event event, sf::RenderWindow &window, bool &dep, Carte &mapNum1, int &imageActu, bool& poserTour,
                  bool& poserTabTour, Ennemi &ennemi, sf::Clock & clock, bool& enJeu);
bool collisionTourEnnemi(Ennemi ennemi, int valCaseX, int valCaseY);

enum tile{VIDE = 0, HERBE = 1, HERBEEPAISSE = 2, SABLE = 3, TILEOK = 4, BARRICADE = 5, FALAISE_HG = 6, FALAISE_HMG = 7, FALAISE_HM = 8, FALAISE_HMD = 9, FALAISE_HD = 10};

enum nomMap{MAP_1, MAP_2, MAP_3, MAP_HERBE};


void afficherViewMap(sf::RenderWindow& window, const std::vector<sf::View> & tabView, int numView, Carte tabMap[NB_VIEW_MAP], sf::Sprite tile[NB_TILE]);
void afficherViewMap(sf::RenderWindow& window, const std::vector<sf::View> & tabView, int numView, Carte tabMap, sf::Sprite tile[NB_TILE]);
void afficherViewMapNiveau2(sf::RenderWindow& window, const std::vector<sf::View> & tabView, int numView, Carte tabMap[NB_VIEW_MAP], sf::Sprite tile[NB_TILE]);
void afficherViewMapNiveau2(sf::RenderWindow& window, const std::vector<sf::View> & tabView, int numView, Carte tabMap, sf::Sprite tile[NB_TILE]);
void afficherViewMapNiveau3(sf::RenderWindow& window, const std::vector<sf::View> & tabView, int numView, Carte tabMap[NB_VIEW_MAP], sf::Sprite tile[NB_TILE]);
void afficherViewMapNiveau3(sf::RenderWindow& window, const std::vector<sf::View> & tabView, int numView, Carte tabMap, sf::Sprite tile[NB_TILE]);

std::string getStringFromEnum(nomMap e);


#endif // CARTE_H_INCLUDED

