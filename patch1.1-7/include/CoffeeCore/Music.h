#pragma once
#include "Tools.h"

class COFFEECORE_API Music
{
private:
	sf::Music m_music;
public:
	//Constructor
	Music(const std::string& _pathMusic);

	//Destructor
	~Music();

	//Return Music
	sf::Music& getMusic();
};