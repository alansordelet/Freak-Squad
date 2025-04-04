#pragma once
#include "CoffeeCore.hpp"
#include "CoffeeCore/GameComponent.h"

class Selection : public GameComponent
{
public:
	Selection();
	~Selection();
	void update();
	void draw();
	void animFirstPlayer();
	void animSecondPlayer();
	std::shared_ptr<Input> getInputJ1();
	std::shared_ptr<Input> getInputJ2();

	void setInputJ1(std::shared_ptr<Input> _input);
	void setInputJ2(std::shared_ptr<Input> _input);

	bool getTransitToGame();
private:

	std::shared_ptr<Input> inputJ1, inputJ2;

	sf::Sprite m_backgroundSprite;
	sf::Sprite m_background2Sprite;

	sf::Sprite m_banderoleSprite;
	sf::Sprite m_firstPlayerBackgroundSprite;
	sf::Sprite m_secondPlayerBackgroundSprite;
	sf::Sprite m_bigboyIconSprite;
	sf::Sprite m_bloodlustIconSprite;
	sf::Sprite m_kimpahIconSprite;

	sf::Sprite m_firstPlayerCadreSprite;
	sf::Sprite m_secondPlayerCadreSprite;

	sf::Sprite m_firstBigboyHoloSprite;
	sf::Sprite m_firstBigboyIdleSprite;

	sf::Sprite m_secondBigboyHoloSprite;
	sf::Sprite m_secondBigboyIdleSprite;

	sf::Sprite m_firstBloodlustHoloSprite;
	sf::Sprite m_firstBloodlustIdleSprite;

	sf::Sprite m_secondBloodlustHoloSprite;
	sf::Sprite m_secondBloodlustIdleSprite;

	sf::Sprite m_firstKimpahHoloSprite;
	sf::Sprite m_firstKimpahIdleSprite;

	sf::Sprite m_secondKimpahHoloSprite;
	sf::Sprite m_secondKimpahIdleSprite;

	sf::Sprite m_AIcon;
	sf::Sprite m_BIcon;

	//Banner things
	sf::Sprite m_firstPlayerBanner;
	sf::Sprite m_secondPlayerBanner;
	sf::Sprite m_J1Sprite; //inutilisé
	sf::Sprite m_J2Sprite; //inutilisé

	sf::Vector2f m_firstPlayerBannerPosition;
	sf::Vector2f m_secondPlayerBannerPosition;

	sf::Vector2f m_J1Position;
	sf::Vector2f m_J2Position;

	//Positions
	sf::Vector2f m_backgroundPos;
	sf::Vector2f m_banderolePos;
	sf::Vector2f m_firstPlayerBackgroundPos;
	sf::Vector2f m_secondPlayerBackgroundPos;
	sf::Vector2f m_bigboyIconPos;
	sf::Vector2f m_bloodlustIconPos;
	sf::Vector2f m_kimpahIconPos;

	sf::Vector2f m_firstPlayerCadrePos;
	sf::Vector2f m_secondPlayerCadrePos;

	sf::Vector2f m_firstBigboyHoloPos;
	sf::Vector2f m_firstBigboyIdlePos;
	sf::Vector2f m_secondBigboyHoloPos;
	sf::Vector2f m_secondBigboyIdlePos;

	sf::Vector2f m_firstBloodlustHoloPos;
	sf::Vector2f m_firstBloodlustIdlePos;
	sf::Vector2f m_secondBloodlustHoloPos;
	sf::Vector2f m_secondBloodlustIdlePos;

	sf::Vector2f m_firstKimpahHoloPos;
	sf::Vector2f m_firstKimpahIdlePos;
	sf::Vector2f m_secondKimpahHoloPos;
	sf::Vector2f m_secondKimpahIdlePos;

	sf::Vector2f m_APosition;
	sf::Vector2f m_BPosition;

	sf::IntRect m_bigboyIdleRect;
	sf::IntRect m_secondBigboyIdleRect;
	sf::IntRect m_bloodlustIdleRect;
	sf::IntRect m_secondBloodlustIdleRect;

	bool b_firstPlayerConnected;
	bool b_secondPlayerConnected;

	bool b_firstPlayerPickMade;
	bool b_secondPlayerPickMade;

	bool b_firstPlayerCursorOnBigBoy;
	bool b_firstPlayerCursorOnBloodLust;
	bool b_firstPlayerCursorOnKimpah;

	bool b_secondPlayerCursorOnBigBoy;
	bool b_secondPlayerCursorOnBloodLust;
	bool b_secondPlayerCursorOnKimpah;

	bool b_kimpahUnlocked;

	bool b_lerpIcons;
	bool b_lerpIconsOut;

	sf::Text t_firstPlayerName;
	sf::Text t_secondPlayerName;

	sf::Text t_AText;
	sf::Text t_BText;

	sf::Text t_validationText;
	sf::Text t_timerText;

	sf::Vector2f m_secondNamePosition;
	sf::Vector2f m_firstNamePosition;

	sf::Vector2f m_validationTextPosition;

	sf::Font f_Font;

	std::string s_firstPlayerString;
	std::string s_secondPlayerString;

	std::string s_validationTextString;

	float speed;
	float speedIcon;

	float timerDuration;

	float timer;
	float timer2;

	float timer1stPlayerSelection;
	float timer2ndPlayerSelection;

	float countdown;

	float timer4PLerpingIn;
	float timer4PLerpingOut;

	float originPos;
	float originPos2;

	float timerAnim1;
	float timerAnim2;

	float frameX;
	float frameX2;

	bool m_haveToTransit;
};

