#pragma once
#include "TextureManager.h"
#include "AudioManager.h"
#include "FontManager.h"
#include "MovieManager.h"

class COFFEECORE_API RessourceManager
{
private:
	static RessourceManager* p_instance;
	bool m_isReady;
	TextureManager textureManager;
	AudioManager audioManager;
	FontManager fontManager;
	MovieManager movieManager;
public:
	RessourceManager();
	~RessourceManager();

	RessourceManager(RessourceManager& other) = delete;

	void operator=(const RessourceManager&) = delete;

	//Return RessourceManager's instance
	static RessourceManager* get();

	//First load global resources
	void firstLoadSceneResources(std::string _pathRessource);

	//Transition between 2 scene (implied the removal of useless resources)
	void LoadSceneResources(std::string _pathRessource);

	//Get global texture loaded during program initialization by his name ("textureName.png")
	const sf::Texture& getGlobalTexture(const std::string& _textureName);

	//Get scene's texture by his name ("textureName.png")
	const sf::Texture& getSceneTexture(const std::string& _textureName);

	//Bind std::shared_ptr<Texture> to texture 
	std::weak_ptr<Texture> bindSharedToTexture(std::string _name);

	//Get global sound loaded during program initialization by his name ("soundBufferName.ogg/wav")
	const sf::SoundBuffer& getGlobalSoundBuffer(const std::string& _soundName);

	//Get scene's sound by his name ("soundName.ogg")
	const sf::SoundBuffer& getSceneSoundBuffer(const std::string& _soundName);

	//Get global sound loaded during program initialization by his name ("soundBufferName.ogg/wav")
	sf::Music& getGlobalMusic(const std::string& _musicName);

	//Get scene's music by his name ("musicName.ogg")
	sf::Music& getSceneMusic(const std::string& _musicName);

	//Get scene's font by his name ("fontName.ttf" or "fontName.otf")
	const sf::Font& getFont(const std::string& _fontName);

	//Clear the container of scene's resources
	void ResetSceneResources();

	//Return if the loading scene's resources is ready
	bool IsReady();

	MovieManager& getMovie();
};
