#pragma once
#include "CoffeeCore.hpp"

class Timer : public GameComponent
{
private:
	float m_timer;
	sf::Text m_textTimer;
public:
	Timer();
	~Timer();

	void update();
	void draw();

	int getTimer();
};

