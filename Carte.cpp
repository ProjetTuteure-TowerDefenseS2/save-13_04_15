#include "Carte.h"

using namespace sf;
using namespace std;

Carte::Carte(string nomCarte, int caseFinDeMap_X, int caseFinDeMap_Y)  ///ajouter la position pour faire de l'aléatoire
{
    m_titre = nomCarte;

    ReinitialiserCarte();

    m_caseFinDeMap_X = caseFinDeMap_X;
    m_caseFinDeMap_Y = caseFinDeMap_Y;
}

Carte::Carte()  ///ajouter la position pour faire de l'aléatoire
{

}

void Carte::initialiserMapRecup()
{
    for(int j = 0 ; j < MAX_HAUTEUR_MAP ; j++)
    {
        for(int i = 0 ; i < MAX_LARGEUR_MAP ; i++)
        {
            m_mapRecup[i][j] = m_map[i][j];
        }
    }
}

void Carte::initialiserMap()
{
    for(int j = 0 ; j < MAX_HAUTEUR_MAP ; j++)
    {
        for(int i = 0 ; i < MAX_LARGEUR_MAP ; i++)
        {
            m_map[i][j] = m_mapRecup[i][j];
        }
    }
}



void Carte::ReinitialiserCarte()
{
    ifstream fichier(m_titre.c_str(), ios::in);

    if(fichier)  // si l'ouverture a fonctionné
    {
        int vide;

        for(int i = 0 ; i < NB_TILE ; i++)
        {
            fichier >> m_tileBloquant[i];
        }

        fichier >> vide;


        for(int j = 0 ; j < MAX_HAUTEUR_MAP ; j++)
        {
            for(int i = 0 ; i < MAX_LARGEUR_MAP ; i++)
            {
                fichier >> m_map[i][j];
            }
        }

        for(int j = 0 ; j < MAX_HAUTEUR_MAP ; j++)
        {
            for(int i = 0 ; i < MAX_LARGEUR_MAP ; i++)
            {
                fichier >> m_mapNiveau2[i][j];
            }
        }

        for(int j = 0 ; j < MAX_HAUTEUR_MAP ; j++)
        {
            for(int i = 0 ; i < MAX_LARGEUR_MAP ; i++)
            {
                fichier >> m_mapNiveau3[i][j];
            }
        }

        fichier.close();
    }
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier !" << endl;

    initialiserMapRecup();
}






