#pragma once
#include "CoffeeCore.hpp"

class Score;
class FeedBackScore : public GameComponent
{
private:

	int m_score = 0;
	float m_keytimer = 0.0f;
public:
	sf::Text m_text, m_txHit;
	std::string s_stHit1;
	sf::Vector2f m_scaleEG = { 1.0f,1.0f };
	sf::Vector2f m_newscaleEG = { 1.0f,1.0f };
	bool m_activeEG = false;
	float m_timerEG = 0.0f;
	float m_timerStop = 0.0f;
	bool m_stoprotation = false;
	float m_rotationEG = 0.0f;
	FeedBackScore();
	~FeedBackScore();

	sf::Vector2f VsmoothstepPingPongLerp(sf::Vector2f start, sf::Vector2f end, float t);
	void update();
	void draw();

};

