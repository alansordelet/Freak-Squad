#pragma once
#include "GameComponent.h"

class COFFEECORE_API Sprite : public GameComponent {
private:
	sf::Sprite sprite;
public:
	Sprite();
	Sprite(std::string _nameTexture);
	~Sprite();

	void update();
	void draw();
	
	void setTexture(const sf::Texture& _t);
	sf::Sprite& getSprite();
};
