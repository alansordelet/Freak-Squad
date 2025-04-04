#include "MenuSettings.h"
#include "Sounds3D.h"
MenuSettings::MenuSettings()
{
	m_selected = SETTINGS_SELECTED;
	m_stateMenu = OPTION_MENU;
	m_keyTimer = 0;

	m_volumeSound = 50;
	m_volumeMusic = 50;
}

MenuSettings::~MenuSettings()
{

}

void MenuSettings::update()
{
	//printf("prout");
	m_keyTimer += tools::GetTimeDelta();
	if (m_stateMenu == OPTION_MENU)
	{
		updateOptionsMenu();
	}
	else if (m_stateMenu == SETTINGS_MENU)
	{
		updateSettingsMenu();
	}
	changeMenu();
}

void MenuSettings::draw()
{
	drawBackGround();
	drawBand();
	if (m_stateMenu == OPTION_MENU)
	{
		drawTextOptionMenu();
	}
	else if (m_stateMenu == SETTINGS_MENU)
	{
		drawSettingsMenu();
	}
	else if (m_stateMenu == INPUT_MENU)
	{
		drawInputMenu();
	}
}

void MenuSettings::updateOptionsMenu()
{
	int tmp_cursor = m_selected;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_keyTimer > 0.2)
	{
		if (m_selected < BACK_SELECTED)
		{
			tmp_cursor++;
		}
		else
		{
			tmp_cursor = e_SETTING_SELECTED::SETTINGS_SELECTED;
		}
		m_keyTimer = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_keyTimer > 0.2)
	{
		if (m_selected > SETTINGS_SELECTED)
		{
			tmp_cursor--;

		}
		else
		{
			tmp_cursor = e_SETTING_SELECTED::BACK_SELECTED;
		}
		m_keyTimer = 0;
	}

	if (auto OptionMenu = getParents().lock())
	{
		auto Scene = OptionMenu->getParent();
		if (auto inputObj = Scene->getObjects("INPUT_J1"))
		{
			if (auto input = inputObj->getComponents<Input>())
			{
				if (input->moveDirection(gpDirection::DOWN) && m_keyTimer > 0.2)
				{
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("menuswitch").play();
					}
					if (m_selected < BACK_SELECTED)
					{
						tmp_cursor++;
					}
					else
					{
						tmp_cursor = e_SETTING_SELECTED::SETTINGS_SELECTED;
					}
					m_keyTimer = 0;
				}
				if (input->moveDirection(gpDirection::UP) && m_keyTimer > 0.2)
				{
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("menuswitch").play();
					}
					if (m_selected > SETTINGS_SELECTED)
					{
						tmp_cursor--;

					}
					else
					{
						tmp_cursor = e_SETTING_SELECTED::BACK_SELECTED;
					}
					m_keyTimer = 0;
				}
			}
		}
	}
	m_selected = static_cast<e_SETTING_SELECTED>(tmp_cursor);
}

void MenuSettings::updateSettingsMenu()
{
	if (auto parent = getParents().lock())
	{
		auto scene = parent->getParent();
		if (auto sound = scene->getObjects("sounds"))
		{
			float tmp_volumeSound = sound->getComponents<Audio3D_Manager>()->getVolumeSound();
			float tmp_volumeMusic = sound->getComponents<Audio3D_Manager>()->getVolumeMusic();
			if(tmp_volumeSound >=0&& tmp_volumeSound <=100)
			{
				m_volumeSound = tmp_volumeSound;
			}
			if (tmp_volumeMusic >= 0 && tmp_volumeMusic <= 100)
			{
				m_volumeMusic = tmp_volumeMusic;
			}
			
		}
	}

	updateSettingsMenuController();
	updateSettingsMenuKeyboard();
	
	if (auto parent = getParents().lock())
	{
		auto scene = parent->getParent();
		if (auto sound = scene->getObjects("sounds"))
		{
			sound->getComponents<Audio3D_Manager>()->setAllGlobalVolume(m_volumeSound);
			sound->getComponents<Audio3D_Manager>()->setAllMusicVolume(m_volumeMusic);
		}
	}	
}

void MenuSettings::updateSettingsMenuController()
{
	int tmp_cursor = m_selected;
	if (auto mainMenu = getParents().lock())
	{
		auto Scene = mainMenu->getParent();
		if (auto inputObj = Scene->getObjects("INPUT_J1"))
		{
			if (auto input = inputObj->getComponents<Input>())
			{
				if (input->moveDirection(gpDirection::DOWN) && m_keyTimer > 0.2)
				{
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("menuswitch").play();
					}
					if (m_selected < FULLSCREEN_SELECTED)
					{
						tmp_cursor++;
					}
					else
					{
						tmp_cursor = e_SETTING_SELECTED::MUSIC_SELECTED;
					}
					m_keyTimer = 0;
				}
				if (input->moveDirection(gpDirection::UP) && m_keyTimer > 0.2)
				{
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("menuswitch").play();
					}
					if (m_selected > MUSIC_SELECTED)
					{
						tmp_cursor--;

					}
					else
					{
						tmp_cursor = e_SETTING_SELECTED::FULLSCREEN_SELECTED;
					}
					m_keyTimer = 0;
				}
				if (input->moveDirection(gpDirection::RIGHT)/* && m_keyTimer > 0.2*/)
				{
					if (m_selected == SOUND_SELECTED)
					{
						if (m_volumeSound < 100)
						{
							//m_volumeSound += 10;
							m_volumeSound += 50 * tools::GetTimeDelta();
						}
					}
					else if (m_selected == MUSIC_SELECTED)
					{
						if (m_volumeMusic < 100)
						{
							//m_volumeMusic += 10;
							m_volumeMusic += 50 * tools::GetTimeDelta();
						}
						if (m_volumeMusic > 100)
						{
							//m_volumeMusic += 10;
							m_volumeMusic = 100;
						}
					}
					m_keyTimer = 0;
				}
				if (input->moveDirection(gpDirection::LEFT)/* && m_keyTimer > 0.2*/)
				{
					if (m_selected == SOUND_SELECTED)
					{
						if (m_volumeSound > 0)
						{
							m_volumeSound -= 50 * tools::GetTimeDelta();
						}
						else
						{
							m_volumeSound = 0;
						}
					}
					else if (m_selected == MUSIC_SELECTED)
					{
						if (m_volumeMusic > 0)
						{
							m_volumeMusic -= 50 * tools::GetTimeDelta();
						}
						else
						{
							m_volumeMusic = 0;
						}
					}
					m_keyTimer = 0;
				}
				if (m_selected == FULLSCREEN_SELECTED)
				{
					if (input->getType(gp::Gamepad::A) == PRESSED && m_keyTimer > 0.2)
					{
						if (auto Menu = getParents().lock())
						{
							Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("characterselect").play();
						}
						window.toggleFullScreen();
						m_keyTimer = 0;
					}
				}
			}
		}
	}
	m_selected = static_cast<e_SETTING_SELECTED>(tmp_cursor);
}

void MenuSettings::updateSettingsMenuKeyboard()
{
	int tmp_cursor = m_selected;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_keyTimer > 0.2)
	{
		if (m_selected < FULLSCREEN_SELECTED)
		{
			tmp_cursor++;
		}
		else
		{
			tmp_cursor = e_SETTING_SELECTED::MUSIC_SELECTED;
		}
		m_keyTimer = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_keyTimer > 0.2)
	{
		if (m_selected > MUSIC_SELECTED)
		{
			tmp_cursor--;

		}
		else
		{
			tmp_cursor = e_SETTING_SELECTED::FULLSCREEN_SELECTED;
		}
		m_keyTimer = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)/* && m_keyTimer > 0.2*/)
	{
		if (m_selected == SOUND_SELECTED)
		{
			if (m_volumeSound < 100)
			{
				//m_volumeSound += 10;
				m_volumeSound += 50 * tools::GetTimeDelta();
			}
			else
			{
				m_volumeSound = 100;
			}
		}
		else if (m_selected == MUSIC_SELECTED)
		{
			if (m_volumeMusic < 100)
			{
				//m_volumeMusic += 10;
				m_volumeMusic += 50 * tools::GetTimeDelta();
			}
			else
			{
				m_volumeMusic = 100;
			}
		}
		m_keyTimer = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)/* && m_keyTimer > 0.2*/)
	{
		if (m_selected == SOUND_SELECTED)
		{
			if (m_volumeSound > 0)
			{
				//m_volumeSound -= 10;
				m_volumeSound -= 50 * tools::GetTimeDelta();

			}
			else
			{
				m_volumeSound = 0;
			}
		}
		else if (m_selected == MUSIC_SELECTED)
		{
			if (m_volumeMusic > 0)
			{
				//m_volumeMusic -= 10;
				m_volumeMusic -= 50 * tools::GetTimeDelta();
			}
			else
			{
				m_volumeMusic = 0;
			}
		}
		m_keyTimer = 0;
	}
	if (m_selected == FULLSCREEN_SELECTED)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && m_keyTimer > 0.2)
		{
			window.toggleFullScreen();
			m_keyTimer = 0;
		}
	}
	m_selected = static_cast<e_SETTING_SELECTED>(tmp_cursor);
}

void MenuSettings::changeMenu()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && m_keyTimer > 0.2)
	{
		if (m_stateMenu == OPTION_MENU)
		{
			if (m_selected == SETTINGS_SELECTED)
			{
				m_stateMenu = SETTINGS_MENU;
				m_selected = SOUND_SELECTED;
			}
			if (m_selected == INPUT_SELECTED)
			{
				m_stateMenu = INPUT_MENU;
			}
			if (m_selected == BACK_SELECTED)
			{
				if (auto OptionMenu = getParents().lock())
				{
					auto Scene = OptionMenu->getParent();
					if (auto mainMenu = Scene->getObjects("MAIN_MENU"))
					{
						m_selected = SETTINGS_SELECTED;
						mainMenu->setActive(true);
						OptionMenu->setActive(false);
					}
				}
			}
		}
		m_keyTimer = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_keyTimer > 0.2)
	{
		if (m_stateMenu == SETTINGS_MENU)
		{
			m_selected = SETTINGS_SELECTED;
		}
		else if (m_stateMenu == INPUT_MENU)
		{
			m_selected = INPUT_SELECTED;
		}
		if (m_stateMenu != OPTION_MENU)
		{
			m_stateMenu = OPTION_MENU;
		}		
		else if (m_stateMenu == OPTION_MENU)
		{
			if (auto OptionMenu = getParents().lock())
			{
				auto Scene = OptionMenu->getParent();
				if (auto mainMenu = Scene->getObjects("MAIN_MENU"))
				{
					m_selected = SETTINGS_SELECTED;
					mainMenu->setActive(true);
					OptionMenu->setActive(false);
				}
			}
		}
		m_keyTimer = 0;
	}

	if (auto OptionMenu = getParents().lock())
	{
		auto Scene = OptionMenu->getParent();
		if (auto inputObj = Scene->getObjects("INPUT_J1"))
		{
			if (auto input = inputObj->getComponents<Input>())
			{
				if (input->getType(gp::Gamepad::A) == PRESSED && m_keyTimer > 0.2)
				{
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("characterselect").play();
					}
					if (m_stateMenu == OPTION_MENU)
					{
						if (m_selected == SETTINGS_SELECTED)
						{
							m_stateMenu = SETTINGS_MENU;
							m_selected = SOUND_SELECTED;
						}
						if (m_selected == INPUT_SELECTED)
						{
							m_stateMenu = INPUT_MENU;
						}
						if (m_selected == BACK_SELECTED)
						{
							if (auto OptionMenu = getParents().lock())
							{
								auto Scene = OptionMenu->getParent();
								if (auto mainMenu = Scene->getObjects("MAIN_MENU"))
								{
									mainMenu->setActive(true);
									OptionMenu->setActive(false);
								}
							}
						}
					}
					m_keyTimer = 0;
				}
				if (input->getType(gp::Gamepad::B) == PRESSED && m_keyTimer > 0.2)
				{
					if (auto Menu = getParents().lock())
					{
						Menu->getParent()->getObjects("sounds")->getComponents<Audio3D_Manager>()->getSound3D("back").play();
					}
					if (m_stateMenu == SETTINGS_MENU)
					{
						m_selected = SETTINGS_SELECTED;
					}
					else if (m_stateMenu == INPUT_MENU)
					{
						m_selected = INPUT_SELECTED;
					}
					if (m_stateMenu != OPTION_MENU)
					{
						m_stateMenu = OPTION_MENU;
					}
					else if (m_stateMenu == OPTION_MENU)
					{
						if (auto OptionMenu = getParents().lock())
						{
							auto Scene = OptionMenu->getParent();
							if (auto mainMenu = Scene->getObjects("MAIN_MENU"))
							{
								mainMenu->setActive(true);
								OptionMenu->setActive(false);
							}
						}
					}
					m_keyTimer = 0;
				}
			}
		}
	}

}

void MenuSettings::drawBand()
{
	sf::Sprite tmp_sprite;

	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("page_option.png"));
	tmp_sprite.setPosition({ posBand.x * window.getSize().x - (tmp_sprite.getTexture()->getSize().x / 2),posBand.y * window.getSize().y });
	window.draw(tmp_sprite);
}

void MenuSettings::drawTextOptionMenu()
{
	sf::Text tmp_text;
	tmp_text.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
	tmp_text.setOutlineColor(sf::Color::Black);
	tmp_text.setOutlineThickness(1.f);

	tmp_text.setString(stringSettings);
	if (m_selected == SETTINGS_SELECTED)
	{
		tmp_text.setFont(RessourceManager::get()->getFont("italique_steelfish.otf"));
		tmp_text.setStyle(sf::Text::Bold);
		tmp_text.setCharacterSize(characterBoldSize);
	}
	else
	{
		tmp_text.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
		tmp_text.setStyle(sf::Text::Regular);
		tmp_text.setCharacterSize(characterSize);
	}
	tmp_text.setPosition({ posTextSettings.x * window.getSize().x - (tmp_text.getGlobalBounds().width / 2), posTextSettings.y * window.getSize().y });
	window.draw(tmp_text);


	tmp_text.setString(stringInput);
	if (m_selected == INPUT_SELECTED)
	{
		tmp_text.setFont(RessourceManager::get()->getFont("italique_steelfish.otf"));
		tmp_text.setStyle(sf::Text::Bold);
		tmp_text.setCharacterSize(characterBoldSize);
	}
	else
	{
		tmp_text.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
		tmp_text.setStyle(sf::Text::Regular);
		tmp_text.setCharacterSize(characterSize);
	}
	tmp_text.setPosition({ posTextInput.x * window.getSize().x - (tmp_text.getGlobalBounds().width / 2), posTextInput.y * window.getSize().y });
	window.draw(tmp_text);


	tmp_text.setString(stringBack);
	if (m_selected == BACK_SELECTED)
	{
		tmp_text.setFont(RessourceManager::get()->getFont("italique_steelfish.otf"));
		tmp_text.setStyle(sf::Text::Bold);
		tmp_text.setCharacterSize(characterBoldSize);
	}
	else
	{
		tmp_text.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
		tmp_text.setStyle(sf::Text::Regular);
		tmp_text.setCharacterSize(characterSize);
	}
	tmp_text.setPosition({ posTextBack.x * window.getSize().x - (tmp_text.getGlobalBounds().width / 2), posTextBack.y * window.getSize().y });
	window.draw(tmp_text);
}

void MenuSettings::drawSettingsMenu()
{
	drawBarSound();
	drawBarMusic();
	drawFullscreenLogo();
	drawBackButton();
}

void MenuSettings::drawInputMenu()
{
	sf::Sprite tmp_sprite;
	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("manette_anglais.png"), true);
	tmp_sprite.setPosition({ posCenter.x * window.getSize().x - (tmp_sprite.getTexture()->getSize().x / 2),posCenter.y * window.getSize().y - (tmp_sprite.getTexture()->getSize().y / 2) });
	window.draw(tmp_sprite);

	drawBackButton();
}

void MenuSettings::drawBarSound()
{
	sf::Sprite tmp_sprite;

	if (m_selected == SOUND_SELECTED)
	{
		tmp_sprite.setColor({ 255,255,255 });
	}
	else
	{
		tmp_sprite.setColor({ 128,128,128 });
	}

	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("audio.png"), true);
	tmp_sprite.setPosition({ posLogoSound.x * window.getSize().x, posLogoSound.y * window.getSize().y });
	window.draw(tmp_sprite);

	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("barre.png"), true);
	tmp_sprite.setPosition({ posBarSound.x * window.getSize().x, posBarSound.y * window.getSize().y });
	window.draw(tmp_sprite);

	//curseur de son
	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("curseur_flamme.png"), true);
	float posCursorSoundX = tools::lerp(posCursorSoundMin.x - 0.001, posCursorSoundMax.x, m_volumeSound / 100);
	//float posCursorSoundX = posCursorSoundMin.x;
	tmp_sprite.setPosition({ posCursorSoundX * window.getSize().x, posCursorSoundMin.y * window.getSize().y });
	window.draw(tmp_sprite);
}

void MenuSettings::drawBarMusic()
{
	sf::Sprite tmp_sprite;

	if (m_selected == MUSIC_SELECTED)
	{
		tmp_sprite.setColor({ 255,255,255 });
	}
	else
	{
		tmp_sprite.setColor({ 128,128,128 });
	}

	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("musique.png"), true);
	tmp_sprite.setPosition({ posLogoMusic.x * window.getSize().x, posLogoMusic.y * window.getSize().y });
	window.draw(tmp_sprite);

	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("barre.png"), true);
	tmp_sprite.setPosition({ posBarMusic.x * window.getSize().x, posBarMusic.y * window.getSize().y });

	window.draw(tmp_sprite);

	//curseur de Musique
	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("curseur_oreille.png"), true);
	float posCursorMusicX = tools::lerp(posCursorMusicMin.x - 0.001, posCursorMusicMax.x, m_volumeMusic / 100);//offset de -3 pixel soit 0.001
	//float posCursorMusicX = posCursorMusicMin.x- 0.001;
	tmp_sprite.setPosition({ posCursorMusicX * window.getSize().x, posCursorMusicMin.y * window.getSize().y });
	window.draw(tmp_sprite);
}

void MenuSettings::drawFullscreenLogo()
{
	sf::Sprite tmp_sprite;
	if (window.isFullScreen())
	{
		tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("fullScreen.png"), true);
	}
	else
	{
		tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("fullScreenNo.png"), true);
	}

	if (m_selected == FULLSCREEN_SELECTED)
	{
		tmp_sprite.setColor({ 255,255,255 });
	}
	else
	{
		tmp_sprite.setColor({ 128,128,128 });
	}
	//float posCursorMusicX = tools::lerp(posCursorMusicMin.x, posCursorMusicMax.x, m_volumeMusic / 100);
	tmp_sprite.setPosition({ posFullScreen.x * window.getSize().x - tmp_sprite.getTexture()->getSize().x / 2, posFullScreen.y * window.getSize().y });
	window.draw(tmp_sprite);
}

void MenuSettings::drawBackButton()
{
	sf::Sprite tmp_sprite;
	sf::Texture tmp_textureTouche = RessourceManager::get()->getSceneTexture("touche_b.png");
	sf::Vector2f tmp_posLogoButton{ posBackButton.x * window.getSize().x, posBackButton.y * window.getSize().y };

	sf::Text tmp_text;
	sf::Vector2f tmp_posTextBack = tmp_posLogoButton;

	//draw du sprite
	tmp_sprite.setTexture(tmp_textureTouche, true);
	tmp_sprite.setScale(0.5, 0.5);
	tmp_sprite.setPosition(tmp_posLogoButton);
	window.draw(tmp_sprite);

	//draw du Text
	tmp_posTextBack.x += tmp_sprite.getGlobalBounds().width + 10;
	tmp_posTextBack.y += 10;

	tmp_text.setString(stringBack);
	tmp_text.setPosition(tmp_posTextBack);
	tmp_text.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
	tmp_text.setOutlineColor(sf::Color::Black);
	tmp_text.setOutlineThickness(1.f);
	window.draw(tmp_text);
}

void MenuSettings::drawBackGround()
{
	sf::Sprite tmp_sprite;

	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("enviro_complet3.png"));
	tmp_sprite.setPosition({ 0.f,0.f });
	window.draw(tmp_sprite);

}
