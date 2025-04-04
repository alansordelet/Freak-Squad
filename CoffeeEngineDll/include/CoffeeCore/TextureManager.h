#pragma once
#include "Texture.h"

typedef std::vector<std::pair<std::string, std::shared_ptr<Texture>>> VectorTexture;


class COFFEECORE_API TextureManager
{
private:
	VectorTexture vector_GlobalTexture;
	VectorTexture vector_SceneTexture;

	bool m_isReady;
public:
	//Constructor
	TextureManager();

	//Destructor
	~TextureManager();

	//Load resources needed by the next scene
	void loadSceneResources(std::string _sceneName);

	//Load block of texture
	void loadByBlock(int _begin, int _end, int& _progress, std::vector<std::pair<std::string, std::string>> _vectinfo, int _id);

	//Reset container of scene texture
	void resetSceneTexture();

	//Return true if all textures are loaded
	bool isReady();

	//Return global texture with _name. If not found return missing texture
	const sf::Texture& getGlobalTexture(const std::string _name);

	//Return scene texture with _name.  If not found return missing texture
	const sf::Texture& getSceneTexture(const std::string _name);

	//Bind std::shared_ptr<Texture> to texture in container
	std::shared_ptr<Texture> bindSharedToTexture(std::string _name);
};



