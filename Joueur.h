#ifndef JOUEUR
#define JOUEUR

class Joueur
{
public:
	Joueur(void);
	int getOr(){return m_or;};
	int getPV(){return m_pv;};
	void retirerOr(int);
	void ajouterOr(int);
	std::string changerAffichageOr();
private:
	int m_or;
	int m_pv;
};

#endif
