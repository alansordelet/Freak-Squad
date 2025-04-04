#pragma once
#include "Sound.h"
#include "Music.h"

typedef std::vector<std::pair<std::string, std::shared_ptr<Sound>>> VectorSound;
typedef std::vector<std::pair<std::string, std::shared_ptr<Music>>> VectorMusic;

class COFFEECORE_API AudioManager
{
private:
	VectorSound vector_GlobalSound;
	VectorSound vector_SceneSound;

	VectorMusic vector_GlobalMusic;
	VectorMusic vector_SceneMusic;

	bool m_isReady;
public:
	//Constructor
	AudioManager();

	//Destructor
	~AudioManager();

	//Load resources needed by the next scene
	void loadSceneResource(std::string _sceneName);

	//Load block of texture
	void loadByBlock(int _begin, int _end, int& _progress, std::vector<std::pair<std::string, std::string>> _vectinfo, int _id);

	//Reset container of scene texture
	void resetSceneSound();

	//Return true if all textures are loaded
	bool isReady();

	//Return global sound buffer with _name. If not found return missing sound buffer
	const sf::SoundBuffer& getGlobalSoundBuffer(const std::string& _name);

	//Return scene sound buffer with _name.  If not found return missing sound buffer
	const sf::SoundBuffer& getSceneSoundBuffer(const std::string& _name);

	//Return global music with _name.  If not found return missing music
	sf::Music& getGlobalMusic(const std::string& _name);

	//Return scene music with _name.  If not found return missing music
	sf::Music& getSceneMusic(const std::string& _name);
};