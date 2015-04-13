#ifndef TOUR_H
#define TOUR_H

#include "Tir.h"
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>


class Tour
{
public:
	Tour();
	void initialiserTour(int zone, int prix, int degat, std::string nomTextureTour, std::string nomTexture, std::string nomTexture_2 = "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e", std::string nomTexture_3 = "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e", std::string nomTexture_4 = "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e", std::string nomTexture_5 = "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e");
	void draw(sf::RenderWindow & window);
	void setPosition(float x, float y);
	void setFillColor();
	void setFillColorBlack();
	float getGlobalBoundsH();
	float getGlobalBoundsW();
	void creationTir(sf::Texture texture_Tour, const sf::Vector2f posEnnemi, int vitesse = 1, int zone = 1) {m_Tir.creationTir(texture_Tour, posX, posY, posEnnemi, vitesse, zone); m_temps.restart();}
    bool deplacementTir(sf::Texture ennemi, const sf::Vector2f posEnnemi){return m_Tir.deplacementTir(ennemi, posEnnemi);}
    void afficheTir(sf::RenderWindow & window) const{m_Tir.afficheTir(window);}

	bool getTirTirer() const {m_Tir.getTirer();}
	float getPosX(){return posX;}
	float getPosY(){return posY;}

	void afficherTour(){m_afficher = true;}
	sf::Clock getClock(){return m_temps;}
	int getDegatTir(){return m_Tir.getDegat();}
	int getPrix(){return m_prix;}
	bool getAfficher(){return m_afficher;}
	int getZone(){return m_zoneDetection;}

	std::string getNom(int num){if(num > -1 && num < 6){return m_nomImage[num];}}

private:
    sf::Texture m_texture;
	sf::Sprite tour1;
	float posX;
	float posY;
	bool m_afficher;
	Tir m_Tir;
	sf::Clock m_temps;
    int m_prix;
    std::string m_nomImage[6];
    int m_zoneDetection;
};

#endif

