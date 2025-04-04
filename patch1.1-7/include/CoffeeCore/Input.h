#pragma once
#include "GameComponent.h"
#include "gamepadx.hpp"

enum KEYTYPE
{
	PRESSED = 1, RELEASED, HOLD, NEUTRAL
};

typedef std::unordered_map<gp::Gamepad::button, KEYTYPE> typeButton;
typedef struct Trigger { float left; float right; };
typedef gp::Gamepad::gpdirection gpDirection;

class COFFEECORE_API Input : public GameComponent {
public:
	Input();
	~Input();

	void update();
	void draw();
	KEYTYPE getType(gp::Gamepad::button _b);
	void addCombo(gp::Gamepad::button _b);
	sf::Vector2f getStickLeft();
	sf::Vector2f getStickRight();
	Trigger getTrigger();
	bool moveDirection(gpDirection _direction);
	bool pressEscape();
	int getCombo();
	void destructor();
	void resetCombo();
private:
	typeButton button;
	Trigger trigger;
	gpDirection m_direction;
	sf::Vector2f stickLeft, stickRight;
	float timer, timerCombo;
	int combo, m_id;

	static int s_globalId;

	bool goLeft();
	bool goRight();
	bool goDown();
	bool goUp();
};