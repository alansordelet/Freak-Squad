#pragma once
#include "CoffeeCore.hpp"

enum e_SETTING_SELECTED2
{
	SETTINGS_SELECTED,
	INPUT_SELECTED,
	BACK_SELECTED,

	MUSIC_SELECTED,
	SOUND_SELECTED,
	FULLSCREEN_SELECTED
};

class PauseGameCOMP : public GameComponent
{
private:

	//TEXTURE
	sf::Sprite m_spriteFond;
	sf::Sprite m_spritePage_Option;

	//TEXTE
	sf::Text m_textBackGame;
	sf::FloatRect m_textRectBackGame;

	sf::Text m_textOption;
	sf::FloatRect m_textRectOption;

	sf::Text m_textCommande;
	sf::FloatRect m_textRectCommande;

	sf::Text m_textQuitter;
	sf::FloatRect m_textRectQuitter;

	//OPTION
	sf::Sprite m_spriteMusique;
	sf::Sprite m_spriteBarMusique;
	sf::Sprite m_spriteEye;
	sf::Vector2f m_posEye;
	sf::Sprite m_spriteSFX;
	sf::Sprite m_spriteBarSFX;
	sf::Sprite m_spriteOreil;
	sf::Vector2f m_posOreil;
	sf::Sprite m_spriteFullScreenOFF;
	sf::Sprite m_spriteFullScreenON;
	bool m_ScreenOFF_ON = false;
	bool m_isDraggingMusic = false;
	bool m_isDraggingSFX = false;

	float volumeMusic;
	float volumeSFX;

	//COMMANDE
	sf::Sprite m_spriteCommade;


	bool m_menu_pause;
	bool m_option;
	bool m_commande;

	float timerKey = 0.0f;

	std::weak_ptr<Input> sp_input;
public:


	PauseGameCOMP(std::shared_ptr<GameObject> _m_object);
	~PauseGameCOMP();

	void update();
	void update2();
	void draw();

	void updateSettingsMenuController();
	void drawFullscreenLogo();
	void drawBarMusic();
	void drawBarSound();
	void drawBackButton();
	void setControlePause(std::shared_ptr<Input> _input);

	e_SETTING_SELECTED2 m_selected;

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

	const std::string stringBack = "Back";

	int m_NavigationMenu;
	bool m_activeGame;
	float m_volumeSound;
	float m_volumeMusic;
	float m_keyTimer;
};