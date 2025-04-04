#pragma once
#include "CoffeeCore.hpp"

enum e_SETTING_SELECTED
{
	SETTINGS_SELECTED,
	INPUT_SELECTED,
	BACK_SELECTED,

	MUSIC_SELECTED,
	SOUND_SELECTED,
	FULLSCREEN_SELECTED
};
enum e_MENU_SETTINGS
{
	OPTION_MENU,
	INPUT_MENU,
	SETTINGS_MENU
};

class MenuSettings : public GameComponent
{
private:

	//0.33,0 de l'écran
	const sf::Vector2f posBand{ 0.5,0 };

	//Options menu
	//0.5 de l'écran - texture size/2
	const sf::Vector2f posTextSettingsTitle{ 0.5,0.09 };
	const sf::Vector2f posTextSettings{ 0.5,0.33 };
	const sf::Vector2f posTextInput{ 0.5,0.45 };
	const sf::Vector2f posTextBack{ 0.5,0.75 };

	const std::string stringSettings = "Settings";
	const std::string stringInput = "Input";
	const std::string stringBack = "Back";

	//taille des character
	const float characterSize = 60.f;
	const float characterBoldSize = 70.f;

	//settings menu

	const sf::Vector2f posLogoMusic{ 0.4f, 0.34f }; // 780,450
	const sf::Vector2f posBarMusic{ 0.46f, posLogoMusic.y + 0.03f }; // 900,480
	const sf::Vector2f posCursorMusicMin{ 0.46f, posBarMusic.y - 0.02f }; // 900,480
	const sf::Vector2f posCursorMusicMax{ 0.57f, posBarMusic.y - 0.025f }; // 1152-47,480

	const sf::Vector2f posLogoSound{ 0.4f, posLogoMusic.y + 0.15f }; // 780,280
	const sf::Vector2f posBarSound{ 0.46f, posLogoSound.y + 0.025f }; // 900,320
	const sf::Vector2f posCursorSoundMin{ 0.46f, posBarSound.y - 0.035f }; // 900,480
	const sf::Vector2f posCursorSoundMax{ 0.58f, posBarSound.y - 0.035f }; // 1152-33,480

	const sf::Vector2f posFullScreen{ 0.5f, posLogoSound.y + 0.16f };
	const sf::Vector2f posBackButton{ 0.6f, 0.87f }; // 525,950
	const std::string stringMusic = "Music";

	//input menu 
	const sf::Vector2f posCenter{ 0.5f,0.5f };



	//permet de savoir ce qui est selectionne
	e_SETTING_SELECTED m_selected;

	//permet de savoir dans quel menu d'option on se trouve
	e_MENU_SETTINGS m_stateMenu;

	//à remplacer par les variable d'alan
	float m_volumeSound;
	float m_volumeMusic;

	void updateOptionsMenu();
	void updateSettingsMenu();
	void updateSettingsMenuController();
	void updateSettingsMenuKeyboard();
	void changeMenu();

	//les draw
	void drawBand();

	void drawTextOptionMenu();

	void drawSettingsMenu();
	void drawInputMenu();
	void drawBarSound();
	void drawBarMusic();
	void drawFullscreenLogo();
	void drawBackButton();

	void drawBackGround();

	float m_keyTimer;

public:

	MenuSettings();
	~MenuSettings();

	void update();
	void draw();



};

