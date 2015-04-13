#include "Tir.h"

using namespace sf;
using namespace std;

Tir::Tir()
{

}

Tir::Tir(string nomTexture, string nomTexture_2, string nomTexture_3, string nomTexture_4, string nomTexture_5)
{
    if (!m_texture[0].loadFromFile(nomTexture)){cout << "Tir.cpp : Impossible de charger : " << nomTexture << endl;}
    m_nbTexture = 1;

    if(nomTexture_2 != "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e")
    {
        if (!m_texture[m_nbTexture++].loadFromFile(nomTexture_2)){cout << "Tir.cpp : Impossible de charger : " << nomTexture_2 << endl;}
    }

    if(nomTexture_3 != "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e")
    {
        if (!m_texture[m_nbTexture++].loadFromFile(nomTexture_3)){cout << "Tir.cpp : Impossible de charger : " << nomTexture_3 << endl;}
    }

    if(nomTexture_4 != "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e")
    {
        if (!m_texture[m_nbTexture++].loadFromFile(nomTexture_4)){cout << "Tir.cpp : Impossible de charger : " << nomTexture_4 << endl;}
    }

    if(nomTexture_5 != "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e")
    {
        if (!m_texture[m_nbTexture++].loadFromFile(nomTexture_5)){cout << "Tir.cpp : Impossible de charger : " << nomTexture_5 << endl;}
    }


    m_tir.setTexture(m_texture[0]);
    m_nbTextureActu = 0;

    m_valeurRotation = 0;

    m_tirer = false;
}

Tir::~Tir()
{
    //dtor
}

void Tir::creationTir(Texture texture_Tour, int posTourX, int posTourY, const Vector2f posEnnemi, int vitesse, int zone)
{
    if(!m_tirer)//{throw(string("Tir.cpp : Tir deja tire"));}
    {

        if(posTourX < MIN_LARGEUR){throw(string("Tir.cpp : Position X de la tour < minimum"));}
        if(posTourX > LARGEUR){throw(string("Tir.cpp : Position X de la tour > maximum"));}

        if(posTourY < MIN_HAUTEUR){throw(string("Tir.cpp : Position Y de la tour < minimum"));}
        if(posTourY > HAUTEUR){throw(string("Tir.cpp : Position Y de la tour > maximum"));}

        if(posEnnemi.x < MIN_LARGEUR){throw(string("Tir.cpp : Position X de l'ennemi < minimum"));}
        if(posEnnemi.x > LARGEUR){throw(string("Tir.cpp : Position X de l'ennemi > maximum"));}

        if(posEnnemi.y < MIN_HAUTEUR){throw(string("Tir.cpp : Position Y de l'ennemi < minimum"));}
        if(posEnnemi.y > HAUTEUR){throw(string("Tir.cpp : Position Y de l'ennemi > maximum"));}

        if(vitesse < 1 || vitesse > 3){throw (string("Tir.cpp : Vitesse non correct"));}

        if(zone < 1 || zone > 4){throw (string("Tir.cpp : Vitesse non correct"));}




        m_tir.rotate(-m_valeurRotation);

        switch(vitesse)
        {
        case 1:
            m_vitesse = 0.005;
            m_tempsZone = 0.39;
            break;
        case 2:
            m_vitesse = 0.003;
            m_tempsZone = 0.3;
            break;
        case 3:
            m_vitesse = 0.001;
            m_tempsZone = 0.115;
            break;
        }

        if(zone != 4)
        {
            m_tempsZone *= zone;
        }
        else
        {
            m_tempsZone = 50;
        }


        int posX = posTourX + (texture_Tour.getSize().x / 2);
        int posY = posTourY + (texture_Tour.getSize().y / 2);


        float valX = posEnnemi.x - posX  + (texture_Tour.getSize().x / 2);
        float valY = posEnnemi.y - posY  + (texture_Tour.getSize().y / 2);

        if(valX > valY)
        {
            if(valX > 0)
            {
                valY /= valX;
                valX /= valX;
            }
            else if(valX < 0)
            {
                valY /= -valX;///A verifier
                valX /= -valX;
            }
        }
        else
        {
            if(valY > 0)
            {
                valX /= valY;
                valY /= valY;
            }
            else if(valY < 0)
            {
                valX /= -valY;
                valY /= -valY;
            }
        }

        m_valeurRotation = (pow(valX, 2) + pow(valY, 2));

        if(m_valeurRotation != 0)
        {
            m_valeurRotation = valX / sqrt(m_valeurRotation);

            m_valeurRotation = acos(m_valeurRotation);


            if(valY < 0)
            {
                m_valeurRotation = -((m_valeurRotation * (360 / (2*M_PI))) + 90);
            }
            else
            {
                m_valeurRotation = (m_valeurRotation * (360 / (2*M_PI))) - 90;
            }
            m_tir.rotate(m_valeurRotation);

            m_tirer = true;

            m_tir.setPosition(posX, posY);

            if(valX < -1)
            {
                valY /= -valX;
                valX /= -valX;
            }
            else if (valY < -1)
            {
                valX /= -valY;
                valY /= -valY;
            }
            m_valeurDeplacement_X = valX;
            m_valeurDeplacement_Y = valY;
            m_clock.restart();
            m_clockZone.restart();
            if(m_nbTexture > 1)
            {
                m_clockTexture.restart();
            }
            m_nbTextureActu = 0;
            m_tir.setTexture(m_texture[m_nbTextureActu]);
        }
    }
}



bool Tir::deplacementTir(Texture ennemi, const Vector2f posEnnemi)
{
    bool toucher = false;

    if(m_tirer)
    {
        if(m_clock.getElapsedTime().asSeconds() >= m_vitesse)
        {
            m_tir.move(m_valeurDeplacement_X, m_valeurDeplacement_Y);
            m_clock.restart();

            if(m_nbTexture > 1 && m_clockTexture.getElapsedTime().asSeconds() >= 0.1)
            {
                m_nbTextureActu++;
                if(m_nbTextureActu >= m_nbTexture)
                {
                    m_nbTextureActu = 0;
                }
                m_tir.setTexture(m_texture[m_nbTextureActu]);
                m_clockTexture.restart();
            }

            if(m_tir.getPosition().x > LARGEUR || m_tir.getPosition().x < MIN_LARGEUR || m_tir.getPosition().y < MIN_HAUTEUR || m_tir.getPosition().y > HAUTEUR)
            {
                m_tirer = false;
            }
            toucher = (((posEnnemi.x < (m_tir.getPosition().x + m_texture[m_nbTextureActu].getSize().x)) && ((posEnnemi.x + ennemi.getSize().x) > m_tir.getPosition().x)) &&
                    ((posEnnemi.y < (m_tir.getPosition().y + m_texture[m_nbTextureActu].getSize().y)) && ((posEnnemi.y + ennemi.getSize().y) > m_tir.getPosition().y)));

            if(toucher)
            {
                m_tirer = false;
            }
        }
        if(m_clockZone.getElapsedTime().asSeconds() >= m_tempsZone)
        {
            m_tirer = false;
        }
    }

    return toucher;
}

void Tir::afficheTir(RenderWindow & window ) const
{
    if(m_tirer)
    {
        window.draw(m_tir);
    }
}

void Tir::creerTir(int degat, string nomTexture, string nomTexture_2, string nomTexture_3, string nomTexture_4, string nomTexture_5)
{
    if (!m_texture[0].loadFromFile(nomTexture)){cout << "Tir.cpp : Impossible de charger : " << nomTexture << endl;}
    m_nbTexture = 1;

    if(nomTexture_2 != "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e")
    {
        if (!m_texture[m_nbTexture++].loadFromFile(nomTexture_2)){cout << "Tir.cpp : Impossible de charger : " << nomTexture_2 << endl;}
    }

    if(nomTexture_3 != "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e")
    {
        if (!m_texture[m_nbTexture++].loadFromFile(nomTexture_3)){cout << "Tir.cpp : Impossible de charger : " << nomTexture_3 << endl;}
    }

    if(nomTexture_4 != "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e")
    {
        if (!m_texture[m_nbTexture++].loadFromFile(nomTexture_4)){cout << "Tir.cpp : Impossible de charger : " << nomTexture_4 << endl;}
    }

    if(nomTexture_5 != "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e")
    {
        if (!m_texture[m_nbTexture++].loadFromFile(nomTexture_5)){cout << "Tir.cpp : Impossible de charger : " << nomTexture_5 << endl;}
    }

    m_degatTir = degat;

    m_tir.setTexture(m_texture[0]);
    m_nbTextureActu = 0;

    m_valeurRotation = 0;

    m_tirer = false;
}
