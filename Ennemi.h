#ifndef ENNEMIS_H_INCLUDED
#define ENNEMIS_H_INCLUDED

#include "Joueur.h"
#include "carte.h"


bool trouveA_B(int posSouris_X, int posSouris_Y, int &a, int &b);

class Ennemi{
public :
    Ennemi(std::string nomEnnemi, sf::Sprite newSprite, float valVitesse = 150);
    Ennemi();
    ~Ennemi();

    void creerEnnemi(std::string nomEnnemi, sf::Sprite newSprite, int nbPv = 10, float valVitesse = 150, int endroitMonstreX = 0, int endroitMonstreY = 0);
    void setPos(int newPos_X, int newPos_Y);

    bool verifColisionDeplacementEnnemi(Carte mapCarte);
    bool deplacement(sf::Clock & clock, Carte mapCarte, int etape);
    void choixZone(sf::Texture texture, sf::RenderWindow & window, sf::Clock & clock, int posX = 0, int posY = 0);

    int supprimerPV(int degats); ///retourne les pv du monstre aprés le coup
    void afficheEnnemi(sf::RenderWindow & window) const;

    void setVivant(bool Vivant){m_vivant = Vivant;}

    bool getMoving(){return m_moving;}
    std::string getNomEn(){ return _nomEnnemi; }
    float getVitesse(){ return _vitesseDeplaEnnemi; }
    const sf::Vector2f getPosition(){return _sprite.getPosition();}
    int getPVRestant(){return _ptsVieActuel;}
    bool getVivant(){return m_vivant;}
    const sf::Vector2f getVelocity(){return m_velocity;}
    const sf::Vector2f getTarget(){return m_target;}
    void newSprite(sf::Sprite newSprite);

    int getEndroitX()const{return m_endroitMonstreX;}
    int getEndroitY()const{return m_endroitMonstreY;}

    void nouvelEndroit(int endroit_X, int endroit_Y);

    void setNbCase(int newNbCase){m_nbCase = newNbCase;}
    int getNbCase()const {return m_nbCase;}

    void setTabOuAller(int numCase, int XouY, int newVal);
    int getTabOuAller(int numCase, int XouY)const{return m_tabOuAller[numCase][XouY];}

    void setEtape(int newEtape){m_etapeActu = newEtape;}
    int getEtape()const{return m_etapeActu;}
    void increEtape(){m_etapeActu++;}

    void reinitialiserClock(sf::Clock & clock){clock.restart();}

private :
    std::string _nomEnnemi;
    int _ptsVieMax = 10;
    int _ptsVieActuel;
    int _armure = 0;
    sf::Sprite _sprite;
    float _vitesseDeplaEnnemi;

    bool m_moving;
    sf::Vector2f m_target;
    sf::Vector2f m_velocity;
    bool m_vivant = true;
    int m_endroitMonstreX;
    int m_endroitMonstreY;

    int m_tabOuAller[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2];
	int m_nbCase;

	int m_etapeActu;



};



#endif // ENNEMIS_H_INCLUDED
