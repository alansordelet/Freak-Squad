#pragma once
#include "GameComponent.h"

class COFFEECORE_API Rectangle : public GameComponent {
private:
	sf::RectangleShape m_rectangle;
public:
	Rectangle(float _x, float _y);
	~Rectangle();

	void update();
	void draw();
	
	sf::RectangleShape& getRectangle();
};