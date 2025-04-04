#pragma once
#include "CoffeeCore.hpp"

class Shake : public GameComponent
{
private:

	float m_shakeTime;
	float m_shakeIntensity;
	sf::Vector2f m_tmpposition;
	sf::Vector2f m_positionSave;

public:
	Shake();
	~Shake();

	void SetActiveShake(bool _bool);

	bool m_activeET;

	void update();
	void draw();
};

