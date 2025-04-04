#pragma once
#include "GameComponent.h"


enum COFFEECORE_API DirectionX {
	RIGHT, LEFT
};
enum COFFEECORE_API DirectionY {
	UP, DOWN
};

typedef std::pair<DirectionX, DirectionY> Direction;

class COFFEECORE_API RigidBody : public GameComponent {
private:
	sf::Vector2f m_speed;
	float m_mass;
	Direction m_direction;
public:
	RigidBody();
	~RigidBody();

	void update();
	void draw();

	Direction getDirection();
	sf::Vector2f getSpeed();
	float getMass();
	void setSpeed(sf::Vector2f _speed);
	void resetSpeed();
};

