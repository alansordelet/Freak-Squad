#pragma once
#include "Tools.h"

class COFFEECORE_API Sound
{
private:
	sf::SoundBuffer m_soundBuffer;
public:
	//Default Constructor
	Sound() = default;

	//Constructor
	Sound(const std::string& _pathSound);

	//Destructor
	~Sound();

	//Return SoundBuffer
	const sf::SoundBuffer& getSoundBuffer();
};