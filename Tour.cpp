#include "Tour.h"

using namespace sf;
using namespace std;

Tour::Tour()
{
    float posX;
    float posY;

    m_afficher = false;


    //m_texture.loadFromFile("./img/tour.png");
    //tour1.setTexture(m_texture);
    //tour1.setPosition(0,0);
}

void Tour::initialiserTour(int zone, int prix, int degat, string nomTextureTour, string nomTexture, string nomTexture_2, string nomTexture_3, string nomTexture_4, string nomTexture_5)
{
    m_texture.loadFromFile(nomTextureTour);
    tour1.setTexture(m_texture);

    m_Tir.creerTir(degat, nomTexture, nomTexture_2, nomTexture_3, nomTexture_4, nomTexture_5);
    m_prix = prix;
    m_zoneDetection = zone;
    m_temps.restart();
    m_afficher = true;
    m_nomImage[0] = nomTextureTour;
    m_nomImage[1] = nomTexture;
    m_nomImage[2] = nomTexture_2;
    m_nomImage[3] = nomTexture_3;
    m_nomImage[4] = nomTexture_4;
    m_nomImage[5] = nomTexture_5;
}

void Tour::setPosition(float x, float y)
{
    posX = x;
    posY = y;

    tour1.setPosition(posX,posY);
}

void Tour::draw(RenderWindow & window)
{
    window.draw(tour1);
}

float Tour::getGlobalBoundsW()
{
    return tour1.getGlobalBounds().width+posX;
}

float Tour::getGlobalBoundsH()
{
    return tour1.getGlobalBounds().height+posY;
}
