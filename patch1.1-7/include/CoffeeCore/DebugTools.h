#pragma once
#include "Tools.h"
#include <Windows.h>
#include <psapi.h>

class COFFEECORE_API DebugTools
{
public:
	DebugTools();
	~DebugTools();

	void initDebugTools(sf::RenderWindow& _window);

	void updateDebugTools();

	void drawDebugTools(sf::RenderWindow& _window);

	///////
	//FPS//
	///////

	// INIT LA FONT POS TAILLE COULEUR DES FPS
	void initFPS(sf::RenderWindow& _window);

	// RESET LA VALEUR DANS LE STRING
	void updateFPS();

	// AFFICHE LES FPS
	void drawFPS(sf::RenderWindow& _window);

	// Return Les FPS
	float getFPS();

	///////////
	//MÉMOIRE//
	///////////

	//PC RAM//

	void initRamMem(sf::RenderWindow& _window);

	void updateRamMem();

	void drawRamMem(sf::RenderWindow& _window);

	int PercentageOfMemUsed();

	void initCurrentRamMem(sf::RenderWindow& _window);

	void updateCurrentRamMem();

	void drawCurrentRamMem(sf::RenderWindow& _window);

	int percentageOfCurrentMem();



private:

	bool m_showDebug;

	sf::Font font;

	sf::Text m_enableDebug;
	///////
	//FPS//
	///////

	float fps;
	float timer;
	sf::Text fpsTexte;
	sf::Clock clock;

	sf::Time previousTime;
	sf::Time currentTime;

	///////////
	//MEMOIRE//
	///////////

	DWORDLONG totalPhysMem;
	DWORDLONG physMemUsed;
	MEMORYSTATUSEX memInfo;
	sf::Text ramTexte;

	int percentage_ofMemUsed;
	std::string ramString;

	//CURRENT USED BY ME//
	SIZE_T physMemUsedByMe;
	sf::Text currentRamText;
	PROCESS_MEMORY_COUNTERS_EX pmc;
	std::string s_currentRamText;
	int percentageOfMemUsedByMe;

};