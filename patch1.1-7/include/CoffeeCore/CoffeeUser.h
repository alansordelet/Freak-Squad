#pragma once
#include "Tools.h"
#include "WindowManager.h"

class COFFEECORE_API CoffeeWindow {
public:
	CoffeeWindow();
	~CoffeeWindow();
	void createWindow(std::string _name, sf::Vector2u _size, bool _isFullScreen);
	void runGameLoop();
	void toggleFullScreen();
	sf::RenderWindow& getWindow();
	bool isFullScreen();
	sf::Vector2u getSize();
	void draw(const sf::Drawable& _drawable);
	void setFirstScene(Scene* _firstScene);
};
