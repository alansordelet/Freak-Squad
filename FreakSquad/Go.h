#pragma once
#include "CoffeeCore.hpp"

class Go : public GameComponent
{
private:
	float m_timerAffichage;
	bool m_affiche;
	int m_repetition;
	sf::Sprite m_spriteGo;
public:
	Go();
	~Go();

	void update();
	void draw();
};

