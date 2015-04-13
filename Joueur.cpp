
#include "Joueur.h"

using namespace sf;
using namespace std;

Joueur::Joueur(void)
{
	m_or = 5000;
	m_pv = 100;
}

string Joueur::changerAffichageOr()
{
    string texteTemp = "Reste : ";
    texteTemp += int_to_string(m_or);
    texteTemp += "$";
    return texteTemp;
}
void Joueur::retirerOr(int difference)
{
    m_or = m_or-difference;
}

void Joueur::ajouterOr(int ajout)
{
    m_or = m_or + ajout;
}
