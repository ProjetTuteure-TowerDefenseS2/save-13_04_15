#ifndef CARTE_H_INCLUDED
#define CARTE_H_INCLUDED


#include "Tour.h"

#include <fstream>
#include <sys/types.h>
#include <stdio.h>

#include "string.h"
#include <SFML/Graphics.hpp>
#include <cmath>

#include <iostream>



const int MAX_ENNEMIS = 50;
const int TAILLE_MAX_MAP = 300;

const int LARGEUR_TILE = 32;
const int HAUTEUR_TILE = 32;

const int TAILLE_BLOC = 32;

const int MAX_LARGEUR_MAP = 25;
const int MAX_HAUTEUR_MAP = 22;

const int NB_TILE = 44;
const int DECOUPAGE_LARGEUR = 20;

const int NB_ENNEMI = 10;
const int NB_TOUR = 10;

const int NB_VIEW_MAP = 6;
const int NB_NIVEAU = 3;

class Carte{

public :
    Carte();
    Carte(std::string nomCarte, int caseFinDeMap_X, int caseFinDeMap_Y);
    ///faudra ajouter un setItineraire() et un setZoneInterdite() pour les guider les deplacements dans la map

    void initialiserMap();
    void initialiserMapRecup();
    void ReinitialiserCarte();

    void setNumCaseMap(int valX, int valY, int newValeur){m_map[valX][valY] = newValeur;}
    void setNumCaseMapNiveau2(int valX, int valY, int newValeur){m_mapNiveau2[valX][valY] = newValeur;}
    void setNumCaseMapRecup(int valX, int valY, int newValeur){m_mapRecup[valX][valY] = newValeur;}
    void SetNumCaseMapViaMapRecup(int valX, int valY){m_map[valX][valY] = m_mapRecup[valX][valY];}
    void SetNumCaseMapViaMapRecupNiveau2(int valX, int valY){m_mapNiveau2[valX][valY] = m_mapRecup[valX][valY];}

    int getCaseFin_X() const{return m_caseFinDeMap_X;}
    int getCaseFin_Y() const{return m_caseFinDeMap_Y;}
    int getNumCaseMap(int valX, int valY) const{return m_map[valX][valY];}
    int getNumCaseMapNiveau3(int valX, int valY) const{return m_mapNiveau3[valX][valY];}
    int getNumCaseMapNiveau2(int valX, int valY) const{return m_mapNiveau2[valX][valY];}
    int getNumCaseMapRecup(int valX, int valY) const{return m_mapRecup[valX][valY];}
    bool getCaseBloquante(int val) const{return m_tileBloquant[val];}


    void setNom(std::string nomCarte){m_titre = nomCarte;}

private :

    /// ajouter un nb pour chaque type de monstre a apparaitre

    std::string m_titre;

    int m_map[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP];
    int m_mapNiveau2[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP];
    int m_mapNiveau3[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP];
	int m_mapRecup[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP];
    bool m_tileBloquant[NB_TILE];
    bool m_tileBloquantNiveau2[NB_TILE];
    bool m_tileBloquantNiveau3[NB_TILE];
    int m_caseFinDeMap_X;
    int m_caseFinDeMap_Y;

};

#endif // CARTE_H_INCLUDED
