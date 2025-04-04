#pragma once
#include "Font.h"


typedef std::vector<std::pair<std::string, std::shared_ptr<Font>>> VectorFont;

class COFFEECORE_API FontManager
{
private:
	VectorFont vectorFont;
public:
	FontManager();
	~FontManager();

	const sf::Font& getFont(const std::string& _nameFont);
};

