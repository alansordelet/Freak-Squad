#pragma once
#include "CoffeeCore.hpp"
#include "CoffeeCore/GameComponent.h"

class Menu : public Scene
{
public:
	Menu();
	Menu(std::shared_ptr<Input> _inputP1, std::shared_ptr<Input> _inputP2);
	~Menu();
	void init();
	void update();
	void display();
	void deInit();

protected:
	std::shared_ptr<GameObject> m_object;
	std::shared_ptr<GameObject> m_objectSelection;
	std::shared_ptr<GameObject> m_objectTransition;
	std::shared_ptr<GameObject> m_objectMainMenu;
private:
	SceneManager sceneManager;
	CoffeeWindow window;
	sf::Text s_Story, s_Stats, s_Success, s_Options, s_credit, s_media, s_exit;
	float m_tmpTimer, m_depTimer, timer;
	int m_choixMenu;
	std::shared_ptr<Input> inputP1, inputP2;
};

