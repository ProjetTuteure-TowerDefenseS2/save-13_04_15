#include "TextNew.h"

using namespace sf;
using namespace std;

TextNew::TextNew(Font font, int taille, int color_Red, int color_Green, int color_Blue, int posX, int posY)
{
    // choix de la police à utiliser
    m_text.setFont(font); // font est un sf::Font

    // choix de la taille des caractères
    m_text.setCharacterSize(taille); // exprimée en pixels, pas en points !

    // choix de la couleur du texte
    Color tempo(color_Red, color_Green, color_Blue);
    m_couleur = tempo;

    m_text.setColor(m_couleur);

    m_text.setPosition(posX, posY);

    cout << "couleur : " << m_text.getCharacterSize() << endl;



}

void TextNew::afficheText(RenderWindow & window ) const
{
    window.draw(m_text);
}

void TextNew::setText(string texte)
{
    m_text.setString(texte);
}
