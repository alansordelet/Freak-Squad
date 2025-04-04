#pragma once
#include "GameComponent.h"


enum COFFEECORE_API State
{
	STATIC,
	NON_STATIC
};

class COFFEECORE_API ObjectTransform : public GameComponent {
private:
	sf::Vector2f m_position;
	float m_zbuffer;
	State m_state;
public:
	//Constructor
	ObjectTransform();

	//Constructor with default position and state(STATIC by default) has arguments
	ObjectTransform(sf::Vector2f _position, State _state = STATIC);

	//Constructor with default position, zbuffer and state(STATIC by default) has arguments
	ObjectTransform(sf::Vector2f _position, float _zbuffer, State _state = STATIC);

	//Destructor
	~ObjectTransform();

	void update();
	void draw();

	//Get object position
	sf::Vector2f getPosition();

	//Set object new position
	void setPosition(sf::Vector2f _position);

	//Get Z-BUFFER
	float getZBuffer();

	//Set Z-BUFFER
	void setZBuffer(float _zbuffer);

	//Set STATIC to not update Z-BUFFER / Set NON_STATIC to update Z-BUFFER
	void setState(State _state);
};