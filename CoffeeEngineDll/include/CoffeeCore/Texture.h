#pragma once
#include "Tools.h"

class COFFEECORE_API Texture
{
private:
	sf::Texture m_texture;
public:
	//Constructor
	Texture(const std::string& _pathTexture);
	~Texture();
	//Return const sf::Texture&
	const sf::Texture& getTexture();
};

 