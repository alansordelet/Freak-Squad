#include "MainMenu.h"
#include "MenuFactory.h"
#include "Selection.h"
#include"Sounds3D.h"

MainMenu::MainMenu()
{
	m_isBloodLeftPlaced = false;
	m_isBloodRightPlaced = false;

	m_posBloodLeft = posBloodLeftOut;
	m_posBloodRight = posBloodRightOut;
	m_posCursor = { 0.01,posStory.y };
	m_cursorSelect = STORY;
	m_keyTimer = 0;
	m_startCredits = false;
}

MainMenu::~MainMenu()
{
}

void MainMenu::update()
{
	m_keyTimer += tools::GetTimeDelta();
	updateBloodLeft();
	updateBloodRight();
	updateCursor();
	changeMenu();
	if (auto parent = getParents().lock())
	{
		if (auto fireFist = parent->getObjects("FIRE_FIST"))
		{
			auto spriteComp = fireFist->getComponents<Sprite>();
			spriteComp->getSprite().setColor({ 255,255,255,150 });
		}
	}
}

void MainMenu::draw()
{
	drawBackGround();
	drawCharacters();
}

void MainMenu::drawUpside()
{
	if (auto _o = getParents().lock())
	{
		_o->getObjects("BLOOD_LEFT")->drawComponents();
		_o->getObjects("BLOOD_RIGHT")->drawComponents();
		_o->getObjects("FIRE_FIST")->drawComponents();
		_o->getObjects("BLOODLUST_FIST")->drawComponents();
	}
	if (m_isBloodLeftPlaced && m_isBloodRightPlaced)
	{
		drawText();
		drawCursor();
		drawLock();
		drawLogoGa();
	}
}

bool MainMenu::getStartCredits()
{
	return m_startCredits;
}

void MainMenu::setStartCredits(bool _start)
{
	m_startCredits = _start;
}

void MainMenu::updateBloodLeft()
{
	if (auto Menu = getParents().lock())
	{
		if (Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getMusic("menumusic").getStatus() == sf::Sound::Stopped)
		Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getMusic("menumusic").play();
		auto bloodLeft = Menu->getObjects("BLOOD_LEFT");

		auto pos = bloodLeft->getComponents<ObjectTransform>()->getPosition();
		sf::Vector2f windowSize = static_cast<sf::Vector2f> (window.getWindow().getSize());
		float posMax = posBloodLeftPlaced.x * windowSize.x;
		if (pos.x < posMax && !m_isBloodLeftPlaced)
		{
			pos.x += bloodSpeed * tools::GetTimeDelta();
			bloodLeft->getComponents<ObjectTransform>()->setPosition(pos);
		}
		else
		{
			bloodLeft->getComponents<ObjectTransform>()->setPosition({ posMax,pos.y });
			m_isBloodLeftPlaced = true;
		}
	}
}

void MainMenu::updateBloodRight()
{
	if (auto Menu = getParents().lock())
	{
		auto bloodRight = Menu->getObjects("BLOOD_RIGHT");

		auto pos = bloodRight->getComponents<ObjectTransform>()->getPosition();
		sf::Vector2f windowSize = static_cast<sf::Vector2f> (window.getWindow().getSize());
		float posMax = posBloodLeftPlaced.x * windowSize.x;
		if (pos.x > posMax && !m_isBloodRightPlaced)
		{
			pos.x -= bloodSpeed * tools::GetTimeDelta();
			bloodRight->getComponents<ObjectTransform>()->setPosition(pos);
		}
		else
		{
			bloodRight->getComponents<ObjectTransform>()->setPosition({ posMax,pos.y });
			m_isBloodRightPlaced = true;
		}
	}
}

void MainMenu::updateCursor()
{

	int tmp_cursor = m_cursorSelect;
	switch (m_cursorSelect)
	{
	case STORY:
		m_posCursor.y = posStory.y;
		break;
		/*case STATS:
			m_posCursor.y = posStats.y;
			break;
		case ACHIEVEMENTS:
			m_posCursor.y = posAchievement.y;
			break;*/
	case OPTIONS:
		m_posCursor.y = posOptions.y;
		break;
	case CREDITS:
		m_posCursor.y = posCredits.y;
		break;
		/*case MEDIA:
			m_posCursor.y = posMedia.y;
			break;*/
	case EXIT:
		m_posCursor.y = posExit.y;
		break;
	default:
		break;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_keyTimer > 0.2)
	{
		if (m_cursorSelect < GA)
		{
			tmp_cursor++;
		}
		else
		{
			tmp_cursor = e_WHAT_IS_SELECTED::STORY;
		}
		m_keyTimer = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_keyTimer > 0.2)
	{
		if (m_cursorSelect > STORY)
		{
			tmp_cursor--;

		}
		else
		{
			tmp_cursor = e_WHAT_IS_SELECTED::GA;
		}
		m_keyTimer = 0;
	}

	if (auto mainMenu = getParents().lock())
	{
		auto Scene = mainMenu->getParent();
		if (auto inputObj = Scene->getObjects("INPUT_J1"))
		{
			if (auto input = inputObj->getComponents<Input>())
			{
				if (input->moveDirection(gpDirection::DOWN) && m_keyTimer > 0.2)
				{
					mainMenu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("menuswitch").play();

					if (m_cursorSelect < GA)
					{
						tmp_cursor++;
					}
					else
					{
						tmp_cursor = e_WHAT_IS_SELECTED::STORY;
					}
					m_keyTimer = 0;
				}
				if (input->moveDirection(gpDirection::UP) && m_keyTimer > 0.2)
				{
					mainMenu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("menuswitch").play();
					if (m_cursorSelect > STORY)
					{
						tmp_cursor--;

					}
					else
					{
						tmp_cursor = e_WHAT_IS_SELECTED::GA;
					}
					m_keyTimer = 0;
				}
			}
		}
	}
	m_cursorSelect = static_cast<e_WHAT_IS_SELECTED>(tmp_cursor);
}

void MainMenu::changeMenu()
{
	if (auto mainMenu = getParents().lock())
	{
		//contrôle manette
		auto Scene = mainMenu->getParent();
		auto inputJ1 = Scene->getObjects("INPUT_J1");
		auto inputJ2 = Scene->getObjects("INPUT_J2");

		auto input = inputJ1->getComponents<Input>();
		if (input->getType(gp::Gamepad::A) == PRESSED && m_keyTimer > 0.2)
		{
			mainMenu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("menuselect").play();

			switch (m_cursorSelect)
			{
			case STORY:
				if (auto selectionMenu = Scene->getObjects("SELECTION_MENU"))
				{
					selectionMenu->getComponents<Selection>()->setInputJ1(inputJ1->getComponents<Input>());
					selectionMenu->getComponents<Selection>()->setInputJ2(inputJ2->getComponents<Input>());
					selectionMenu->setActive(true);
					mainMenu->setActive(false);
				}
				break;
				/*case STATS:
					break;
				case ACHIEVEMENTS:
					break;*/
			case OPTIONS:
				if (auto optionMenu = Scene->getObjects("OPTION_MENU"))
				{
					mainMenu->setActive(false);
					optionMenu->setActive(true);
				}
				break;
			case CREDITS:
				m_startCredits = true;
				break;
				/*case MEDIA:
					break;*/
			case EXIT:
				//window.getWindow().close();
				exit(0);
				break;
			case GA:
				system("start https://www.gameacademy.fr/");
				break;
			default:
				break;
			}
			m_keyTimer = 0;
		}

		//contrôle clavier
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && m_keyTimer > 0.2)
		{
			switch (m_cursorSelect)
			{
			case STORY:
				if (auto selectionMenu = Scene->getObjects("SELECTION_MENU"))
				{
					selectionMenu->getComponents<Selection>()->setInputJ1(inputJ1->getComponents<Input>());
					selectionMenu->getComponents<Selection>()->setInputJ2(inputJ2->getComponents<Input>());
					selectionMenu->setActive(true);
					mainMenu->setActive(false);
				}
				break;
				/*case STATS:
					m_posCursor.y = posStats.y;
					break;
				case ACHIEVEMENTS:
					m_posCursor.y = posAchievement.y;
					break;*/
			case OPTIONS:
				if (auto optionMenu = Scene->getObjects("OPTION_MENU"))
				{
					mainMenu->setActive(false);
					optionMenu->setActive(true);
				}
				m_posCursor.y = posOptions.y;
				break;
			case CREDITS:
				m_startCredits = true;
				m_posCursor.y = posCredits.y;
				break;
				/*	case MEDIA:
						m_posCursor.y = posMedia.y;
						break;*/
			case EXIT:
				exit(0);
				m_posCursor.y = posExit.y;
				break;
			case GA:
				system("start https://www.gameacademy.fr/");
				break;
			default:
				break;
			}
			m_keyTimer = 0;
		}
	}
}

void MainMenu::drawText()
{
	drawTextFirstPart();
	drawTextSecondePart();
}

void MainMenu::drawTextFirstPart()
{
	sf::Text tmp_text;

	tmp_text.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
	tmp_text.setFillColor(sf::Color(230, 230, 230));
	tmp_text.setOutlineColor(sf::Color::Black);
	tmp_text.setOutlineThickness(1.f);

	//text.setStyle(sf::Text::Bold);//simple test

	tmp_text.setCharacterSize(characterSizeFirstPart);

	tmp_text.setString(stringStory);
	tmp_text.setPosition({ posStory.x * window.getSize().x,posStory.y * window.getSize().y });
	if (m_cursorSelect == STORY)
	{
		tmp_text.setFont(RessourceManager::get()->getFont("italique_steelfish.otf"));
		tmp_text.setStyle(sf::Text::Bold);
	}
	else
	{
		tmp_text.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
		tmp_text.setStyle(sf::Text::Regular);
	}
	window.draw(tmp_text);

	tmp_text.setString(stringStats);
	tmp_text.setPosition({ posStats.x * window.getSize().x,posStats.y * window.getSize().y });
	tmp_text.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
	tmp_text.setStyle(sf::Text::Regular);
	/*if (m_cursorSelect == STATS)
	{
		tmp_text.setFont(RessourceManager::get()->getFont("italique_steelfish.otf"));
		tmp_text.setStyle(sf::Text::Bold);
	}
	else
	{
		tmp_text.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
		tmp_text.setStyle(sf::Text::Regular);
	}*/
	window.draw(tmp_text);

	tmp_text.setString(stringAchievement);
	tmp_text.setPosition({ posAchievement.x * window.getSize().x,posAchievement.y * window.getSize().y });
	tmp_text.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
	tmp_text.setStyle(sf::Text::Regular);
	/*if (m_cursorSelect == ACHIEVEMENTS)
	{
		tmp_text.setFont(RessourceManager::get()->getFont("italique_steelfish.otf"));
		tmp_text.setStyle(sf::Text::Bold);
	}
	else
	{
		tmp_text.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
		tmp_text.setStyle(sf::Text::Regular);
	}*/
	window.draw(tmp_text);
}

void MainMenu::drawTextSecondePart()
{
	sf::Text tmp_text;

	tmp_text.setFillColor(sf::Color(230, 230, 230));
	tmp_text.setOutlineColor(sf::Color::Black);

	//text.setOutlineThickness(4.f);

	tmp_text.setCharacterSize(characterSizeSecPart);

	tmp_text.setString(stringOptions);
	tmp_text.setPosition({ posOptions.x * window.getSize().x,posOptions.y * window.getSize().y });
	if (m_cursorSelect == OPTIONS)
	{
		tmp_text.setFont(RessourceManager::get()->getFont("italique_steelfish.otf"));
		tmp_text.setStyle(sf::Text::Bold);
	}
	else
	{
		tmp_text.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
		tmp_text.setStyle(sf::Text::Regular);
	}
	window.draw(tmp_text);

	tmp_text.setString(stringCredits);
	tmp_text.setPosition({ posCredits.x * window.getSize().x,posCredits.y * window.getSize().y });
	if (m_cursorSelect == CREDITS)
	{
		tmp_text.setFont(RessourceManager::get()->getFont("italique_steelfish.otf"));
		tmp_text.setStyle(sf::Text::Bold);
	}
	else
	{
		tmp_text.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
		tmp_text.setStyle(sf::Text::Regular);
	}
	window.draw(tmp_text);

	tmp_text.setString(stringMedia);
	tmp_text.setPosition({ posMedia.x * window.getSize().x,posMedia.y * window.getSize().y });
	tmp_text.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
	tmp_text.setStyle(sf::Text::Regular);
	/*if (m_cursorSelect == MEDIA)
	{
		tmp_text.setFont(RessourceManager::get()->getFont("italique_steelfish.otf"));
		tmp_text.setStyle(sf::Text::Bold);
	}
	else
	{
		tmp_text.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
		tmp_text.setStyle(sf::Text::Regular);
	}*/
	window.draw(tmp_text);

	tmp_text.setString(stringExit);
	tmp_text.setPosition({ posExit.x * window.getSize().x,posExit.y * window.getSize().y });
	if (m_cursorSelect == EXIT)
	{
		tmp_text.setFont(RessourceManager::get()->getFont("italique_steelfish.otf"));
		tmp_text.setStyle(sf::Text::Bold);
	}
	else
	{
		tmp_text.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
		tmp_text.setStyle(sf::Text::Regular);
	}
	window.draw(tmp_text);
}

void MainMenu::drawCursor()
{
	sf::Sprite tmp_sprite;
	if (m_cursorSelect != GA)
	{
		auto texture = RessourceManager::get()->getSceneTexture("Gelule.png");
		texture.setSmooth(true);
		tmp_sprite.setTexture(texture, true);
		tmp_sprite.setPosition({ m_posCursor.x * window.getSize().x,m_posCursor.y * window.getSize().y + 7 });

		if (tmp_sprite.getPosition().y < posOptions.y * window.getSize().y)
		{
			tmp_sprite.setScale({ 0.8,0.8 });
		}
		else
		{
			tmp_sprite.setScale({ 0.5,0.5 });
			tmp_sprite.setPosition({ m_posCursor.x * window.getSize().x + 20 ,m_posCursor.y * window.getSize().y + 7 });
		}
		window.draw(tmp_sprite);
	}
}

void MainMenu::drawLock()
{
	sf::Sprite tmp_sprite;
	auto tmp_texture = RessourceManager::get()->getSceneTexture("cadena.png");
	auto windowSize = window.getSize();
	tmp_sprite.setTexture(tmp_texture, true);
	if (tmp_sprite.getPosition().y < posOptions.y * window.getSize().y)
	{
		tmp_sprite.setScale({ 0.5,0.5 });
		tmp_sprite.setPosition({ m_posCursor.x * window.getSize().x + 20 ,posStats.y * window.getSize().y + 7 });
	}
	else
	{
		tmp_sprite.setScale({ 0.5,0.5 });
		tmp_sprite.setPosition({ m_posCursor.x * window.getSize().x + 20 ,posStats.y * window.getSize().y + 7 });
	}

	tmp_sprite.setScale({ 0.5,0.5 });
	tmp_sprite.setPosition({ m_posCursor.x * window.getSize().x + 20 ,posStats.y * window.getSize().y + 7 });
	window.draw(tmp_sprite);

	tmp_sprite.setPosition({ m_posCursor.x * window.getSize().x + 20 ,posAchievement.y * window.getSize().y + 7 });
	window.draw(tmp_sprite);

	tmp_sprite.setScale({ 0.3,0.3 });
	tmp_sprite.setPosition({ m_posCursor.x * window.getSize().x + 40 ,posMedia.y * window.getSize().y });
	window.draw(tmp_sprite);
}

void MainMenu::drawLogoGa()
{
	sf::Sprite tmp_sprite;
	auto tmp_texture = RessourceManager::get()->getSceneTexture("GA_HD.png");
	tmp_texture.setSmooth(true);
	auto windowSize = window.getSize();
	sf::Vector2f tmp_pos = { posGA.x * windowSize.x, posGA.y * windowSize.y };

	tmp_sprite.setTexture(tmp_texture);
	tmp_sprite.setOrigin(tmp_sprite.getGlobalBounds().width / 2, tmp_sprite.getGlobalBounds().height / 2);
	tmp_sprite.setPosition(tmp_pos);
	if (m_cursorSelect == GA)
	{
		tmp_sprite.setScale({ 1.5,1.5 });
	}

	window.draw(tmp_sprite);
}

void MainMenu::drawBackGround()
{
	sf::Sprite tmp_sprite;

	tmp_sprite.setPosition({ 0.f,0.f });
	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("fond2.png"));
	window.draw(tmp_sprite);
}

void MainMenu::drawCharacters()
{
	sf::Sprite tmp_sprite;

	tmp_sprite.setPosition({ 0.f,0.f });

	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("0kimpah.png"));
	window.draw(tmp_sprite);

	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("1aspi.png"));
	window.draw(tmp_sprite);

	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("2cleaver.png"));
	window.draw(tmp_sprite);

	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("3trasher.png"));
	window.draw(tmp_sprite);

	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("4spiker.png"));
	window.draw(tmp_sprite);

	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("5BB.png"));
	window.draw(tmp_sprite);

	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("6BL.png"));
	window.draw(tmp_sprite);
}
