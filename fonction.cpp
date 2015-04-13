#include "constante.h"

using namespace sf;
using namespace std;

void gestionEvent(Event event, RenderWindow &window, bool &dep, Carte &mapNum1, int &imageActu,
                  bool& poserTour, bool& poserTabTour, Ennemi &ennemi, Clock & clock, bool& enJeu)
{
    if (event.type == sf::Event::Closed)
        window.close();
    if (event.type == sf::Event::KeyPressed)//MouseButtonReleased pour relacher
    {
        if (event.key.code == sf::Keyboard::Return)
        {
            //if(depClique){depClique = false;x = 0;ennemi.setPos(279,258);}
            //else{depClique = true;}

            /*for(int i = 0 ; i < NB_ENNEMI ; i++)
            {
                tabEnnemi[i].setPos(-32 * i , 0);
                tabEnnemi[i].nouvelEndroit(0, 0);
            }*/
            ennemi.nouvelEndroit(0, 0);
            dep = true;
        }
        else if (event.key.code == sf::Keyboard::Tab  )
        {
            mapNum1.ReinitialiserCarte();
        }

        if (event.key.code == sf::Keyboard::Numpad1 )
        {
            imageActu = 0;
        }
        else if (event.key.code == sf::Keyboard::Numpad2 )
        {
            imageActu = 1;
        }
        else if (event.key.code == sf::Keyboard::Numpad3 )
        {
            imageActu = 2;
        }

        if (event.key.code == sf::Keyboard::Escape )
        {
            enJeu = false;
        }
    }
    if (event.type == sf::Event::LostFocus)
    {

    }
    else if (event.type == sf::Event::GainedFocus)
    {
        ennemi.reinitialiserClock(clock);
    }
}


void chargerMap(string level, int map[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP], bool tileBloquant[NB_TILE])
{
    ifstream fichier(level.c_str(), ios::in);

    if(fichier)  // si l'ouverture a fonctionné
    {
        for(int i = 0 ; i < NB_TILE ; i++)
        {
            fichier >> tileBloquant[i];
        }
        for(int i = 0 ; i < MAX_HAUTEUR_MAP ; i++)
        {
            for(int j = 0 ; j < MAX_LARGEUR_MAP ; j++)
            {
                fichier >> map[j][i];
            }
        }

        fichier.close();
    }
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier !" << endl;
}



bool trouveA_B(int posSouris_X, int posSouris_Y, int &case_X, int &case_Y)
{
    bool trouveCoordo = false;
    if(posSouris_Y < MAX_HAUTEUR_MAP * HAUTEUR_TILE)
    {
        case_X = 0;
        while(case_X <= MAX_LARGEUR_MAP && !trouveCoordo)
        {
            if((case_X * LARGEUR_TILE) > posSouris_X)
            {
                case_X--;
                case_Y = 0;
                while(case_Y <= MAX_HAUTEUR_MAP && !trouveCoordo)
                {
                    if((case_Y * HAUTEUR_TILE) > posSouris_Y)
                    {
                        case_Y--;
                        trouveCoordo = true;
                    }
                    case_Y++;
                }
            }

            case_X++;
        }
        if(case_X > 0){case_X--;}
        if(case_Y > 0){case_Y--;}
    }
    return trouveCoordo;
}


bool dijkstra(int numDepartX, int numDepartY, int numATrouverX, int numATrouverY,
              int mapNum[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP], int tabOuAller[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2],
              int &nbCase)
{
    int numTemp = 0;

    int map[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP][2];

    for(int j = 0; j < MAX_HAUTEUR_MAP; j++)
    {
        for(int i = 0; i < MAX_LARGEUR_MAP; i++)
        {
            map[i][j][0] = numTemp;
            numTemp++;
            map[i][j][1] = 0;
        }
    }


    int tabPredes[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP];
    int tabATeste[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2];

    int nbValeur = 1, nbValeur2 = 0;

    int noeudPetitI = numDepartX;
    int noeudPetitJ = numDepartY;

    int varLargeur = 0, varHauteur = 0, testNbValeurFaite = 0;

    tabATeste[map[noeudPetitI][noeudPetitJ][0]][0] = 0;
    tabPredes[noeudPetitI][noeudPetitJ] = -1;
    map[noeudPetitI][noeudPetitJ][1] = 1;


    bool nonTrouve = true, trouverTester = false;

    int valeurAntiBug = 0;

    while(nonTrouve && valeurAntiBug <= HAUTEUR_TILE * LARGEUR_TILE)
    {
        testNbValeurFaite = 0;
        while(testNbValeurFaite < nbValeur && nonTrouve)
        {
            varLargeur = 0;
            while(varLargeur < MAX_LARGEUR_MAP && !trouverTester)
            {
                varHauteur = 0;
                while(varHauteur < MAX_HAUTEUR_MAP && !trouverTester)
                {
                    if(map[varLargeur][varHauteur][0] == tabATeste[testNbValeurFaite][0])
                    {
                        noeudPetitI = varLargeur;
                        noeudPetitJ = varHauteur;
                        trouverTester = true;
                    }
                    varHauteur++;
                }
                varLargeur++;
            }
            trouverTester = false;

            if(map[numATrouverX][numATrouverY][0] == map[noeudPetitI][noeudPetitJ][0])
            {
                nonTrouve = false;
            }
            else
            {
                if(noeudPetitI + 1 < MAX_LARGEUR_MAP)
                {
                    trouveNewCase(noeudPetitI + 1, noeudPetitJ, noeudPetitI, noeudPetitJ, nbValeur2, map, tabPredes, tabATeste, mapNum[noeudPetitI][noeudPetitJ]);
                }
                if(noeudPetitI - 1 >= 0)
                {
                    trouveNewCase(noeudPetitI - 1, noeudPetitJ, noeudPetitI, noeudPetitJ, nbValeur2, map, tabPredes, tabATeste, mapNum[noeudPetitI][noeudPetitJ]);
                }
                if(noeudPetitJ + 1 < MAX_HAUTEUR_MAP)
                {
                    trouveNewCase(noeudPetitI, noeudPetitJ + 1, noeudPetitI, noeudPetitJ, nbValeur2, map, tabPredes, tabATeste, mapNum[noeudPetitI][noeudPetitJ]);
                }
                if(noeudPetitJ - 1 >= 0)
                {
                    trouveNewCase(noeudPetitI, noeudPetitJ - 1, noeudPetitI, noeudPetitJ, nbValeur2, map, tabPredes, tabATeste, mapNum[noeudPetitI][noeudPetitJ]);
                }

            }

            testNbValeurFaite++;
        }
        if(nbValeur2 > 0 && nonTrouve)
        {
            for(int i = 0 ; i < nbValeur2 ; i++)
            {
                tabATeste[i][0] = tabATeste[i][1];
            }
            nbValeur = nbValeur2;
            nbValeur2 = 0;
        }
        valeurAntiBug++;


    }


    if(valeurAntiBug >= HAUTEUR_TILE * LARGEUR_TILE)
    {
        cout << endl << "ERREUR DIJKSTRA !!!!" << endl << endl;
        return false;
    }
    else
    {
        //cout << endl;
        nbCase = 0;
        valeurAntiBug--;
        while(tabPredes[numATrouverX][numATrouverY] != -1 && valeurAntiBug > -1)
        {
            //cout << "Num Case : " << valeurAntiBug << " case actu : " << map[numATrouverX][numATrouverY][0] << " predescesseur : " << tabPredes[numATrouverX][numATrouverY] << endl;
            mapNum[numATrouverX][numATrouverY] = TILEOK; ///On met l'image "OK" pour le chemin
            valeurAntiBug--;
            varLargeur = 0;
            while(varLargeur < MAX_LARGEUR_MAP && !trouverTester)
            {
                varHauteur = 0;
                while(varHauteur < MAX_HAUTEUR_MAP && !trouverTester)
                {
                    if(map[varLargeur][varHauteur][0] == tabPredes[numATrouverX][numATrouverY])
                    {
                        tabOuAller[nbCase][0] = numATrouverX;
                        tabOuAller[nbCase][1] = numATrouverY;
                        nbCase++;
                        numATrouverX = varLargeur;
                        numATrouverY = varHauteur;
                        trouverTester = true;
                    }
                    varHauteur++;
                }
                varLargeur++;
            }

            trouverTester = false;
        }

        nbCase--;

        if(numDepartX != numATrouverX || numDepartY != numATrouverY)
        {
            cout << endl << "ERREUR DIJKSTRA !!!! numX" << numDepartX << " numTrouX: " << numATrouverX << endl << endl;
            return false;
        }
        //cout << "case actu : " << map[numATrouverX][numATrouverY][0] << endl;

        cout << endl << "OK DIJKSTRA !!!! numX" << numDepartX << " numTrouX: " << numATrouverX << endl << endl;
        return true;
    }

}

bool dijkstra(int numDepartX, int numDepartY, int numATrouverX, int numATrouverY,
              int tabOuAller[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2], int &nbCase, Carte &mapCarte)
{
    int numTemp = 0;

    int map[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP][2];

    for(int j = 0; j < MAX_HAUTEUR_MAP; j++)
    {
        for(int i = 0; i < MAX_LARGEUR_MAP; i++)
        {
            map[i][j][0] = numTemp;
            numTemp++;
            map[i][j][1] = 0;
        }
    }


    int tabPredes[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP];
    int tabATeste[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2];

    int nbValeur = 1, nbValeur2 = 0;

    int noeudPetitI = numDepartX;
    int noeudPetitJ = numDepartY;

    int varLargeur = 0, varHauteur = 0, testNbValeurFaite = 0;

    tabATeste[map[noeudPetitI][noeudPetitJ][0]][0] = 0;
    tabPredes[noeudPetitI][noeudPetitJ] = -1;
    map[noeudPetitI][noeudPetitJ][1] = 1;


    bool nonTrouve = true, trouverTester = false;

    int valeurAntiBug = 0;

    while(nonTrouve && valeurAntiBug <= MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP)
    {
        testNbValeurFaite = 0;
        while(testNbValeurFaite < nbValeur && nonTrouve)
        {
            varLargeur = 0;
            while(varLargeur < MAX_LARGEUR_MAP && !trouverTester)
            {
                varHauteur = 0;
                while(varHauteur < MAX_HAUTEUR_MAP && !trouverTester)
                {
                    if(map[varLargeur][varHauteur][0] == tabATeste[testNbValeurFaite][0])
                    {
                        noeudPetitI = varLargeur;
                        noeudPetitJ = varHauteur;
                        trouverTester = true;
                    }
                    varHauteur++;
                }
                varLargeur++;
            }
            trouverTester = false;
            //cout << "mapActu : " << map[noeudPetitI][noeudPetitJ][0] << " mapATrouver : " << map[numATrouverX][numATrouverY][0] << endl;
            if(map[numATrouverX][numATrouverY][0] == map[noeudPetitI][noeudPetitJ][0])
            {
                nonTrouve = false;
            }
            else
            {
                if(noeudPetitI + 1 < MAX_LARGEUR_MAP)
                {
                    trouveNewCase(noeudPetitI + 1, noeudPetitJ, noeudPetitI, noeudPetitJ, nbValeur2, map, tabPredes, tabATeste, mapCarte.getNumCaseMap(noeudPetitI, noeudPetitJ));
                }
                if(noeudPetitI - 1 >= 0)
                {
                    trouveNewCase(noeudPetitI - 1, noeudPetitJ, noeudPetitI, noeudPetitJ, nbValeur2, map, tabPredes, tabATeste, mapCarte.getNumCaseMap(noeudPetitI, noeudPetitJ));
                }
                if(noeudPetitJ + 1 < MAX_HAUTEUR_MAP)
                {
                    trouveNewCase(noeudPetitI, noeudPetitJ + 1, noeudPetitI, noeudPetitJ, nbValeur2, map, tabPredes, tabATeste, mapCarte.getNumCaseMap(noeudPetitI, noeudPetitJ));
                }
                if(noeudPetitJ - 1 >= 0)
                {
                    trouveNewCase(noeudPetitI, noeudPetitJ - 1, noeudPetitI, noeudPetitJ, nbValeur2, map, tabPredes, tabATeste, mapCarte.getNumCaseMap(noeudPetitI, noeudPetitJ));
                }

            }

            testNbValeurFaite++;
        }
        if(nbValeur2 > 0 && nonTrouve)
        {
            for(int i = 0 ; i < nbValeur2 ; i++)
            {
                tabATeste[i][0] = tabATeste[i][1];
            }
            nbValeur = nbValeur2;
            nbValeur2 = 0;
        }
        valeurAntiBug++;


    }


    if(valeurAntiBug >= MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP)
    {
        cout << endl << "ERREUR DIJKSTRA !!!!" << endl << endl;
        return false;
    }
    else
    {
        //cout << endl;
        nbCase = 0;
        valeurAntiBug--;
        while(tabPredes[numATrouverX][numATrouverY] != -1 && valeurAntiBug > -1)
        {
            cout << "Num Case : " << valeurAntiBug << " case actu : " << map[numATrouverX][numATrouverY][0] << " predescesseur : " << tabPredes[numATrouverX][numATrouverY] << endl;

            mapCarte.setNumCaseMap(numATrouverX, numATrouverY, TILEOK);
            valeurAntiBug--;
            varLargeur = 0;
            while(varLargeur < MAX_LARGEUR_MAP && !trouverTester)
            {
                varHauteur = 0;
                while(varHauteur < MAX_HAUTEUR_MAP && !trouverTester)
                {
                    if(map[varLargeur][varHauteur][0] == tabPredes[numATrouverX][numATrouverY])
                    {
                        tabOuAller[nbCase][0] = numATrouverX;
                        tabOuAller[nbCase][1] = numATrouverY;
                        nbCase++;
                        numATrouverX = varLargeur;
                        numATrouverY = varHauteur;
                        trouverTester = true;
                    }
                    varHauteur++;
                }
                varLargeur++;
            }

            trouverTester = false;
        }

        nbCase--;

        if(numDepartX != numATrouverX || numDepartY != numATrouverY)
        {
            cout << endl << "ERREUR DIJKSTRA !!!! numX: " << numDepartX << " numTrouX: " << numATrouverX << endl << endl;
            return false;
        }
        //cout << "case actu : " << map[numATrouverX][numATrouverY][0] << endl;

        cout << endl << "OK DIJKSTRA !!!! numX " << numDepartX << " numTrouX: " << numATrouverX << endl << endl;
        return true;
    }

}


void trouveNewCase(int noeudPetitI, int noeudPetitJ, int noeudPetitIBase, int noeudPetitJBase, int &nbValeur2, int map[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP][2], int tabPredes[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP], int tabATeste[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2], int valCase)
{
    if(map[noeudPetitI][noeudPetitJ][1] == 0 && testMap(valCase))
    {
            map[noeudPetitI][noeudPetitJ][1] = 1;
            tabPredes[noeudPetitI][noeudPetitJ] = map[noeudPetitIBase][noeudPetitJBase][0];
            tabATeste[nbValeur2][1] = map[noeudPetitI][noeudPetitJ][0];
            nbValeur2++;
    }
}

bool testMap(int val)
{
    bool different = true;
    if(val >= BARRICADE)
    {
        different = false;
    }
    return different;
}



string int_to_string(int nb)
{
    string ss;
    stringstream out;
    out << nb;
    ss = out.str();

    return ss;
}








bool dijkstra(int numATrouverX, int numATrouverY, Ennemi tabEnnemiActu[NB_ENNEMI], int numEnnemi, Carte &mapCarte)
{
    int numTemp = 0;

    int map[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP][2];

    for(int j = 0; j < MAX_HAUTEUR_MAP; j++)
    {
        for(int i = 0; i < MAX_LARGEUR_MAP; i++)
        {
            map[i][j][0] = numTemp;
            numTemp++;
            map[i][j][1] = 0;
        }
    }


    int tabPredes[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP];
    int tabATeste[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2];

    int nbValeur = 1, nbValeur2 = 0;

    int noeudPetitI = tabEnnemiActu[numEnnemi].getEndroitX();
    int noeudPetitJ = tabEnnemiActu[numEnnemi].getEndroitY();

    int varLargeur = 0, varHauteur = 0, testNbValeurFaite = 0;

    tabATeste[0][0] = map[noeudPetitI][noeudPetitJ][0];
    tabPredes[noeudPetitI][noeudPetitJ] = -1;
    map[noeudPetitI][noeudPetitJ][1] = 1;

    bool nonTrouve = true, trouverTester = false;

    int valeurAntiBug = 0;

    while(nonTrouve && valeurAntiBug <= HAUTEUR_TILE * LARGEUR_TILE)
    {
        testNbValeurFaite = 0;
        while(testNbValeurFaite < nbValeur && nonTrouve)
        {
            varLargeur = 0;
            while(varLargeur < MAX_LARGEUR_MAP && !trouverTester)
            {
                varHauteur = 0;
                while(varHauteur < MAX_HAUTEUR_MAP && !trouverTester)
                {

                    if(map[varLargeur][varHauteur][0] == tabATeste[testNbValeurFaite][0])
                    {
                        noeudPetitI = varLargeur;
                        noeudPetitJ = varHauteur;
                        trouverTester = true;
                    }
                    varHauteur++;
                }
                varLargeur++;
            }

            trouverTester = false;

            if(map[numATrouverX][numATrouverY][0] == map[noeudPetitI][noeudPetitJ][0])
            {
                nonTrouve = false;
            }
            else
            {
                if(noeudPetitI + 1 < MAX_LARGEUR_MAP)
                {
                    trouveNewCase(noeudPetitI + 1, noeudPetitJ, noeudPetitI, noeudPetitJ, nbValeur2, map, tabPredes, tabATeste, mapCarte.getNumCaseMap(noeudPetitI, noeudPetitJ));
                }
                if(noeudPetitI - 1 >= 0)
                {
                    trouveNewCase(noeudPetitI - 1, noeudPetitJ, noeudPetitI, noeudPetitJ, nbValeur2, map, tabPredes, tabATeste, mapCarte.getNumCaseMap(noeudPetitI, noeudPetitJ));
                }
                if(noeudPetitJ + 1 < MAX_HAUTEUR_MAP)
                {
                    trouveNewCase(noeudPetitI, noeudPetitJ + 1, noeudPetitI, noeudPetitJ, nbValeur2, map, tabPredes, tabATeste, mapCarte.getNumCaseMap(noeudPetitI, noeudPetitJ));
                }
                if(noeudPetitJ - 1 >= 0)
                {
                    trouveNewCase(noeudPetitI, noeudPetitJ - 1, noeudPetitI, noeudPetitJ, nbValeur2, map, tabPredes, tabATeste, mapCarte.getNumCaseMap(noeudPetitI, noeudPetitJ));
                }

            }

            testNbValeurFaite++;
        }
        if(nbValeur2 > 0 && nonTrouve)
        {
            for(int i = 0 ; i < nbValeur2 ; i++)
            {
                tabATeste[i][0] = tabATeste[i][1];
            }
            nbValeur = nbValeur2;
            nbValeur2 = 0;
        }
        valeurAntiBug++;


    }


    if(valeurAntiBug >= HAUTEUR_TILE * LARGEUR_TILE)
    {
        cout << endl << "ERREUR DIJKSTRA VALEUR ANTI BUG!!!!" << endl << endl;
        return false;
    }
    else
    {
        //cout << endl;
        int nbCase = 0;
        valeurAntiBug--;
        while(tabPredes[numATrouverX][numATrouverY] != -1 && valeurAntiBug > -1)
        {
            //cout << "Num Case : " << valeurAntiBug << " case actu : " << map[numATrouverX][numATrouverY][0] << " predescesseur : " << tabPredes[numATrouverX][numATrouverY] << endl;

            valeurAntiBug--;
            varLargeur = 0;
            while(varLargeur < MAX_LARGEUR_MAP && !trouverTester)
            {
                varHauteur = 0;
                while(varHauteur < MAX_HAUTEUR_MAP && !trouverTester)
                {
                    if(map[varLargeur][varHauteur][0] == tabPredes[numATrouverX][numATrouverY])
                    {
                        tabEnnemiActu[numEnnemi].setTabOuAller(nbCase, 0, numATrouverX);
                        tabEnnemiActu[numEnnemi].setTabOuAller(nbCase, 1, numATrouverY);
                        nbCase++;
                        numATrouverX = varLargeur;
                        numATrouverY = varHauteur;
                        trouverTester = true;
                    }
                    varHauteur++;
                }
                varLargeur++;
            }

            trouverTester = false;
        }

        nbCase--;

        tabEnnemiActu[numEnnemi].setNbCase(nbCase);

        if(tabEnnemiActu[numEnnemi].getEndroitX() != numATrouverX || tabEnnemiActu[numEnnemi].getEndroitY() != numATrouverY)
        {
            cout << endl << "ERREUR DIJKSTRA !!!! numX" << tabEnnemiActu[numEnnemi].getEndroitX() << " numTrouX: " << numATrouverX << endl << endl;
            return false;
        }
        //cout << "case actu : " << map[numATrouverX][numATrouverY][0] << endl;

        cout << endl << "OK DIJKSTRA !!!! numX" << tabEnnemiActu[numEnnemi].getEndroitX() << " numTrouX: " << numATrouverX << endl << endl;
        return true;
    }

}



bool dijkstra(int numATrouverX, int numATrouverY, Ennemi &ennemi, Carte &mapCarte)
{
    int numTemp = 0;

    int map[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP][2];

    for(int j = 0; j < MAX_HAUTEUR_MAP; j++)
    {
        for(int i = 0; i < MAX_LARGEUR_MAP; i++)
        {
            map[i][j][0] = numTemp;
            numTemp++;
            map[i][j][1] = 0;
        }
    }


    int tabPredes[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP];
    int tabATeste[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2];

    int nbValeur = 1, nbValeur2 = 0;

    int noeudPetitI = ennemi.getEndroitX();
    int noeudPetitJ = ennemi.getEndroitY();
    cout << endl << ennemi.getEndroitX() << " " << ennemi.getEndroitY() << endl;
    int varLargeur = 0, varHauteur = 0, testNbValeurFaite = 0;

    tabATeste[0][0] = map[noeudPetitI][noeudPetitJ][0];
    tabPredes[noeudPetitI][noeudPetitJ] = -1;
    map[noeudPetitI][noeudPetitJ][1] = 1;

    bool nonTrouve = true, trouverTester = false;

    int valeurAntiBug = 0;

    while(nonTrouve && valeurAntiBug <= HAUTEUR_TILE * LARGEUR_TILE)
    {
        testNbValeurFaite = 0;
        while(testNbValeurFaite < nbValeur && nonTrouve)
        {
            varLargeur = 0;
            while(varLargeur < MAX_LARGEUR_MAP && !trouverTester)
            {
                varHauteur = 0;
                while(varHauteur < MAX_HAUTEUR_MAP && !trouverTester)
                {

                    if(map[varLargeur][varHauteur][0] == tabATeste[testNbValeurFaite][0])
                    {
                        noeudPetitI = varLargeur;
                        noeudPetitJ = varHauteur;
                        trouverTester = true;
                    }
                    varHauteur++;
                }
                varLargeur++;
            }

            trouverTester = false;

            if(map[numATrouverX][numATrouverY][0] == map[noeudPetitI][noeudPetitJ][0])
            {
                nonTrouve = false;
            }
            else
            {
                if(noeudPetitI + 1 < MAX_LARGEUR_MAP)
                {
                    trouveNewCase(noeudPetitI + 1, noeudPetitJ, noeudPetitI, noeudPetitJ, nbValeur2, map, tabPredes, tabATeste, mapCarte.getNumCaseMapNiveau2(noeudPetitI, noeudPetitJ));
                }
                if(noeudPetitI - 1 >= 0)
                {
                    trouveNewCase(noeudPetitI - 1, noeudPetitJ, noeudPetitI, noeudPetitJ, nbValeur2, map, tabPredes, tabATeste, mapCarte.getNumCaseMapNiveau2(noeudPetitI, noeudPetitJ));
                }
                if(noeudPetitJ + 1 < MAX_HAUTEUR_MAP)
                {
                    trouveNewCase(noeudPetitI, noeudPetitJ + 1, noeudPetitI, noeudPetitJ, nbValeur2, map, tabPredes, tabATeste, mapCarte.getNumCaseMapNiveau2(noeudPetitI, noeudPetitJ));
                }
                if(noeudPetitJ - 1 >= 0)
                {
                    trouveNewCase(noeudPetitI, noeudPetitJ - 1, noeudPetitI, noeudPetitJ, nbValeur2, map, tabPredes, tabATeste, mapCarte.getNumCaseMapNiveau2(noeudPetitI, noeudPetitJ));
                }

            }

            testNbValeurFaite++;
        }
        if(nbValeur2 > 0 && nonTrouve)
        {
            for(int i = 0 ; i < nbValeur2 ; i++)
            {
                tabATeste[i][0] = tabATeste[i][1];
            }
            nbValeur = nbValeur2;
            nbValeur2 = 0;
        }
        valeurAntiBug++;


    }


    if(valeurAntiBug >= HAUTEUR_TILE * LARGEUR_TILE)
    {
        cout << endl << "ERREUR DIJKSTRA VALEUR ANTI BUG!!!!" << endl << endl;
        return false;
    }
    else
    {
        //cout << endl;
        int nbCase = 0;
        valeurAntiBug--;
        while(tabPredes[numATrouverX][numATrouverY] != -1 && valeurAntiBug > -1)
        {
            cout << "Num Case : " << valeurAntiBug << " case actu : " << map[numATrouverX][numATrouverY][0] << " predescesseur : " << tabPredes[numATrouverX][numATrouverY] << endl;

            valeurAntiBug--;
            varLargeur = 0;
            mapCarte.setNumCaseMap(numATrouverX, numATrouverY, TILEOK);
            while(varLargeur < MAX_LARGEUR_MAP && !trouverTester)
            {
                varHauteur = 0;
                while(varHauteur < MAX_HAUTEUR_MAP && !trouverTester)
                {
                    if(map[varLargeur][varHauteur][0] == tabPredes[numATrouverX][numATrouverY])
                    {
                       ennemi.setTabOuAller(nbCase, 0, numATrouverX);
                       ennemi.setTabOuAller(nbCase, 1, numATrouverY);
                        nbCase++;
                        numATrouverX = varLargeur;
                        numATrouverY = varHauteur;
                        trouverTester = true;
                    }
                    varHauteur++;
                }
                varLargeur++;
            }

            trouverTester = false;
        }

        nbCase--;

       ennemi.setNbCase(nbCase);

        if(ennemi.getEndroitX() != numATrouverX ||ennemi.getEndroitY() != numATrouverY)
        {
            cout << endl << "ERREUR DIJKSTRA !!!! numX" <<ennemi.getEndroitX() << " numTrouX: " << numATrouverX << endl << endl;
            return false;
        }
        //cout << "case actu : " << map[numATrouverX][numATrouverY][0] << endl;

        cout << endl << "OK DIJKSTRA !!!! numX" <<ennemi.getEndroitX() << " numTrouX: " << numATrouverX << endl << endl;
        return true;
    }

}


bool collisionTourEnnemi(Ennemi ennemi, int valCaseX, int valCaseY)
{
    return (((ennemi.getPosition().x < (valCaseX * LARGEUR_TILE) + TAILLE_BLOC &&
              ennemi.getPosition().x + TAILLE_BLOC > (valCaseX * LARGEUR_TILE) + TAILLE_BLOC) ||

             (ennemi.getPosition().x < valCaseX * LARGEUR_TILE &&
              ennemi.getPosition().x + TAILLE_BLOC > valCaseX * LARGEUR_TILE)) &&

            ((ennemi.getPosition().y < (valCaseY * HAUTEUR_TILE) + TAILLE_BLOC &&
              ennemi.getPosition().y + TAILLE_BLOC > (valCaseY * HAUTEUR_TILE) + TAILLE_BLOC) ||

            (ennemi.getPosition().y < valCaseY * HAUTEUR_TILE &&
             ennemi.getPosition().y + TAILLE_BLOC > valCaseY * HAUTEUR_TILE)));
}


string getStringFromEnum(nomMap e)
{
  switch (e)
  {
  case MAP_1: return "./maps/map1.txt";
  case MAP_2: return "./maps/map2.txt";
  case MAP_3: return "./maps/map3.txt";
  case MAP_HERBE: return "./maps/map_herbe.txt";
  }
}



void afficherViewMap(RenderWindow& window, const vector<View> & tabView, int numView,Carte tabMap[NB_VIEW_MAP], Sprite tile[NB_TILE])
{
    window.setView(tabView[numView]);

    for(int i = 0; i < MAX_LARGEUR_MAP; i++)
    {
        for(int j = 0; j < MAX_HAUTEUR_MAP; j++)
        {
            if(tabMap[numView].getNumCaseMap(i, j) >= 0 || tabMap[numView].getNumCaseMap(i, j) < NB_TILE)
            {
                tile[tabMap[numView].getNumCaseMap(i, j)].setPosition(i * LARGEUR_TILE, j * HAUTEUR_TILE);
                window.draw(tile[tabMap[numView].getNumCaseMap(i, j)]);
            }
        }
    }
}

void afficherViewMapNiveau2(RenderWindow& window, const vector<View> & tabView, int numView, Carte tabMap[NB_VIEW_MAP], Sprite tileNiveau2[NB_TILE])
{
    window.setView(tabView[numView]);

    for(int i = 0; i < MAX_LARGEUR_MAP; i++)
    {
        for(int j = 0; j < MAX_HAUTEUR_MAP; j++)
        {
            if(tabMap[numView].getNumCaseMapNiveau2(i, j) >= 0 || tabMap[numView].getNumCaseMapNiveau2(i, j) < NB_TILE)
            {
                tileNiveau2[tabMap[numView].getNumCaseMapNiveau2(i, j)].setPosition(i * LARGEUR_TILE, j * HAUTEUR_TILE);
                window.draw(tileNiveau2[tabMap[numView].getNumCaseMapNiveau2(i, j)]);
            }
        }
    }
}

void afficherViewMapNiveau3(RenderWindow& window, const vector<View> & tabView, int numView, Carte tabMap[NB_VIEW_MAP], Sprite tileNiveau3[NB_TILE])
{
    window.setView(tabView[numView]);

    for(int i = 0; i < MAX_LARGEUR_MAP; i++)
    {
        for(int j = 0; j < MAX_HAUTEUR_MAP; j++)
        {
            if(tabMap[numView].getNumCaseMapNiveau3(i, j) >= 0 || tabMap[numView].getNumCaseMapNiveau3(i, j) < NB_TILE)
            {
                tileNiveau3[tabMap[numView].getNumCaseMapNiveau3(i, j)].setPosition(i * LARGEUR_TILE, j * HAUTEUR_TILE);
                window.draw(tileNiveau3[tabMap[numView].getNumCaseMapNiveau3(i, j)]);
            }
        }
    }
}

void afficherViewMap(RenderWindow& window, const vector<View> & tabView, int numView, Carte tabMap, Sprite tile[NB_TILE])
{
    window.setView(tabView[numView]);

    for(int i = 0; i < MAX_LARGEUR_MAP; i++)
    {
        for(int j = 0; j < MAX_HAUTEUR_MAP; j++)
        {
            if(tabMap.getNumCaseMap(i, j) >= 0 || tabMap.getNumCaseMap(i, j) < NB_TILE)
            {
                tile[tabMap.getNumCaseMap(i, j)].setPosition(i * LARGEUR_TILE, j * HAUTEUR_TILE);
                window.draw(tile[tabMap.getNumCaseMap(i, j)]);
            }
        }
    }
}

void afficherViewMapNiveau2(RenderWindow& window, const vector<View> & tabView, int numView, Carte tabMap, Sprite tileNiveau2[NB_TILE])
{
    window.setView(tabView[numView]);

    for(int i = 0; i < MAX_LARGEUR_MAP; i++)
    {
        for(int j = 0; j < MAX_HAUTEUR_MAP; j++)
        {
            if(tabMap.getNumCaseMapNiveau2(i, j) >= 0 || tabMap.getNumCaseMapNiveau2(i, j) < NB_TILE)
            {
                tileNiveau2[tabMap.getNumCaseMapNiveau2(i, j)].setPosition(i * LARGEUR_TILE, j * HAUTEUR_TILE);
                window.draw(tileNiveau2[tabMap.getNumCaseMapNiveau2(i, j)]);
            }
        }
    }
}

void afficherViewMapNiveau3(RenderWindow& window, const vector<View> & tabView, int numView, Carte tabMap, Sprite tileNiveau3[NB_TILE])
{
    window.setView(tabView[numView]);

    for(int i = 0; i < MAX_LARGEUR_MAP; i++)
    {
        for(int j = 0; j < MAX_HAUTEUR_MAP; j++)
        {
            if(tabMap.getNumCaseMapNiveau3(i, j) >= 0 || tabMap.getNumCaseMapNiveau3(i, j) < NB_TILE)
            {
                tileNiveau3[tabMap.getNumCaseMapNiveau3(i, j)].setPosition(i * LARGEUR_TILE, j * HAUTEUR_TILE);
                window.draw(tileNiveau3[tabMap.getNumCaseMapNiveau3(i, j)]);
            }
        }
    }
}
