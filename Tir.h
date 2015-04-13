#ifndef TIR_H
#define TIR_H



#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>



const int HAUTEUR = 800;
const int LARGEUR = 1300;

const int MIN_HAUTEUR = 0;
const int MIN_LARGEUR = 0;
class Tir
{
    public:
        Tir();
        Tir(std::string nomTexture, std::string nomTexture_2 = "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e", std::string nomTexture_3 = "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e", std::string nomTexture_4 = "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e", std::string nomTexture_5 = "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e");

        void creerTir(int degat, std::string nomTexture, std::string nomTexture_2 = "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e", std::string nomTexture_3 = "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e", std::string nomTexture_4 = "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e", std::string nomTexture_5 = "2f41e151z4d/*é-&4564548ké&à\"kgjjsked74q1a1a4487zzz!%£¤e");
        virtual ~Tir();
        //void creationTir(Texture texture_Tour, const Vector2f posTour, const Vector2f posEnnemi, int vitesse = 1, int zone = 1) throw(string);
        void creationTir(sf::Texture texture_Tour, int posTourX, int posTourY, const sf::Vector2f posEnnemi, int vitesse = 1, int zone = 1);
        bool deplacementTir(sf::Texture ennemi, const sf::Vector2f posEnnemi);
        void afficheTir(sf::RenderWindow & window) const;
        sf::Sprite getSprite() const {return m_tir;}
        bool getTirer() const {return m_tirer;}
        int getDegat(){return m_degatTir;}

    private:

        sf::Texture m_texture[5];
        sf::Sprite m_tir;

        sf::Vector2i m_pos;

        float m_vitesse;
        float m_tempsZone;
        float m_valeurDeplacement_X;
        float m_valeurDeplacement_Y;
        float m_valeurRotation;
        bool m_tirer;
        int m_nbTexture;
        int m_nbTextureActu;
        sf::Clock m_clock;
        sf::Clock m_clockTexture;
        sf::Clock m_clockZone;

        int m_degatTir;
};

#endif // TIR_H
