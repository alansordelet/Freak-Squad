#pragma once
#include "CoffeeCore.hpp"
#include "Physique.h"
enum Personnage
{
	UI_BIGBOY,
	UI_BLOODLUST,
	UI_KIMPAH
};


class Lifebar : public GameComponent
{
private:

	sf::Sprite s_cadrePlayer, s_personnageProfil, s_nomPersonnage, s_cadreLife, s_lifeBar, s_fondCadre, s_possibleLife, s_lifeBarGRIS, s_vieBonus;

	sf::Sprite s_cadreUlti, s_barreUlti, s_barreUltiGris;

	static int m_playerNbr;

	sf::Text m_textScore;

	Personnage personnage;
	std::weak_ptr<Physique> wp_physique;
	sf::Vector2f m_pos;
	float m_scale = 0.8;

	float m_timer;
	int m_life, m_ulti;
	float  m_fullLifeBar;
	void ColorLife();
	void ScaleLife();
	bool b_vieBonus;
	float m_fullUlti;
	bool b_showProfiPicture;
public:

	Lifebar(Personnage _personnage);
	~Lifebar();

	void setShowProfilePicture(bool _b_bool);

	int getPlayerNbr();

	void setPersonnageType(Personnage _personnage);

	sf::Vector2f getPos();

	//Init the pos of all Sprite
	void initAllSpritePos();

	void LinkPlayerToUI(std::shared_ptr<Physique> _physique);

	void setBonusLife(bool _vieBonus);

	void update();
	void draw();

};

enum UI_COLIS
{
	BLEU_UI,
	JAUNE_UI,
	ROUGE_UI,
	VERT_UI
};

class Score : public GameComponent
{
private:
	int m_nbrScoreThousands,m_nbrScoreHundreds;
	sf::Text m_textScoreThousands, m_texteScoreHundreds;
	sf::Text m_ComboHit;
	sf::Sprite m_spriteRoulette;
	static int nbrPlayer;
	sf::Vector2f m_pos, m_posCombo;
	int m_nbrCombo, m_nbrHit,m_maxCombo;
	int totalScore, m_roulette;
	int tmpTour;
	static float timer;

	float timerColor, timerRoulette,timerFiniRoulette;

	bool b_Comboing, b_rouletteActive, b_finalLargage,b_colisDrop;

	UI_COLIS m_ui_colis;

	std::shared_ptr<GameObject> colis;
public: 
	Score();
	~Score();
	
	int getTotalScore();

	void initAllPos();

	int getMaxCombo();

	int getScoreTotal();

	void setTextWhite();

	bool getFinitoRoulette();
	void setFinitoRoulette(bool _colisDrop);
	int getNbrPlayer();

	void scoreAdd(int _scoreThousands, int _scoreHundreds);

	void checkScoreLargage();

	void justAddScore(int _scoreThousands, int _scoreHundreds);

	void setRouletteActif(bool m_bool);

	void update();
	void draw();

	void setTypeColisUI(std::shared_ptr<GameObject> _go);

};