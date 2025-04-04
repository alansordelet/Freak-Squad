#pragma once
#include"CoffeeCore.hpp"

class Starters : public GameComponent {
public:
	Starters();
	~Starters();

	void setSpriteStartersSouteTexture(int index);
	bool getStarterboolperPlayer(std::string _player, std::string _starter);
	bool getStartTutobool();
	bool getSpawnHOLObool();
	void setStartTutobool(bool _newbool);
	void setSpawnHOLObool(bool _newbool);
	void setBforZoneTrigger(bool _newbool);
	void update();
	void draw();
private:
	//Assets
	sf::Sprite m_screenLeft, m_screenRight, m_startGlow, m_endGlow;
	//Starters
	sf::Sprite m_VieSupp, m_UltiSupp, m_DegatSupp, m_ScoreSupp;
	std::vector<sf::Text> m_textsSoute;
	std::vector<sf::Sprite> m_spriteStartersSoute;
	std::vector<sf::Sprite> m_buttonX;
	std::vector<sf::Sprite> m_inputs;
	float m_incrementation;
	bool VieStarterBB, UltiStarterBB, DegatStarterBB, ScoreStarterBB;
	bool VieStarterBL, UltiStarterBL, DegatStarterBL, ScoreStarterBL;
	int m_switchDescription, m_nbHOLO;
	bool m_startTuto, m_spawnHOLO;
	float m_timerTuto;
	float m_timerB;
	bool showB;
	bool showBtimer = false;
};


