#include "Selection.h"
#include "Ui.h"
#include "Game.h"
#include "Sounds3D.h"

#define SCREEN_W 1920.f
#define SCREEN_H 1080.f
#define HALF_LEFT ((SCREEN_W/2) / 2)
#define HALF_RIGHT (SCREEN_W * 0.75f)

Selection::Selection()
{
	b_firstPlayerConnected = false;
	b_secondPlayerConnected = false;
	b_kimpahUnlocked = false;

	timer = 0.f;
	timer1stPlayerSelection = 0.f;
	timer2ndPlayerSelection = 0.f;
	timer4PLerpingIn = 0.f;
	timer4PLerpingOut = 0.f;

	m_backgroundSprite.setTexture(RessourceManager::get()->getSceneTexture("fond2.png"));
	m_background2Sprite.setTexture(RessourceManager::get()->getSceneTexture("fond3.png"));
	m_banderoleSprite.setTexture(RessourceManager::get()->getSceneTexture("borne.png"));

	if (!b_firstPlayerConnected)
	{
		m_firstPlayerBackgroundSprite.setTexture(RessourceManager::get()->getSceneTexture("0p1.png"));
		m_firstPlayerBackgroundSprite.setScale(sf::Vector2f(1.f, 1.1f));
	}

	if (!b_secondPlayerConnected)
	{
		m_secondPlayerBackgroundSprite.setTexture(RessourceManager::get()->getSceneTexture("0p2.png"));
		m_secondPlayerBackgroundSprite.setScale(sf::Vector2f(1.f, 1.1f));
	}

	m_bigboyIconSprite.setTexture(RessourceManager::get()->getSceneTexture("bouton_BB.png"));
	m_bloodlustIconSprite.setTexture(RessourceManager::get()->getSceneTexture("bouton_BL.png"));
	m_kimpahIconSprite.setTexture(RessourceManager::get()->getSceneTexture("bouton_K.png"));

	m_firstPlayerCadreSprite.setTexture(RessourceManager::get()->getSceneTexture("survol_j1.png"));
	m_secondPlayerCadreSprite.setTexture(RessourceManager::get()->getSceneTexture("survol_j2.png"));

	m_firstBigboyHoloSprite.setTexture(RessourceManager::get()->getSceneTexture("BB_Holo.png"));
	m_firstBigboyIdleSprite.setTexture(RessourceManager::get()->getSceneTexture("bigboy_idle.png"));

	m_secondBigboyHoloSprite.setTexture(RessourceManager::get()->getSceneTexture("BB_Holo.png"));
	m_secondBigboyIdleSprite.setTexture(RessourceManager::get()->getSceneTexture("bigboy_idle.png"));

	m_firstBloodlustHoloSprite.setTexture(RessourceManager::get()->getSceneTexture("BL_Holo.png"));
	m_firstBloodlustIdleSprite.setTexture(RessourceManager::get()->getSceneTexture("BloodLust_Idle.png"));

	m_secondBloodlustHoloSprite.setTexture(RessourceManager::get()->getSceneTexture("BL_Holo.png"));
	m_secondBloodlustIdleSprite.setTexture(RessourceManager::get()->getSceneTexture("BloodLust_Idle.png"));

	m_firstPlayerBanner.setTexture(RessourceManager::get()->getSceneTexture("banniere1.png"));
	m_secondPlayerBanner.setTexture(RessourceManager::get()->getSceneTexture("banniere2.png"));
	m_J1Sprite.setTexture(RessourceManager::get()->getSceneTexture("j1.png"));
	m_J2Sprite.setTexture(RessourceManager::get()->getSceneTexture("j2.png"));

	m_AIcon.setTexture(RessourceManager::get()->getSceneTexture("touche_a.png"));
	m_BIcon.setTexture(RessourceManager::get()->getSceneTexture("touche_b.png"));

	t_firstPlayerName.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
	t_secondPlayerName.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
	t_validationText.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
	t_timerText.setFont(RessourceManager::get()->getFont("steelfish2.otf"));

	std::shared_ptr<Animation> animPlayer = std::shared_ptr<Animation>(new Animation());
	/*m_firstBigboyIdleSprite->add*/

	t_firstPlayerName.setLetterSpacing(2);
	t_secondPlayerName.setLetterSpacing(2);
	t_validationText.setLetterSpacing(2);
	t_validationText.setCharacterSize(60);
	t_timerText.setCharacterSize(90);

	m_banderolePos = { SCREEN_W * 0.f, SCREEN_H * 0.74074f };
	m_firstPlayerBackgroundPos = { SCREEN_W * 0.18229f, 0.f };
	m_secondPlayerBackgroundPos = { SCREEN_W * 0.60416f, 0.f };
	if (b_kimpahUnlocked)
	{
		m_bigboyIconPos = { (HALF_LEFT * 1.45f) , SCREEN_H * 0.7f };
		m_bloodlustIconPos = { m_bigboyIconPos.x + (SCREEN_W * 0.1f), m_bigboyIconPos.y };
		m_kimpahIconPos = { m_bloodlustIconPos.x + (SCREEN_W * 0.1f), m_bigboyIconPos.y };
	}
	else if (!b_kimpahUnlocked)
	{
		m_bigboyIconPos = { ((SCREEN_W / 2) * 0.8f), SCREEN_H * 0.7f };
		m_bloodlustIconPos = { ((SCREEN_W / 2) * 1.f), m_bigboyIconPos.y };
	}
	m_firstPlayerCadrePos = { m_bigboyIconPos };
	m_secondPlayerCadrePos = { m_bigboyIconPos };
	m_firstBigboyHoloPos = { SCREEN_W * 0.f, SCREEN_H * 0.f };
	m_firstBigboyIdlePos = { SCREEN_W * 0.24f, SCREEN_H * 0.16f };
	m_firstBloodlustHoloPos = { (SCREEN_W / 2) * 0.f, SCREEN_H * 0.f };
	m_firstBloodlustIdlePos = { SCREEN_W * 0.25f, SCREEN_H * 0.20 };
	m_secondBigboyHoloPos = { (SCREEN_W), SCREEN_H * 0.f };
	m_secondBigboyIdlePos = { (SCREEN_W / 2) * 1.51f, SCREEN_H * 0.16 };
	m_secondBloodlustHoloPos = { (SCREEN_W), SCREEN_H * 0.f };
	m_secondBloodlustIdlePos = { (SCREEN_W / 2) * 1.5f, SCREEN_H * 0.20f };
	m_firstPlayerBannerPosition = { (HALF_LEFT) * 0.82f, SCREEN_H * 0.65 };
	m_secondPlayerBannerPosition = { (HALF_RIGHT) * 0.82f, SCREEN_H * 0.65f };
	m_firstNamePosition = { (HALF_LEFT) * 1.05f, SCREEN_H * 0.658f };
	m_secondNamePosition = { (HALF_RIGHT) * 0.92f, SCREEN_H * 0.658f };
	m_validationTextPosition = { SCREEN_W / -0.8f,SCREEN_H * 0.85f };
	m_APosition = { SCREEN_W * 0.86, SCREEN_H * 0.95 };
	m_BPosition = { SCREEN_W * 0.91, SCREEN_H * 0.95 };

	m_banderoleSprite.setPosition(m_banderolePos);
	m_firstPlayerBackgroundSprite.setPosition(m_firstPlayerBackgroundPos);
	m_secondPlayerBackgroundSprite.setPosition(m_secondPlayerBackgroundPos);
	m_bigboyIconSprite.setPosition(m_bigboyIconPos);
	m_bloodlustIconSprite.setPosition(m_bloodlustIconPos);
	m_kimpahIconSprite.setPosition(m_kimpahIconPos);
	m_firstPlayerCadreSprite.setPosition(m_firstPlayerCadrePos);
	m_secondPlayerCadreSprite.setPosition(m_secondPlayerCadrePos);
	m_firstBigboyHoloSprite.setPosition(m_firstBigboyHoloPos);
	m_firstBigboyIdleSprite.setPosition(m_firstBigboyIdlePos);
	m_firstBloodlustHoloSprite.setPosition(m_firstBloodlustHoloPos);
	m_firstBloodlustIdleSprite.setPosition(m_firstBloodlustIdlePos);
	m_secondBigboyHoloSprite.setPosition(m_secondBigboyHoloPos);
	m_secondBigboyIdleSprite.setPosition(m_secondBigboyIdlePos);
	m_secondBloodlustHoloSprite.setPosition(m_secondBloodlustHoloPos);
	m_secondBloodlustIdleSprite.setPosition(m_secondBloodlustIdlePos);
	m_firstPlayerBanner.setPosition(m_firstPlayerBannerPosition);
	m_secondPlayerBanner.setPosition(m_secondPlayerBannerPosition);
	t_firstPlayerName.setPosition(m_firstNamePosition);
	t_secondPlayerName.setPosition(m_secondNamePosition);
	m_AIcon.setPosition(m_APosition);
	m_BIcon.setPosition(m_BPosition);

	m_firstBigboyHoloSprite.setColor(sf::Color(255, 255, 255, 0));
	m_secondBigboyHoloSprite.setColor(sf::Color(255, 255, 255, 0));
	m_firstBloodlustHoloSprite.setColor(sf::Color(255, 255, 255, 0));
	m_secondBloodlustHoloSprite.setColor(sf::Color(255, 255, 255, 0));

	m_secondBigboyHoloSprite.setScale(-1.f, 1.f);
	m_secondBigboyIdleSprite.setScale(-1.f, 1.f);
	m_secondBloodlustHoloSprite.setScale(-1.f, 1.f);
	m_secondBloodlustIdleSprite.setScale(-1.f, 1.f);
	m_firstPlayerBanner.setScale(0.7f, 0.7f);
	m_secondPlayerBanner.setScale(0.7f, 0.7f);
	m_AIcon.setScale(0.5f, 0.5f);
	m_BIcon.setScale(0.5f, 0.5f);

	m_bigboyIdleRect = { 0,0,225,497 };
	m_secondBigboyIdleRect = { 0,0,225,497 };
	m_firstBigboyIdleSprite.setTextureRect(m_bigboyIdleRect);
	m_secondBigboyIdleSprite.setTextureRect(m_secondBigboyIdleRect);

	m_bloodlustIdleRect = { 0,0,142,406 };
	m_secondBloodlustIdleRect = { 0,0,142,406 };
	m_firstBloodlustIdleSprite.setTextureRect(m_bloodlustIdleRect);
	m_secondBloodlustIdleSprite.setTextureRect(m_secondBloodlustIdleRect);

	m_firstPlayerCadreSprite.setColor(sf::Color(0, 150, 255));
	m_secondPlayerCadreSprite.setColor(sf::Color(215, 0, 64));

	t_firstPlayerName.setFillColor(sf::Color(0, 150, 255));
	t_secondPlayerName.setFillColor(sf::Color(215, 0, 64));

	inputJ1 = std::shared_ptr<Input>(new Input());
	inputJ2 = std::shared_ptr<Input>(new Input());

	s_validationTextString = "PRESS A TO START GAME";
	t_validationText.setString(s_validationTextString);
	t_validationText.setOrigin(t_validationText.getGlobalBounds().width / 2, t_validationText.getGlobalBounds().height / 2.f);
	t_validationText.setPosition(m_validationTextPosition);

	t_timerText.setPosition(sf::Vector2f((SCREEN_W / 2.f) - 20.f, SCREEN_H / 2.8f));

	t_AText.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
	t_AText.setString("OK                   BACK");
	t_AText.setPosition(sf::Vector2f(m_AIcon.getPosition().x + 60.f, m_AIcon.getPosition().y + 10.f));
	t_AText.setOutlineThickness(1.f);
	t_AText.setOutlineColor(sf::Color::Black);

	timerDuration = 0.7f;
	speed = 0.5f;
	speedIcon = 3.f;

	countdown = 3.f;

	m_haveToTransit = false;
}

Selection::~Selection()
{
}

void Selection::update()
{


	inputJ1->update();
	inputJ2->update();

	if (inputJ1->getType(gp::Gamepad::A) == PRESSED && !b_firstPlayerConnected)
	{		
		b_firstPlayerConnected = true;
		if (auto ui = getParents().lock()->getComponents<Ui>())
		{
			ui->setPlayerNumber(ui->getPlayerNumber() + 1);
		}
		if (auto Menu = getParents().lock())
		{
			Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("characterselect").play();
		}
		return;
	}
	if (!b_lerpIcons || !b_lerpIconsOut)
	{
		if (inputJ2->getType(gp::Gamepad::A) == PRESSED && !b_secondPlayerConnected && !b_firstPlayerPickMade)
		{
			
			b_secondPlayerConnected = true;
			if (auto ui = getParents().lock()->getComponents<Ui>())
			{
				ui->setPlayerNumber(ui->getPlayerNumber() + 1);
			}
			if (auto Menu = getParents().lock())
			{
				Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("characterselect").play();
			}
			return;
		}
	}

	if (b_firstPlayerConnected)
	{
		timer += tools::GetTimeDelta();
		timer1stPlayerSelection += tools::GetTimeDelta();
		m_firstPlayerBackgroundSprite.setColor(sf::Color(0, 150, 255));

		animFirstPlayer();
		if (!b_firstPlayerPickMade)
		{
			if (inputJ1->getType(gp::Gamepad::B) == PRESSED && timer >= 0.2f) //RETOUR AU MENU
			{
				if (auto selectionMenu = getParents().lock())
				{
					auto Scene = selectionMenu->getParent();
					if (auto mainMenu = Scene->getObjects("MAIN_MENU"))
					{
						mainMenu->setActive(true);
						selectionMenu->setActive(false);
					}
				}
				timer = 0.f;
				b_firstPlayerCursorOnBigBoy = true;
				b_secondPlayerCursorOnBigBoy = true;
				m_firstPlayerBackgroundSprite.setTexture(RessourceManager::get()->getSceneTexture("0p1.png"));
				m_secondPlayerBackgroundSprite.setTexture(RessourceManager::get()->getSceneTexture("0p2.png"));
				m_firstPlayerBackgroundSprite.setColor(sf::Color(255, 255, 255));
				m_secondPlayerBackgroundSprite.setColor(sf::Color(255, 255, 255));
				b_firstPlayerConnected = false;
				b_secondPlayerConnected = false;
				if (auto Menu = getParents().lock())
				{
					Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("back").play();
				}
			}
			if (b_kimpahUnlocked)
			{
				if (inputJ1->moveDirection(gpDirection::RIGHT) && timer > 0.3f)
				{
					
					if (m_firstPlayerCadrePos.x == 696.f)
					{
						m_firstPlayerCadrePos.x += 192.f;
					}
					else if (m_firstPlayerCadrePos.x == 888.f)
					{
						m_firstPlayerCadrePos.x += 192.f;
					}
					else if (m_firstPlayerCadrePos.x == 1080.f)
					{
						m_firstPlayerCadrePos.x -= 384.f;
					}
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("characterswitch").play();
					}
					timer = 0.f;
					timer1stPlayerSelection = 0.f;
				}
				if (inputJ1->moveDirection(gpDirection::LEFT) && timer > 0.3f)
				{
					
					if (m_firstPlayerCadrePos.x == 696.f)
					{
						m_firstPlayerCadrePos.x += 384.f;
					}
					else if (m_firstPlayerCadrePos.x == 888.f)
					{
						m_firstPlayerCadrePos.x -= 192.f;
					}
					else if (m_firstPlayerCadrePos.x == 1080.f)
					{
						m_firstPlayerCadrePos.x -= 192.f;
					}
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("characterswitch").play();
					}
					timer = 0.f;
					timer1stPlayerSelection = 0.f;
				}
			}
			else if (!b_kimpahUnlocked)
			{
				if (inputJ1->moveDirection(gpDirection::RIGHT) && timer > 0.3f)
				{
					
					if (m_firstPlayerCadrePos.x == 768.f)
					{
						m_firstPlayerCadrePos.x += 192.f;
					}
					else if (m_firstPlayerCadrePos.x == 960.f)
					{
						m_firstPlayerCadrePos.x -= 192.f;
					}
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("characterswitch").play();
					}
					timer = 0.f;
					timer1stPlayerSelection = 0.f;
				}
				if (inputJ1->moveDirection(gpDirection::LEFT) && timer > 0.3f)
				{
					
					if (m_firstPlayerCadrePos.x == 768.f)
					{
						m_firstPlayerCadrePos.x += 192.f;
					}
					else if (m_firstPlayerCadrePos.x == 960.f)
					{
						m_firstPlayerCadrePos.x -= 192.f;
					}
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("characterswitch").play();
					}
					timer = 0.f;
					timer1stPlayerSelection = 0.f;
				}
			}
			m_firstPlayerCadreSprite.setPosition(m_firstPlayerCadrePos);

			if (m_firstPlayerCadrePos.x == 696.f || m_firstPlayerCadrePos.x == 768.f)
			{
				b_firstPlayerCursorOnBigBoy = true;
				b_firstPlayerCursorOnBloodLust = false;
				b_firstPlayerCursorOnKimpah = false;
				s_firstPlayerString = "BIGBOY";
				sf::Color currentColor = m_firstBigboyHoloSprite.getColor();

				if (m_firstBigboyHoloSprite.getColor().a < 255 && timer1stPlayerSelection < timerDuration)
				{
					float alpha = 255.f * (timer1stPlayerSelection / timerDuration);
					m_firstBigboyHoloSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
				}

				if (m_firstBigboyHoloPos.x > (SCREEN_W / -10) && m_firstBigboyHoloPos.x - speed > (SCREEN_W / -10) && timer1stPlayerSelection < timerDuration)
					m_firstBigboyHoloPos.x -= speed;

				//reset opacité + pos des autres
				m_firstBloodlustHoloSprite.setColor(sf::Color(255, 255, 255, 0));
				m_firstBloodlustHoloPos = { (SCREEN_W / 2) * 0.f, SCREEN_H * 0.f };
				//m_firstKimpahHoloPos = { (SCREEN_W / 2) * 0.f, SCREEN_H * 0.f };
			}
			else if (m_firstPlayerCadrePos.x == 888.f || m_firstPlayerCadrePos.x == 960.f)
			{

				b_firstPlayerCursorOnBigBoy = false;
				b_firstPlayerCursorOnBloodLust = true;
				b_firstPlayerCursorOnKimpah = false;
				s_firstPlayerString = "BLOODLUST";

				sf::Color currentColor = m_firstBloodlustHoloSprite.getColor();
				if (m_firstBloodlustHoloSprite.getColor().a < 255 && timer1stPlayerSelection < timerDuration)
				{
					float alpha = 255.f * (timer1stPlayerSelection / timerDuration);
					m_firstBloodlustHoloSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
				}

				if (m_firstBloodlustHoloPos.x > (SCREEN_W / -10) && m_firstBloodlustHoloPos.x - speed > (SCREEN_W / -10) && timer1stPlayerSelection < timerDuration)
					m_firstBloodlustHoloPos.x -= speed;

				//reset opacité + pos des autres
				m_firstBigboyHoloSprite.setColor(sf::Color(255, 255, 255, 0));
				m_firstBigboyHoloPos = { SCREEN_W * 0.f, SCREEN_H * 0.f };
			}
			else if (m_firstPlayerCadrePos.x == 1080.f)
			{

				b_firstPlayerCursorOnBigBoy = false;
				b_firstPlayerCursorOnBloodLust = false;
				b_firstPlayerCursorOnKimpah = true;
				s_firstPlayerString = "KIMPAH";
			}

			m_firstBigboyHoloSprite.setPosition(m_firstBigboyHoloPos);
			m_firstBloodlustHoloSprite.setPosition(m_firstBloodlustHoloPos);
			t_firstPlayerName.setString(s_firstPlayerString);

			if (auto parent = m_Parents.lock())
			{
				auto ui = parent->getComponents<Ui>();

				if (inputJ1->getType(gp::Gamepad::A) == PRESSED && timer > 0.2f)
				{
					if (b_kimpahUnlocked)
					{
						if (m_firstPlayerCadrePos.x == 696.f)
						{
							if (b_secondPlayerPickMade && m_secondPlayerCadrePos.x != 696.f || !b_secondPlayerPickMade)
							{
								m_firstBigboyHoloSprite.setColor(sf::Color(215, 0, 64));
								b_firstPlayerPickMade = true;
								ui->setFirstPlayerType(1);
							}
						}
						else if (m_firstPlayerCadrePos.x == 888.f)
						{
							if (b_secondPlayerPickMade && m_secondPlayerCadrePos.x != 888.f || !b_secondPlayerPickMade)
							{
								m_firstBloodlustHoloSprite.setColor(sf::Color(215, 0, 64));
								b_firstPlayerPickMade = true;
								ui->setFirstPlayerType(2);
							}
						}
						else if (m_secondPlayerCadrePos.x == 1080.f)
						{
							if (b_secondPlayerPickMade && m_secondPlayerCadrePos.x != 1080 || !b_secondPlayerPickMade) {
								m_firstKimpahHoloSprite.setColor(sf::Color(215, 0, 64));
								b_firstPlayerPickMade = true;
								ui->setFirstPlayerType(3);
							}
						}
					}
					else if (!b_kimpahUnlocked)
					{
						
						if (m_firstPlayerCadrePos.x == 768.f)
						{
							if (b_secondPlayerPickMade && m_secondPlayerCadrePos.x != 768.f || !b_secondPlayerPickMade)
							{
								m_firstBigboyHoloSprite.setColor(sf::Color(0, 150, 255));
								b_firstPlayerPickMade = true;
								ui->setFirstPlayerType(1);
							}
						}
						else if (m_firstPlayerCadrePos.x == 960.f)
						{
							if (b_secondPlayerPickMade && m_secondPlayerCadrePos.x != 960.f || !b_secondPlayerPickMade) {
								m_firstBloodlustHoloSprite.setColor(sf::Color(0, 150, 255));
								b_firstPlayerPickMade = true;
								ui->setFirstPlayerType(2);
							}
						}
					}
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("characterselect").play();
					}
					timer = 0.f;
				}
			}
		}
		if (b_firstPlayerPickMade)
		{
			if (!b_secondPlayerConnected)
			{
				timer4PLerpingIn += tools::GetTimeDelta();

				if (countdown >= 0.f)
				{
					countdown -= tools::GetTimeDelta();
					int secondsremaining = static_cast<int>(countdown) + 1;
					t_timerText.setString(std::to_string(secondsremaining));

					if (countdown <= 0.f)
					{
						b_lerpIcons = true;
						b_lerpIconsOut = false;

						timer4PLerpingIn = 0.f;
					}
				}

				if (b_lerpIcons)
				{
					if (m_bigboyIconPos.x < 2000)
					{
						m_bigboyIconPos.x += speedIcon;
					}
					if (m_bloodlustIconPos.x < 2221)
					{
						m_bloodlustIconPos.x += speedIcon;
					}
					if (m_kimpahIconPos.x < 2442)
					{
						m_kimpahIconPos.x += speedIcon;
					}
					if (m_validationTextPosition.x < (SCREEN_W / 2.f))
					{
						m_validationTextPosition.x += speedIcon;
					}
					m_firstPlayerCadreSprite.setColor(sf::Color(255, 255, 255, 0));
				}
				if (inputJ1->getType(gp::Gamepad::B) == PRESSED && timer > 0.2f)
				{
					b_lerpIcons = false;
					b_lerpIconsOut = true;
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("back").play();
					}
					timer = 0.f;

				}
				if (b_lerpIconsOut)
				{
					if (!b_kimpahUnlocked)
					{
						if (m_bigboyIconPos.x > ((SCREEN_W / 2) * 0.8f))//696
						{
							m_bigboyIconPos.x -= speedIcon;
						}
						if (m_bloodlustIconPos.x > ((SCREEN_W / 2) * 1.f))//SCREEN_W * 0.1f = 192
						{
							m_bloodlustIconPos.x -= speedIcon;
						}
						if (m_kimpahIconPos.x > (((HALF_LEFT * 1.45f) + (SCREEN_W * 0.1f)) + (SCREEN_W * 0.1f)))
						{
							m_kimpahIconPos.x -= speedIcon;
						}
					}
					else if (b_kimpahUnlocked)
					{
						if (m_bigboyIconPos.x > (HALF_LEFT * 1.45f))//696
						{
							m_bigboyIconPos.x -= speedIcon;
						}
						if (m_bloodlustIconPos.x > ((HALF_LEFT * 1.45f) + (SCREEN_W * 0.1f)))//SCREEN_W * 0.1f = 192
						{
							m_bloodlustIconPos.x -= speedIcon;
						}
						if (m_kimpahIconPos.x > (((HALF_LEFT * 1.45f) + (SCREEN_W * 0.1f)) + (SCREEN_W * 0.1f)))
						{
							m_kimpahIconPos.x -= speedIcon;
						}
					}

					if (m_validationTextPosition.x > (SCREEN_W / -0.8f))
					{
						m_validationTextPosition.x -= speedIcon;
					}

					m_firstPlayerCadreSprite.setColor(sf::Color(0, 150, 255, 255));

					if (auto parent = m_Parents.lock())
					{
						auto ui = parent->getComponents<Ui>();

						if (m_kimpahIconPos.x == (((HALF_LEFT * 1.45f) + (SCREEN_W * 0.1f)) + (SCREEN_W * 0.1f))) //CONDITION DE SORTIE DE LA BOUCLE
						{
							m_firstPlayerCadreSprite.setTexture(RessourceManager::get()->getSceneTexture("survol_j1.png"));
							m_secondPlayerCadreSprite.setTexture(RessourceManager::get()->getSceneTexture("survol_j2.png"));
							m_firstBigboyHoloSprite.setColor(sf::Color(255, 255, 255, 255));
							m_secondBigboyHoloSprite.setColor(sf::Color(255, 255, 255, 255));
							m_firstBloodlustHoloSprite.setColor(sf::Color(255, 255, 255, 255));
							m_secondBloodlustHoloSprite.setColor(sf::Color(255, 255, 255, 255));
							m_firstKimpahHoloSprite.setColor(sf::Color(255, 255, 255, 255));
							m_secondKimpahHoloSprite.setColor(sf::Color(255, 255, 255, 255));
							ui->setFirstPlayerType(0);
							ui->setSecondPlayerType(0);
							b_firstPlayerPickMade = false;
							b_secondPlayerPickMade = false;
							b_lerpIcons = false;
							b_lerpIconsOut = false;
							countdown = 3.f;
						}
					}
				}
				m_bigboyIconSprite.setPosition(m_bigboyIconPos);
				m_bloodlustIconSprite.setPosition(m_bloodlustIconPos);
				m_kimpahIconSprite.setPosition(m_kimpahIconPos);
				t_validationText.setPosition(m_validationTextPosition);

				if (inputJ1->getType(gp::Gamepad::A) == PRESSED && m_validationTextPosition.x == (SCREEN_W / 2.f) && timer > 0.3f)
				{
					//TRANSITION TO GAME HERE
					if (auto Menu = getParents().lock())
					{						
						float volume = Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getVolumeMusic();	
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->graduallyStopMusic("menumusic", 1);
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("startgame").play();
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->setAllMusicVolume(volume);
						m_haveToTransit = true;
					}
					
					timer = 0.f;
				}
				//if (getParents().lock()->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("startgame").getStatus() == sf::Sound::Stopped && getParents().lock()->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getMusic("menumusic").getStatus() == sf::Sound::Stopped)
					
				if (inputJ1->getType(gp::Gamepad::B) == PRESSED && m_kimpahIconPos.x == (((HALF_LEFT * 1.45f) + (SCREEN_W * 0.1f)) + (SCREEN_W * 0.1f)) && timer >= 0.3f)
				{
					b_firstPlayerPickMade = false;
					m_firstPlayerCadreSprite.setTexture(RessourceManager::get()->getSceneTexture("survol_j1.png"));
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("back").play();
					}
					timer = 0.f;
				}
			}
			else if (b_secondPlayerConnected)
			{

			}
			if (!b_lerpIcons && !b_lerpIconsOut)
			{
				if (inputJ1->getType(gp::Gamepad::B) == PRESSED && timer > 0.2f)
				{
					
					if (m_firstPlayerCadrePos.x == 696.f || m_firstPlayerCadrePos.x == 768.f)
					{
						m_firstBigboyHoloSprite.setColor(sf::Color(255, 255, 255, 255));
						b_firstPlayerPickMade = false;
						m_firstPlayerCadreSprite.setTexture(RessourceManager::get()->getSceneTexture("survol_j1.png"));
					}
					if (m_firstPlayerCadrePos.x == 888.f || m_firstPlayerCadrePos.x == 960.f)
					{
						m_firstBloodlustHoloSprite.setColor(sf::Color(255, 255, 255, 255));
						b_firstPlayerPickMade = false;
						m_firstPlayerCadreSprite.setTexture(RessourceManager::get()->getSceneTexture("survol_j1.png"));
					}
					if (m_firstPlayerCadrePos.x == 1080.f)
					{
						m_firstKimpahHoloSprite.setColor(sf::Color(255, 255, 255, 255));
						b_firstPlayerPickMade = false;
						m_firstPlayerCadreSprite.setTexture(RessourceManager::get()->getSceneTexture("survol_j1.png"));
					}

					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("cancel").play();
					}
					timer = 0.f;
				}
			}

		}
	}
	if (b_secondPlayerConnected)
	{
		timer2 += tools::GetTimeDelta();
		timer2ndPlayerSelection += tools::GetTimeDelta();
		m_secondPlayerBackgroundSprite.setColor(sf::Color(255, 0, 0));

		animSecondPlayer();

		if (!b_secondPlayerPickMade)
		{
			if (b_kimpahUnlocked)
			{
				if (inputJ2->moveDirection(gpDirection::RIGHT) && timer2 > 0.3f)
				{
					
					if (m_secondPlayerCadrePos.x == 696.f)
					{
						m_secondPlayerCadrePos.x += 192.f;
					}
					else if (m_secondPlayerCadrePos.x == 888.f)
					{
						m_secondPlayerCadrePos.x += 192.f;
					}
					else if (m_secondPlayerCadrePos.x == 1080.f)
					{
						m_secondPlayerCadrePos.x -= 384.f;
					}
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("characterswitch").play();
					}
					timer2 = 0.f;
					timer2ndPlayerSelection = 0.f;
				}
				if (inputJ2->moveDirection(gpDirection::LEFT) && timer2 > 0.3f)
				{
					
					if (m_secondPlayerCadrePos.x == 696.f)
					{
						m_secondPlayerCadrePos.x += 384.f;
					}
					else if (m_secondPlayerCadrePos.x == 888.f)
					{
						m_secondPlayerCadrePos.x -= 192.f;
					}
					else if (m_secondPlayerCadrePos.x == 1080.f)
					{
						m_secondPlayerCadrePos.x -= 192.f;
					}
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("characterswitch").play();
					}
					timer2 = 0.f;
					timer2ndPlayerSelection = 0.f;
				}
			}
			else if (!b_kimpahUnlocked)
			{
				if (inputJ2->moveDirection(gpDirection::RIGHT) && timer2 > 0.3f)
				{
					
					if (m_secondPlayerCadrePos.x == 768.f)
					{
						m_secondPlayerCadrePos.x += 192.f;
					}
					else if (m_secondPlayerCadrePos.x == 960.f)
					{
						m_secondPlayerCadrePos.x -= 192.f;
					}
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("characterswitch").play();
					}
					timer2 = 0.f;
					timer2ndPlayerSelection = 0.f;
				}
				if (inputJ2->moveDirection(gpDirection::LEFT) && timer2 > 0.3f)
				{
					
					if (m_secondPlayerCadrePos.x == 768.f)
					{
						m_secondPlayerCadrePos.x += 192.f;
					}
					else if (m_secondPlayerCadrePos.x == 960.f)
					{
						m_secondPlayerCadrePos.x -= 192.f;
					}
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("characterswitch").play();
					}
					timer2 = 0.f;
					timer2ndPlayerSelection = 0.f;
				}
			}
			m_secondPlayerCadreSprite.setPosition(m_secondPlayerCadrePos);

			if (m_secondPlayerCadrePos.x == 696.f || m_secondPlayerCadrePos.x == 768.f)
			{
				b_secondPlayerCursorOnBigBoy = true;
				b_secondPlayerCursorOnBloodLust = false;
				b_secondPlayerCursorOnKimpah = false;
				s_secondPlayerString = "BIGBOY";

				sf::Color currentColor = m_secondBigboyHoloSprite.getColor();

				if (m_secondBigboyHoloSprite.getColor().a < 255 && timer2ndPlayerSelection < timerDuration)
				{
					float alpha = 255.f * (timer2ndPlayerSelection / timerDuration);
					m_secondBigboyHoloSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
				}

				if (m_secondBigboyHoloPos.x < (SCREEN_W * 1.095f) && m_secondBigboyHoloPos.x - speed < (SCREEN_W * 1.095f) && timer2ndPlayerSelection < timerDuration)
					m_secondBigboyHoloPos.x += speed;

				//reset opacité + pos des autres
				m_secondBloodlustHoloSprite.setColor(sf::Color(255, 255, 255, 0));
				m_secondBloodlustHoloPos = { (SCREEN_W), SCREEN_H * 0.f };
			}
			else if (m_secondPlayerCadrePos.x == 888.f || m_secondPlayerCadrePos.x == 960.f)
			{
				b_secondPlayerCursorOnBigBoy = false;
				b_secondPlayerCursorOnBloodLust = true;
				b_secondPlayerCursorOnKimpah = false;
				s_secondPlayerString = "BLOODLUST";

				sf::Color currentColor = m_secondBloodlustHoloSprite.getColor();

				if (m_secondBloodlustHoloSprite.getColor().a < 255 && timer2ndPlayerSelection < timerDuration)
				{
					float alpha = 255.f * (timer2ndPlayerSelection / timerDuration);
					m_secondBloodlustHoloSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
				}

				if (m_secondBloodlustHoloPos.x < (SCREEN_W * 1.095f) && m_secondBloodlustHoloPos.x - speed < (SCREEN_W * 1.095f) && timer2ndPlayerSelection < timerDuration)
					m_secondBloodlustHoloPos.x += speed;

				//reset opacité + pos des autres
				m_secondBigboyHoloSprite.setColor(sf::Color(255, 255, 255, 0));
				m_secondBigboyHoloPos = { (SCREEN_W) , SCREEN_H * 0.f };
			}
			else if (m_secondPlayerCadrePos.x == 1080.f)
			{
				b_secondPlayerCursorOnBigBoy = false;
				b_secondPlayerCursorOnBloodLust = false;
				b_secondPlayerCursorOnKimpah = true;
				s_secondPlayerString = "KIMPAH";
			}
			m_secondBigboyHoloSprite.setPosition(m_secondBigboyHoloPos);
			m_secondBloodlustHoloSprite.setPosition(m_secondBloodlustHoloPos);
			t_secondPlayerName.setString(s_secondPlayerString);

			if (auto parent = m_Parents.lock())
			{
				auto ui = parent->getComponents<Ui>();

				if (inputJ2->getType(gp::Gamepad::A) == PRESSED && timer2 > 0.2f)
				{
					
					if (b_kimpahUnlocked)
					{
						originPos = m_firstPlayerCadrePos.x;
						originPos2 = m_secondPlayerCadrePos.x;

						if (m_secondPlayerCadrePos.x == 696.f)
						{
							if (b_firstPlayerPickMade && m_firstPlayerCadrePos.x != 696.f || !b_firstPlayerPickMade)
							{
								m_secondBigboyHoloSprite.setColor(sf::Color(215, 0, 64));
								b_secondPlayerPickMade = true;
								ui->setSecondPlayerType(1);
							}
						}
						else if (m_secondPlayerCadrePos.x == 888.f)
						{
							if (b_firstPlayerPickMade && m_firstPlayerCadrePos.x != 888.f || !b_firstPlayerPickMade)
							{
								m_secondBloodlustHoloSprite.setColor(sf::Color(215, 0, 64));
								b_secondPlayerPickMade = true;
								ui->setSecondPlayerType(2);
							}
						}
						else if (m_secondPlayerCadrePos.x == 1080.f)
						{
							if (b_firstPlayerPickMade && m_firstPlayerCadrePos.x != 1080 || !b_firstPlayerPickMade) {
								m_secondKimpahHoloSprite.setColor(sf::Color(215, 0, 64));
								b_secondPlayerPickMade = true;
								ui->setSecondPlayerType(3);
							}
						}
					}
					else if (!b_kimpahUnlocked)
					{
						originPos = m_firstPlayerCadrePos.x;
						originPos2 = m_secondPlayerCadrePos.x;

						if (m_secondPlayerCadrePos.x == 768.f)
						{
							if (b_firstPlayerPickMade && m_firstPlayerCadrePos.x != 768.f || !b_firstPlayerPickMade)
							{
								m_secondBigboyHoloSprite.setColor(sf::Color(215, 0, 64));
								b_secondPlayerPickMade = true;
								ui->setSecondPlayerType(1);
							}
						}
						else if (m_secondPlayerCadrePos.x == 960.f)
						{
							if (b_firstPlayerPickMade && m_firstPlayerCadrePos.x != 960.f || !b_firstPlayerPickMade) {
								m_secondBloodlustHoloSprite.setColor(sf::Color(215, 0, 64));
								b_secondPlayerPickMade = true;
								ui->setSecondPlayerType(2);
							}
						}
					}
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("characterselect").play();
					}
					timer2 = 0.f;
				}
			}
		}
		else if (b_secondPlayerPickMade)//si le joueur 2 a pick
		{
			if (b_firstPlayerPickMade)
			{
				timer4PLerpingIn += tools::GetTimeDelta();

				if (countdown >= 0.f)
				{
					countdown -= tools::GetTimeDelta();
					int secondsremaining = static_cast<int>(countdown) + 1;
					t_timerText.setString(std::to_string(secondsremaining));

					if (countdown <= 0.f)
					{
						b_lerpIcons = true;
						b_lerpIconsOut = false;

						timer4PLerpingIn = 0.f;
					}
				}
				if (b_lerpIcons)
				{
					if (m_bigboyIconPos.x < 2000)
					{
						m_bigboyIconPos.x += speedIcon;
					}
					if (m_bloodlustIconPos.x < 2221)
					{
						m_bloodlustIconPos.x += speedIcon;
					}
					if (m_kimpahIconPos.x < 2442)
					{
						m_kimpahIconPos.x += speedIcon;
					}

					if (m_validationTextPosition.x < (SCREEN_W / 2.f))
					{
						m_validationTextPosition.x += speedIcon;
					}

					if (inputJ2->getType(gp::Gamepad::B) == PRESSED && timer2 >= 0.3f || inputJ1->getType(gp::Gamepad::B) == PRESSED && timer >= 0.3f)
					{
						

						b_lerpIcons = false;
						b_lerpIconsOut = true;

						if (auto Menu = getParents().lock())
						{
							Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("back").play();
						}
						timer2 = 0.f;
						timer = 0.f;
					}
				}

				if (b_lerpIconsOut)
				{
					if (!b_kimpahUnlocked)
					{
						if (m_bigboyIconPos.x > ((SCREEN_W / 2) * 0.8f))//696
						{
							m_bigboyIconPos.x -= speedIcon;
						}
						if (m_bloodlustIconPos.x > ((SCREEN_W / 2) * 1.f))//SCREEN_W * 0.1f = 192
						{
							m_bloodlustIconPos.x -= speedIcon;
						}
						if (m_kimpahIconPos.x > (((HALF_LEFT * 1.45f) + (SCREEN_W * 0.1f)) + (SCREEN_W * 0.1f)))
						{
							m_kimpahIconPos.x -= speedIcon;
						}
					}
					else if (b_kimpahUnlocked)
					{
						if (m_bigboyIconPos.x > (HALF_LEFT * 1.45f))//696
						{
							m_bigboyIconPos.x -= speedIcon;
						}
						if (m_bloodlustIconPos.x > ((HALF_LEFT * 1.45f) + (SCREEN_W * 0.1f)))//SCREEN_W * 0.1f = 192
						{
							m_bloodlustIconPos.x -= speedIcon;
						}
						if (m_kimpahIconPos.x > (((HALF_LEFT * 1.45f) + (SCREEN_W * 0.1f)) + (SCREEN_W * 0.1f)))
						{
							m_kimpahIconPos.x -= speedIcon;
						}
					}

					if (m_validationTextPosition.x > (SCREEN_W / -0.8f))
					{
						m_validationTextPosition.x -= speedIcon;
					}

					m_firstPlayerCadreSprite.setColor(sf::Color(0, 150, 255, 255));
					m_secondPlayerCadreSprite.setColor(sf::Color(255, 0, 64, 255));

					if (auto parent = m_Parents.lock())
					{
						auto ui = parent->getComponents<Ui>();

						if (m_kimpahIconPos.x == (((HALF_LEFT * 1.45f) + (SCREEN_W * 0.1f)) + (SCREEN_W * 0.1f))) //CONDITION DE SORTIE DE LA BOUCLE
						{
							m_firstPlayerCadreSprite.setTexture(RessourceManager::get()->getSceneTexture("survol_j1.png"));
							m_secondPlayerCadreSprite.setTexture(RessourceManager::get()->getSceneTexture("survol_j2.png"));
							m_firstBigboyHoloSprite.setColor(sf::Color(255, 255, 255, 255));
							m_secondBigboyHoloSprite.setColor(sf::Color(255, 255, 255, 255));
							m_firstBloodlustHoloSprite.setColor(sf::Color(255, 255, 255, 255));
							m_secondBloodlustHoloSprite.setColor(sf::Color(255, 255, 255, 255));
							m_firstKimpahHoloSprite.setColor(sf::Color(255, 255, 255, 255));
							m_secondKimpahHoloSprite.setColor(sf::Color(255, 255, 255, 255));
							ui->setFirstPlayerType(0);
							ui->setSecondPlayerType(0);
							b_firstPlayerPickMade = false;
							b_secondPlayerPickMade = false;
							b_lerpIcons = false;
							b_lerpIconsOut = false;
							countdown = 3.f;
						}
					}
				}
				m_bigboyIconSprite.setPosition(m_bigboyIconPos);
				m_bloodlustIconSprite.setPosition(m_bloodlustIconPos);
				m_kimpahIconSprite.setPosition(m_kimpahIconPos);
				t_validationText.setPosition(m_validationTextPosition);

				if (inputJ2->getType(gp::Gamepad::A) == PRESSED && m_validationTextPosition.x == (SCREEN_W / 2.f) && timer2 >= 0.3f || inputJ1->getType(gp::Gamepad::A) == PRESSED && m_validationTextPosition.x == (SCREEN_W / 2.f) && timer >= 0.3f)
				{
					//TRANSITION TO GAME HERE
					if (auto Menu = getParents().lock())
					{
						float volume = Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getVolumeMusic();
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->graduallyStopMusic("menumusic", 1);
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("startgame").play();
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->setAllMusicVolume(volume);
					}
					m_haveToTransit = true;
					timer2 = 0.f;
					timer = 0.f;
				}
				/*if (getParents().lock()->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("startgame").getStatus() == sf::Sound::Stopped && getParents().lock()->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getMusic("menumusic").getStatus() == sf::Sound::Stopped)
					m_haveToTransit = true;*/
			}
			if (inputJ2->getType(gp::Gamepad::B) == PRESSED && timer2 >= 0.3f)
			{
				
				b_secondPlayerPickMade = false;
				m_secondPlayerCadreSprite.setTexture(RessourceManager::get()->getSceneTexture("survol_j2.png"));
				if (auto Menu = getParents().lock())
				{
					Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("back").play();
				}

				timer2 = 0.f;
			}
		}
	}
}

void Selection::draw()
{
	window.draw(m_backgroundSprite);
	window.draw(m_background2Sprite);

	if (b_firstPlayerCursorOnBigBoy && b_firstPlayerConnected)
		window.draw(m_firstBigboyHoloSprite);
	if (b_secondPlayerCursorOnBigBoy && b_secondPlayerConnected)
		window.draw(m_secondBigboyHoloSprite);
	if (b_firstPlayerCursorOnBloodLust && b_firstPlayerConnected)
		window.draw(m_firstBloodlustHoloSprite);
	if (b_secondPlayerCursorOnBloodLust && b_secondPlayerConnected)
		window.draw(m_secondBloodlustHoloSprite);
	if (b_firstPlayerConnected)
	{
		m_firstPlayerBackgroundSprite.setTexture(RessourceManager::get()->getSceneTexture("plan.png"));
	}
	window.draw(m_firstPlayerBackgroundSprite);
	if (b_secondPlayerConnected)
	{
		m_secondPlayerBackgroundSprite.setTexture(RessourceManager::get()->getSceneTexture("plan.png"));
	}
	window.draw(m_secondPlayerBackgroundSprite);
	if (b_firstPlayerCursorOnBigBoy && b_firstPlayerConnected)
	{
		window.draw(m_firstBigboyIdleSprite);
	}
	if (b_secondPlayerCursorOnBigBoy && b_secondPlayerConnected)
	{
		window.draw(m_secondBigboyIdleSprite);
	}
	if (b_firstPlayerCursorOnBloodLust && b_firstPlayerConnected)
	{
		window.draw(m_firstBloodlustIdleSprite);
	}
	if (b_secondPlayerCursorOnBloodLust && b_secondPlayerConnected)
		window.draw(m_secondBloodlustIdleSprite);
	if (b_firstPlayerConnected)
	{
		window.draw(m_firstPlayerBanner);
		window.draw(t_firstPlayerName);
		//window.draw(m_J1Sprite);
	}
	if (b_secondPlayerConnected)
	{
		window.draw(m_secondPlayerBanner);
		window.draw(t_secondPlayerName);
		//window.draw(m_J2Sprite);
	}
	window.draw(m_banderoleSprite);

	if (!b_lerpIcons)
	{
		if (b_kimpahUnlocked)
		{
			for (int i = 0; i < 3; i++)
			{
				sf::Sprite tempSprite;
				tempSprite.setTexture(RessourceManager::get()->getSceneTexture("vignette_base.png"));
				if (i == 0)
					tempSprite.setPosition(m_bigboyIconPos);
				else
					tempSprite.setPosition(m_bigboyIconPos.x + (192.f * i), m_bigboyIconPos.y);

				window.draw(tempSprite);
			}
		}
		else if (!b_kimpahUnlocked)
		{
			for (int i = 0; i < 2; i++)
			{
				sf::Sprite tempSprite;
				tempSprite.setTexture(RessourceManager::get()->getSceneTexture("vignette_base.png"));
				if (i == 0)
					tempSprite.setPosition(m_bigboyIconPos);
				else
					tempSprite.setPosition(m_bigboyIconPos.x + (192.f * i), m_bigboyIconPos.y);

				window.draw(tempSprite);
			}
		}
	}

	if (b_secondPlayerConnected)
	{
		if (b_secondPlayerPickMade)
			m_secondPlayerCadreSprite.setTexture(RessourceManager::get()->getSceneTexture("fixed.png"));
		if (!b_lerpIcons && !b_lerpIconsOut)
			window.draw(m_secondPlayerCadreSprite);
	}
	if (b_firstPlayerConnected)
	{
		if (b_firstPlayerPickMade)
			m_firstPlayerCadreSprite.setTexture(RessourceManager::get()->getSceneTexture("fixed.png"));
		if (!b_lerpIcons && !b_lerpIconsOut)
			window.draw(m_firstPlayerCadreSprite);
	}
	window.draw(m_bigboyIconSprite);
	window.draw(m_bloodlustIconSprite);
	if (b_kimpahUnlocked)
		window.draw(m_kimpahIconSprite);
	if(b_firstPlayerPickMade && !b_lerpIcons && !b_lerpIconsOut || b_firstPlayerPickMade && b_secondPlayerPickMade && !b_lerpIcons && !b_lerpIconsOut)
	window.draw(t_timerText);
	window.draw(t_validationText);
	window.draw(m_AIcon);
	window.draw(m_BIcon);
	window.draw(t_AText);
}

void Selection::animFirstPlayer()
{
	timerAnim1 += tools::GetTimeDelta();

	if (m_firstPlayerCadrePos.x == 696.f || m_firstPlayerCadrePos.x == 768.f)
	{
		if (timerAnim1 > 0.15f)
		{
			frameX++;

			if (frameX > 7)
				frameX = 0;

			m_bigboyIdleRect.left = frameX * m_bigboyIdleRect.width;

			timerAnim1 = 0.f;
		}
		m_firstBigboyIdleSprite.setTextureRect(m_bigboyIdleRect);
	}
	else if (m_firstPlayerCadrePos.x == 888.f || m_firstPlayerCadrePos.x == 960.f)
	{
		if (timerAnim1 > 0.15f)
		{
			frameX++;

			if (frameX > 8)
				frameX = 0;

			m_bloodlustIdleRect.left = frameX * m_bloodlustIdleRect.width;

			timerAnim1 = 0.f;
		}
		m_firstBloodlustIdleSprite.setTextureRect(m_bloodlustIdleRect);
	}
}

void Selection::animSecondPlayer()
{
	timerAnim2 += tools::GetTimeDelta();

	if (m_secondPlayerCadrePos.x == 696.f || m_secondPlayerCadrePos.x == 768.f)
	{
		if (timerAnim2 > 0.15f)
		{
			frameX2++;

			if (frameX2 > 7)
				frameX2 = 0;

			m_secondBigboyIdleRect.left = frameX2 * m_secondBigboyIdleRect.width;

			timerAnim2 = 0.f;
		}
		m_secondBigboyIdleSprite.setTextureRect(m_secondBigboyIdleRect);
	}
	else if (m_secondPlayerCadrePos.x == 888.f || m_secondPlayerCadrePos.x == 960.f)
	{
		if (timerAnim2 > 0.15f)
		{
			frameX2++;

			if (frameX2 > 8)
				frameX2 = 0;

			m_secondBloodlustIdleRect.left = frameX2 * m_secondBloodlustIdleRect.width;

			timerAnim2 = 0.f;
		}
		m_secondBloodlustIdleSprite.setTextureRect(m_secondBloodlustIdleRect);
	}
}

std::shared_ptr<Input> Selection::getInputJ1()
{
	return inputJ1;
}

std::shared_ptr<Input> Selection::getInputJ2()
{
	return inputJ2;
}

void Selection::setInputJ1(std::shared_ptr<Input> _input)
{
	inputJ1 = _input;
}

void Selection::setInputJ2(std::shared_ptr<Input> _input)
{
	inputJ2 = _input;
}

bool Selection::getTransitToGame()
{
	return m_haveToTransit;
}
