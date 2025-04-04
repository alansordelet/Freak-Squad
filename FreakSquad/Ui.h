#pragma once
#include "CoffeeCore.hpp"

class Ui : public GameComponent
{
public:
	Ui();
	~Ui();
	void update();
	int getPlayerNumber(); //renvoie le nombre de joueurs 
	void setPlayerNumber(int _m_playerNbr); //d�finit le nombre de joueurs
	int getFirstPlayerType(); //renvoie le personnage jou� par le joueur1
	void setFirstPlayerType(int _m_firstPlayerType); //d�finit le personnage que joueur1 va jouer
	int getSecondPlayerType(); //renvoie le personnage jou� par le joueur2
	void setSecondPlayerType(int _m_secondPlayerType); //d�finit le personnage que joueur2 va jouer
	void draw();
private:
	int m_playerNbr; //int simulant le nombre de joueurs (1 ou 2)
	int m_firstPlayerType; //d�termine quel personnage joueur1 va jouer : 1=Bigboy 2=Bloodlust 3=Kimpah
	int m_secondPlayerType; //d�termine quel personnage joueur2 va jouer
};

