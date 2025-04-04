#pragma once
#include "CoffeeCore.hpp"

enum FONDU
{
	NOIR, TRANS
};

enum FONDU2
{
	NOIR2, TRANS2
};

class Transition : public GameComponent
{
private:
	//fondu noir ///////////////////////////
	sf::RectangleShape m_recFondu;
	float m_opacity;
	float m_timerFondu;
	bool m_makeFondu;
	float m_timerTransition;
	float m_timerFonduLerp;
	bool m_mooveCam;
	bool m_transitionCam;
	bool m_bFonduLerp;
	bool m_isDoingTp;
	int m_type;
	///////////////////////////////////////

	bool m_doTransitToMenu;

	//fondu fin de niveau////////////////
	bool m_activeFinLevel;
	bool m_activeDechirureLevel;
	sf::Sprite m_spriteBandeDebut;
	sf::Sprite m_spriteBandeFin;
	sf::IntRect m_intrectBande;
	float m_timerBande;
	int m_frameXBande;
	float m_timerActiveFondu;
	bool m_activeNewAnime;

	bool m_makeFondu2;
	float m_timerFondu2;
	float m_timerFonduLerp2;
	bool m_bFonduLerp2;
	bool m_isDoingTp2;
	sf::RectangleShape m_recFonduScore;
	float m_opacityScore;
	int m_type2;
	bool m_activeFinScore;
	sf::Sprite m_spriteFondScore;
	sf::Vector2f m_positionFondScore;
	sf::Vector2f m_NEWpositionFondScore;
	sf::Sprite m_spriteBandeScore;
	sf::Vector2f m_positionBandeScore;
	sf::Vector2f m_NEWpositionBandeScore;
	float m_timerPositionScore;
	float m_timerPositionFondScore;

	//text score
	sf::Text textScore;
	sf::Text textTemps;
	sf::Text textComboMax;
	sf::Text textScoreTotal;
	sf::Text textNBScore;
	sf::Text textNBTemps;
	sf::Text textNBComboMax;
	sf::Text textNBScoreTotal;
	int m_Score;
	int m_ScoreCombo;
	int m_ScoreTemps;
	int m_ScoreTotal;
	sf::Sprite m_spriteBoutonA;
	float m_opacityBoutonA;
	sf::Text m_textSkip;
	float m_opacitySkip;
	sf::Sprite m_spriteBoutonA2;
	float m_opacityBoutonA2;


	//Ecran mort
	sf::Sprite m_spriteFondDegrader;
	sf::Sprite m_spriteFondCrane;
	float m_opacityDegrader_Crane;
	sf::RectangleShape m_recFondGris;
	float m_opacityGris;
	sf::Sprite m_spriteGameOver;
	float m_opacityGameOver;
	float m_timerFonduMenu;
	sf::RectangleShape m_recFonduGameOver;

	bool m_makeFonduMORT;
	float m_timerFonduMORT;
	float m_timerFonduLerpMORT;
	bool m_bFonduLerpMORT;
	bool m_isDoingpMORT;
	bool m_lanceEnding;

	//Credit
	sf::Sprite m_spriteCredit;
	sf::Sprite m_spriteCredit2;
	float m_posYCredit;
	bool m_activeCredit;
	bool m_activeTMP;
	float m_timertemp;
	int m_NBTemps;
	bool m_afficeScore;
	bool m_activateEnd;


	std::weak_ptr<Input> wp_input;

public:
	Transition();
	~Transition();

	void update();
	void draw();

	void DoFondu(FONDU _choix);
	void DoFonduScore(FONDU2 _choix);
	void DoFonduMORT();
	void DisplayFonduSwap();
	void DisplayFonduScore();
	void DisplayFonduMORT();
	float testelerp(float start, float end, float t);
	bool getTransitToMenu();
	void setBoolFinNiveau(bool _bool);
	bool getBoolFinNiveau();
	bool getStartEnding();
	bool getEnd();
	void setStartCredit(bool _start);
	void resetStartEnding();
	bool getRetourMenu();
	int getScore();
	int getTimer();
	int getCombo();
	void setScore(int _score);
	void setTimer(int _timer);
	void setCombo(int _Combo);
	void setPosition(float _posY);
	void setTransitionMenu(bool _bool);
	bool m_activeBackMenu;
	void calculScore();
};

