#include "ennemis.h"

using namespace sf;
using namespace std;

float length(sf::Vector2f vecteur)
{
    return sqrt(vecteur.x * vecteur.x + vecteur.y * vecteur.y);
}

Ennemi::Ennemi()
{

}

Ennemi::~Ennemi()
{

}

Ennemi::Ennemi(string nomEnnemi, Sprite newSprite, float valVitesse)
{
    creerEnnemi(nomEnnemi, newSprite, valVitesse);
}

void Ennemi::newSprite(Sprite newSprite)
{
    _sprite = newSprite;
}

void Ennemi::creerEnnemi(string nomEnnemi, Sprite newSprite, int nbPv, float valVitesse, int endroitMonstreX, int endroitMonstreY)
{

///coordonées d'apparition du monstre

///attribution du nom du monstre avec celui passé en parametre
    _nomEnnemi = nomEnnemi;

///attribution du sprite pour l'interface graphique
    _sprite = newSprite;

///A completer : attribution des point de vie max, de l'armure et de la vitesse en fonction du type de monstre symboliser par son nom (ici str)

    m_moving = false;
    _ptsVieMax = nbPv;
    _ptsVieActuel = _ptsVieMax;
    _vitesseDeplaEnnemi = valVitesse;

    m_endroitMonstreX = endroitMonstreX;
    m_endroitMonstreY = endroitMonstreY;

    m_etapeActu = 0;
}

void Ennemi::nouvelEndroit(int endroit_X, int endroit_Y)
{
    m_endroitMonstreX = endroit_X;
    m_endroitMonstreY = endroit_Y;
}


void Ennemi::setPos(int newPos_X, int newPos_Y)
{
    _sprite.setPosition(newPos_X, newPos_Y);
}

void Ennemi::setTabOuAller(int numCase, int XouY, int newVal)
{
    m_tabOuAller[numCase][XouY] = newVal;
}

int Ennemi::supprimerPV(int degats)
{

    if(_armure ==0)
    {
        _ptsVieActuel -= degats;
    }

    else
    {
        degats /= _armure;
        _ptsVieActuel -= degats; ///pts de vie actuel est un float dont les virgules sont pris en compte
    }

    if(_ptsVieActuel <= 0)
    {
        _sprite.setPosition(-100, - 100);
        m_vivant = false;
        _ptsVieActuel = 0;
        cout << "le monstre a ete tue !\n";
        ///this.~Ennemi();
    }

    return _ptsVieActuel;
}




bool Ennemi::deplacement(Clock & clock, Carte mapCarte, int etape)
{
    if (m_moving && m_vivant)
    {
        bool boolean = true;
        int a, b;

        Time elapsed = clock.restart();
        _sprite.move(m_velocity * elapsed.asSeconds());
        if(verifColisionDeplacementEnnemi(mapCarte) && etape > 2)
        {
            _sprite.move(-m_velocity * elapsed.asSeconds());
            m_moving = false;
            m_velocity.x = 0;
            m_velocity.y = 0;
            boolean = false;
            cout << endl << "STOP" << endl;
        }

        if (length(m_target - _sprite.getPosition()) <= 5)
            m_moving = false;

        return boolean;
    }
}

void Ennemi::choixZone(Texture texture, RenderWindow & window, Clock & clock, int posX, int posY)
{
    Vector2i cursor(posX, posY);
    m_target = window.mapPixelToCoords(cursor);
    m_velocity = m_target - _sprite.getPosition();
    m_velocity = m_velocity / length(m_velocity) * _vitesseDeplaEnnemi;

    //cout << endl << "posX : " << posX << " ; posY : " << posY << " ; targetX : " << m_target.x << " ; targetY : " << m_target.y << " X: " << m_velocity.x << " Y: " << m_velocity.y << endl;
    m_moving = true;
    clock.restart();
}


void Ennemi::afficheEnnemi(RenderWindow & window ) const
{
    if(m_vivant)
    {
        window.draw(_sprite);
    }
}

bool Ennemi::verifColisionDeplacementEnnemi(Carte mapCarte)
{
    int nb3 = 0;
    bool collision = false;

    int posMob_X = (int)_sprite.getPosition().x;
    int posMob_Y = (int)_sprite.getPosition().y;


    if(m_velocity.x < -30)
    {
        if(m_velocity.y < -30)///5 haut gauche
        {

            if(mapCarte.getCaseBloquante(mapCarte.getNumCaseMap((posMob_X) / LARGEUR_TILE, (posMob_Y - nb3) / HAUTEUR_TILE)) == 1 )/*||
                        tileBloquant[map[(posMob_X - nb3) / LARGEUR_TILE][(posMob_Y + 16) / HAUTEUR_TILE]] == 1)*/
            {
                collision = true;
                cout << endl << "Collision haut gauche" << " X: " << m_velocity.x << " Y: " << m_velocity.y << endl;
            }
        }
        else if(m_velocity.y > 30)///7 bas gauche
        {
            if(mapCarte.getCaseBloquante(mapCarte.getNumCaseMap((posMob_X) / LARGEUR_TILE, (posMob_Y + HAUTEUR_TILE + nb3) / HAUTEUR_TILE)) == 1)/* ||
                        tileBloquant[map[(posMob_X - nb3) / LARGEUR_TILE][(posMob_Y + 16) / HAUTEUR_TILE]] == 1)*/
            {
                collision = true;
                cout << endl << "Collision bas gauche" << " X: " << m_velocity.x << " Y: " << m_velocity.y << endl;
            }
        }
        else ///2 gauche
        {
            if (mapCarte.getCaseBloquante(mapCarte.getNumCaseMap((posMob_X - nb3) / LARGEUR_TILE, (posMob_Y + 16) / HAUTEUR_TILE)) == 1)
            {
                collision = true;
                cout << endl << "Collision gauche" << " X: " << m_velocity.x << " Y: " << m_velocity.y << endl;
            }
        }
    }
    else if(m_velocity.x > 30)
    {
        if(m_velocity.y < -30)///6 haut droite
        {
            if (mapCarte.getCaseBloquante(mapCarte.getNumCaseMap((posMob_X + LARGEUR_TILE) / LARGEUR_TILE, (posMob_Y - nb3) / HAUTEUR_TILE)) == 1)/* ||
                        tileBloquant[map[(posMob_X + LARGEUR_TILE + nb3) / LARGEUR_TILE][(posMob_Y + 16) / HAUTEUR_TILE]] == 1)*/
            {
                collision = true;
                cout << endl << "Collision haut droite" << " X: " << m_velocity.x << " Y: " << m_velocity.y << endl;
            }
        }
        else if(m_velocity.y > 30)///8 bas droite
        {
            if (mapCarte.getCaseBloquante(mapCarte.getNumCaseMap((posMob_X  + LARGEUR_TILE) / LARGEUR_TILE, (posMob_Y + HAUTEUR_TILE + nb3) / HAUTEUR_TILE)) == 1)/* ||
                        tileBloquant[map[(posMob_X + LARGEUR_TILE + nb3) / LARGEUR_TILE][(posMob_Y + 16) / HAUTEUR_TILE]] == 1)*/
            {
                collision = true;
                cout << endl << "Collision bas droite" << " X: " << m_velocity.x << " Y: " << m_velocity.y << endl;
            }
        }
        else ///1 droite
        {
            if (mapCarte.getCaseBloquante(mapCarte.getNumCaseMap((posMob_X + TAILLE_BLOC + nb3) / LARGEUR_TILE, (posMob_Y + 16) / HAUTEUR_TILE)) == 1)
            {
                collision = true;
                cout << endl << "Collision droite" << " X: " << m_velocity.x << " Y: " << m_velocity.y << endl;
            }
        }
    }
    else
    {
        if(m_velocity.y < -30)///4 haut
        {
            if (mapCarte.getCaseBloquante(mapCarte.getNumCaseMap((posMob_X + 16) / LARGEUR_TILE, (posMob_Y - nb3) / HAUTEUR_TILE)) == 1)
            {
                collision = true;
                cout << endl << "Collision haut" << " X: " << m_velocity.x << " Y: " << m_velocity.y << endl;
            }
        }
        else if(m_velocity.y > 30)///3 bas
        {
            if (mapCarte.getCaseBloquante(mapCarte.getNumCaseMap((posMob_X + 16) / LARGEUR_TILE, (posMob_Y + TAILLE_BLOC + nb3) / HAUTEUR_TILE)) == 1)
            {
                collision = true;
                cout << endl << "Collision bas" << " X: " << m_velocity.x << " Y: " << m_velocity.y << endl;
            }
        }
        else
        {
            cout << endl << "Ennemi immobile" << endl;
        }
    }

    return collision;
}







