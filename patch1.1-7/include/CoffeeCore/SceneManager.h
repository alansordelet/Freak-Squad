#pragma once
#include "RessourceManager.h"

class SceneManager;
class COFFEECORE_API Scene {
protected:
	bool m_isLoading;
	bool m_isReady;
	bool m_firstPass;
	std::thread thread;
	SceneManager* p_SceneManager;
public:
	sf::Texture m_textureTransition;
	sf::IntRect m_rectTransition;
	float m_timerTransition;
	sf::Sprite m_spriteTransition;

	Scene();
	~Scene();
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void display() = 0;
	virtual void deInit() = 0;
	void set_stateManager(SceneManager* _SceneManager);
	void joinThread();
	//Accesseur
	bool getIsLoading();
	bool getIsReady();
	bool getFirstPass();

	void launchThread();
	const sf::Texture& getTexture(std::string _texture);
};

class COFFEECORE_API SceneManager {
protected:
	Scene* scene;
	std::thread threadRessource;
	bool threadRessourceIsJoin;
public:
	SceneManager();
	~SceneManager() {};

	void setFirstScene(Scene* _firstScene);
	void transitionTo(Scene* _newScene);
	void update();
	void display();
	void launchThreadRessource(std::string _newScene);
	void joinThreadRessource();
};