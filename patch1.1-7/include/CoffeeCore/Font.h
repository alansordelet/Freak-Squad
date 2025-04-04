#pragma once
#include "Tools.h"

class COFFEECORE_API Font
{
private:
	sf::Font m_font;
public:
	Font(std::string _pathFont);
	~Font();

	const sf::Font& getFont();
};

