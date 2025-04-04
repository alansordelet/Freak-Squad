#pragma once
#include "Tools.h"
#include "SceneManager.h"
#include "DebugTools.h"

class COFFEECORE_API MyWindow {
public:
	//Création window/FullScreen
	MyWindow();
	~MyWindow();

	void setUp(std::string _name, sf::Vector2u _size, bool _isFullScreen);
	void toggleFullScreen();
	void launcheFirstScene(Scene* _firstScene);
	//Display
	void beginDraw();
	void endDraw();

	//Accesseur
	bool getIsFullScreen() { return m_isFullscreen; }
	sf::Vector2u getSizeWindow() { return m_windowSize; }
	sf::RenderWindow& getWindow() { return m_window; }
	void gameLoop();
private:
	sf::RenderWindow m_window;
	std::string m_windowTitle;
	sf::Vector2u m_windowSize;
	sf::Vector2f m_windowScale;
	bool m_isFullscreen;
	bool m_isDone;
	sf::Event event;
	SceneManager sceneManager;
	void create();
	void destroy();

#ifdef DEBUG_TOOLS
	DebugTools m_debugTools;
#endif;

};

