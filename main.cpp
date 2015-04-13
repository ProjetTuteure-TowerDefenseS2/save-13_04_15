#include "constante.h"

using namespace sf;
using namespace std;


int main()
{
	RenderWindow window(VideoMode(1200, 704), "Tower Defense !", Style::Titlebar | Style::Close);
	cout <<"bienvenue dans notre projet de Tower Defense !";
    const Vector2f pos(279,258);

    Texture textureAcceuil;

    textureAcceuil.loadFromFile("./img/textureMenu.jpg");

    Sprite sprite;
	sprite.setTexture(textureAcceuil);
	sprite.setPosition(0,0);

    bool enJeu = false;

    Event event;



    Texture textureTile;
	textureTile.loadFromFile("./maps/herbe.png");
	Sprite mySprite;
	mySprite.setTexture(textureTile);

	Sprite tile[NB_TILE];

    int cpt = 0;
    int valHauteur = 0;
    while(cpt < NB_TILE)
    {
        for (int i = 0 ; i < DECOUPAGE_LARGEUR ; i++)
        {
            mySprite.setTextureRect(IntRect(LARGEUR_TILE * i, HAUTEUR_TILE * valHauteur, LARGEUR_TILE, HAUTEUR_TILE));
            mySprite.setPosition(LARGEUR_TILE * i, HAUTEUR_TILE * valHauteur);
            tile[cpt] = mySprite;
            cpt++;
        }
        valHauteur++;
    }

    Carte mapNum1(getStringFromEnum(MAP_1), 0, 0);
    //mapNum1.ReinitialiserCarte();

    Carte mapNum2(getStringFromEnum(MAP_2), 0, 0);
    //mapNum2.ReinitialiserCarte();

    Carte tabMap[NB_VIEW_MAP];

    vector <View> tabView;

    tabMap[0].setNom(getStringFromEnum(MAP_1));
    tabMap[1].setNom(getStringFromEnum(MAP_2));
    tabMap[2].setNom(getStringFromEnum(MAP_3));
    tabMap[3].setNom(getStringFromEnum(MAP_1));
    tabMap[4].setNom(getStringFromEnum(MAP_1));
    tabMap[5].setNom(getStringFromEnum(MAP_HERBE));

    for(int i = 0 ; i < NB_VIEW_MAP ; i++)
    {
        tabMap[i].ReinitialiserCarte();
        tabView.push_back(window.getDefaultView());
    }

    tabView[0].setViewport(sf::FloatRect(0.054f, 0.08, 0.3275f, 0.3f));
    tabView[1].setViewport(sf::FloatRect(0.329f, 0.08, 0.3275f, 0.3f));
    tabView[2].setViewport(sf::FloatRect(0.604f, 0.08, 0.3275f, 0.3f));
    tabView[3].setViewport(sf::FloatRect(0.054f, 0.5, 0.3275f, 0.3f));
    tabView[4].setViewport(sf::FloatRect(0.329f, 0.5, 0.3275f, 0.3f));
    tabView[5].setViewport(sf::FloatRect(0.604f, 0.5, 0.3275f, 0.3f));

    Font font;
    if (!font.loadFromFile("./font/Calligraphic.TTF"))
    {
        // erreur...
    }

    Text text;

    text.setFont(font); // font est un sf::Font
    text.setCharacterSize(40); // exprimée en pixels, pas en points !
    text.setColor(Color::White);
    text.setPosition(130, 270);
    text.setString("Map 1");

    Text textTitre;

    textTitre.setFont(font); // font est un sf::Font
    textTitre.setCharacterSize(80); // exprimée en pixels, pas en points !
    textTitre.setColor(Color::Red);
    textTitre.setPosition(50, 300);
    textTitre.setString("TOWER DEFENSE");

    bool affichageDeb = true;

    while (window.isOpen() && affichageDeb)
	{
        while (window.pollEvent(event))
		{
		    if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)//MouseButtonReleased pour relacher
            {
                if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Return)
                {
                    affichageDeb = false;
                }
            }
		}

		window.clear(Color(127,127,127));

        window.draw(textTitre);

        window.display();
	}


    while (window.isOpen() && !enJeu)
	{
        while (window.pollEvent(event))
		{
		    if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)//MouseButtonReleased pour relacher
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    window.setView(window.getDefaultView());
                    try{
                        if(event.mouseButton.x > 64 && event.mouseButton.x < 329 && event.mouseButton.y > 54 && event.mouseButton.y < 222)
                        {
                            enJeu = jeu(window, getStringFromEnum(MAP_1), font, tile);
                        }
                        else if(event.mouseButton.x > 393 && event.mouseButton.x < 658 && event.mouseButton.y > 54 && event.mouseButton.y < 222)
                        {
                            enJeu = jeu(window, getStringFromEnum(MAP_2), font, tile);
                        }
                        else if(event.mouseButton.x > 722 && event.mouseButton.x < 987 && event.mouseButton.y > 54 && event.mouseButton.y < 222)
                        {
                            enJeu = jeu(window, getStringFromEnum(MAP_3), font, tile);
                        }
                    }
                    catch(string msg)
                    {
                        cout << endl << endl << msg << endl;
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {

                }
            }
		}

		window.setView(window.getDefaultView());

        //window.clear(Color(127,127,127));

        window.draw(sprite);

        window.draw(text);

        for(int i = 0 ; i < NB_VIEW_MAP ; i++)
        {
            afficherViewMap(window, tabView, i, tabMap, tile);
            afficherViewMapNiveau2(window, tabView, i, tabMap, tile);
            afficherViewMapNiveau3(window, tabView, i, tabMap, tile);
        }

        window.display();
        // réactivation de la vue par défaut
	}

    return 0;
}
