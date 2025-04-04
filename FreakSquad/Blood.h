#pragma once
#include "CoffeeCore.hpp"

class Blood : public GameComponent
{
private:

	std::vector<Blood*> BLOOD;
	sf::Sprite m_spriteBlood;
	sf::Vector2f m_positionBlood = { 0.0f, 0.0f };
	sf::Vector2f m_vitesseBlood = { 0.0f, 0.0f };
	sf::Vector2f m_scaleBlood = { 1.0f,1.0f };
	sf::Vector2f m_originBlood = { 177.0f / 2.0f, 56.0f / 2.0f };
	sf::Vector2f m_originBlood2 = { 70.0f / 2.0f, 76.0f / 2.0f };
	sf::Vector2f m_originBlood3 = { 62.0f / 2.0f, 52.0f / 2.0f };
	float m_transBlood = 100.0f;
	float m_TMPtransBlood = 0.0f;
	float m_angleBlood = 0.0f;
	float m_timerPlaquer = 0.0f;
	float m_TMPtimerPlaquer = 0.0f;
	float m_angleDirection = 0.0f;
	int m_direction = 0;

public:

	Blood();
	Blood(sf::Sprite _spriteBlood, sf::Vector2f _positionBlood, int _m_direction);
	~Blood();

	void GoPushBlood(sf::Vector2f _positionBlood,int _direction);

	void update();
	void draw();

};

