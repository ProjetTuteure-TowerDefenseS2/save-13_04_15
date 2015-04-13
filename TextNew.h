#ifndef TEXTNEW_H
#define TEXTNEW_H

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
std::string int_to_string(int nb);

class TextNew
{
    public:
        TextNew(sf::Font font, int taille, int color_Red, int color_Green, int color_Blue, int posX = 0, int posY = 0);

        void setText(std::string texte);
        void afficheText(sf::RenderWindow & window) const;
        sf::Text getText()const {return m_text;}

    private:
        sf::Text m_text;
        sf::Color m_couleur;
};

#endif // TEXTNEW_H
