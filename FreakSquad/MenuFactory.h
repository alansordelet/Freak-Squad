#pragma once
#include"CoffeeCore.hpp"

#define BLOOD_LEFT "BLOOD_LEFT"
#define BLOOD_RIGHT "BLOOD_RIGHT"
#define MAINMENU "MAIN_MENU"

enum e_MENUTYPE_FACTORY
{
	MAIN_MENU_FACTO,
	SELECTION_MENU_FACTO,
	OPTION_MENU_FACTO,
	START_MENU_FACTO
};
class MenuFactory
{
public : 
	MenuFactory();
	~MenuFactory();

	static std::shared_ptr<GameObject> factory(e_MENUTYPE_FACTORY _type);
	static std::shared_ptr<GameObject> createMainMenu();
	static std::shared_ptr<GameObject> createSelectionMenu();
	static std::shared_ptr<GameObject> createSettingsMenu();
	static std::shared_ptr<GameObject> createStartMenu();
};

