#include "PauseGameCOMP.h"
#include "Sounds3D.h"
#include "Camera.h"
PauseGameCOMP::PauseGameCOMP(std::shared_ptr<GameObject> m_object)
{

	m_NavigationMenu = 1;
	timerKey = 0.0f;
	m_menu_pause = true;
	m_option = false;
	m_commande = false;
	m_ScreenOFF_ON = false;
	m_isDraggingMusic = false;
	m_isDraggingSFX = false;
	m_posEye = { 870.0f, 455.0f };
	m_posOreil = { 870.0f, 605.0f };
	volumeMusic = 0.0f;
	m_volumeMusic = 50.0f;
	m_volumeSound = 50.0f;
	m_keyTimer = 0;
	volumeSFX = 0.0f;
	m_activeGame = false;
	m_selected = MUSIC_SELECTED;
	//m_object = _m_object;
	//TEXTURE
#pragma region fond
	m_spriteFond.setTexture(RessourceManager::get()->getSceneTexture("fon.png"));
	m_spriteFond.setPosition(sf::Vector2f(0.0f, 0.0f));
#pragma endregion fond
#pragma region page_option
	m_spritePage_Option.setTexture(RessourceManager::get()->getSceneTexture("pauseFS.png"));
	m_spritePage_Option.setPosition(sf::Vector2f(548.0f, 0.0f));
#pragma endregion page_option
	//TEXTE
#pragma region BackGame
	m_textBackGame.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
	m_textBackGame.setPosition(sf::Vector2f(960.0f, 400.0f));
	m_textBackGame.setCharacterSize(40);
	m_textBackGame.setString("Resume Game");
	m_textRectBackGame = m_textBackGame.getLocalBounds();
	m_textBackGame.setOrigin(m_textRectBackGame.left + m_textRectBackGame.width / 2.0f,
		m_textRectBackGame.top + m_textRectBackGame.height / 2.0f);
	m_textBackGame.setScale(sf::Vector2f(1.2f,1.2f));
#pragma endregion BackGame
#pragma region Option
	m_textOption.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
	m_textOption.setPosition(sf::Vector2f(960.0f, 540.0f));
	m_textOption.setCharacterSize(40);
	m_textOption.setString("Options");
	m_textRectOption = m_textOption.getLocalBounds();
	m_textOption.setOrigin(m_textRectOption.left + m_textRectOption.width / 2.0f,
		m_textRectOption.top + m_textRectOption.height / 2.0f);
	m_textOption.setScale(sf::Vector2f(1.2f, 1.2f));
#pragma endregion Option
#pragma region Commande
	m_textCommande.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
	m_textCommande.setPosition(sf::Vector2f(960.0f, 630.0f));
	m_textCommande.setCharacterSize(40);
	m_textCommande.setString("Commands");
	m_textRectCommande = m_textCommande.getLocalBounds();
	m_textCommande.setOrigin(m_textRectCommande.left + m_textRectCommande.width / 2.0f,
		m_textRectCommande.top + m_textRectCommande.height / 2.0f);
	m_textCommande.setScale(sf::Vector2f(1.2f, 1.2f));
#pragma endregion Commande
#pragma region Quitter
	m_textQuitter.setFont(RessourceManager::get()->getFont("steelfish2.otf"));
	m_textQuitter.setPosition(sf::Vector2f(960.0f, 790.0f));
	m_textQuitter.setCharacterSize(40);
	m_textQuitter.setString("Quit");
	m_textRectQuitter = m_textQuitter.getLocalBounds();
	m_textQuitter.setOrigin(m_textRectQuitter.left + m_textRectQuitter.width / 2.0f,
		m_textRectQuitter.top + m_textRectQuitter.height / 2.0f);
	m_textQuitter.setScale(sf::Vector2f(1.2f, 1.2f));
#pragma endregion Quitter
	//OPTION
#pragma region InOption
	m_spriteMusique.setTexture(RessourceManager::get()->getSceneTexture("musique.png"));
	m_spriteMusique.setPosition(sf::Vector2f(800.0f, 470.0f));
	m_spriteMusique.setOrigin(sf::Vector2f(68 / 2, 71 / 2));
	m_spriteBarMusique.setTexture(RessourceManager::get()->getSceneTexture("barre.png"));
	m_spriteBarMusique.setPosition(sf::Vector2f(880.0f, 470.0f));
	m_spriteEye.setTexture(RessourceManager::get()->getSceneTexture("curseur_oeil.png"));
	m_spriteEye.setPosition(m_posEye);

	m_spriteSFX.setTexture(RessourceManager::get()->getSceneTexture("audio.png"));
	m_spriteSFX.setPosition(sf::Vector2f(800.0f, 620.0f));
	m_spriteSFX.setOrigin(sf::Vector2f(78 / 2, 53 / 2));
	m_spriteBarSFX.setTexture(RessourceManager::get()->getSceneTexture("barre.png"));
	m_spriteBarSFX.setPosition(sf::Vector2f(880.0f, 620.0f));
	m_spriteOreil.setTexture(RessourceManager::get()->getSceneTexture("curseur_oreille.png"));
	m_spriteOreil.setPosition(m_posOreil);

	m_spriteFullScreenOFF.setTexture(RessourceManager::get()->getSceneTexture("fenetre2.png"));
	m_spriteFullScreenOFF.setPosition(sf::Vector2f(965.0f, 750.0f));
	m_spriteFullScreenOFF.setOrigin(sf::Vector2f(117 / 2, 90 / 2));
	m_spriteFullScreenON.setTexture(RessourceManager::get()->getSceneTexture("fentre.png"));
	m_spriteFullScreenON.setPosition(sf::Vector2f(975.0f, 754.0f));
	m_spriteFullScreenON.setOrigin(sf::Vector2f(103 / 2, 86 / 2));
#pragma endregion InOption
	//COMMANDE
#pragma region InCommande
	m_spriteCommade.setTexture(RessourceManager::get()->getSceneTexture("manette.png"));
	m_spriteCommade.setPosition(sf::Vector2f(650.0f, 350.0f));
#pragma endregion InCommande
}

PauseGameCOMP::~PauseGameCOMP()
{
}

void PauseGameCOMP::update()
{

}

void PauseGameCOMP::update2()
{
	if (m_activeGame)
	{
		if (auto input = sp_input.lock())
		{
			timerKey += tools::GetTimeDelta();
			m_textRectBackGame = m_textBackGame.getLocalBounds();
			m_textRectOption = m_textOption.getLocalBounds();
			m_textRectCommande = m_textCommande.getLocalBounds();
			m_textRectQuitter = m_textQuitter.getLocalBounds();

			input->update();

#pragma region select
			m_textBackGame.setOrigin(m_textRectBackGame.left + m_textRectBackGame.width / 2.0f,
				m_textRectBackGame.top + m_textRectBackGame.height / 2.0f);

			m_textOption.setOrigin(m_textRectOption.left + m_textRectOption.width / 2.0f,
				m_textRectOption.top + m_textRectOption.height / 2.0f);

			m_textCommande.setOrigin(m_textRectCommande.left + m_textRectCommande.width / 2.0f,
				m_textRectCommande.top + m_textRectCommande.height / 2.0f);

			m_textQuitter.setOrigin(m_textRectQuitter.left + m_textRectQuitter.width / 2.0f,
				m_textRectQuitter.top + m_textRectQuitter.height / 2.0f);
#pragma endregion select

			if (m_option == true && input->getType(gp::Gamepad::B) == PRESSED && timerKey >= 0.2f)
			{
				m_NavigationMenu = 1;
				m_option = false;
				m_menu_pause = true;
				timerKey = 0.0f;
			}
			if (m_commande == true && input->getType(gp::Gamepad::B) == PRESSED && timerKey >= 0.2f)
			{
				m_NavigationMenu = 1;
				m_commande = false;
				m_menu_pause = true;
				timerKey = 0.0f;
			}

#pragma region InOption
			if (input->getType(gp::Gamepad::A) == PRESSED && timerKey >= 0.2f)
			{
				if (m_NavigationMenu == 7)
				{
					WindowManager::getInstance()->getWindow()->toggleFullScreen();
					m_ScreenOFF_ON = !m_ScreenOFF_ON;
					timerKey = 0.0f;
				}
			}

			if (m_option == true)
			{

				/*if (auto parent = getParents().lock())
				{
					if (auto sound = parent->getComponents<Audio3D_Manager>())
					{
						volumeSFX = sound->getVolumeSound();
						volumeMusic = sound->getVolumeMusic();
					}
				}

				if (input->getStickLeft().x > +50.0f && m_posEye.x < 1100.f && m_NavigationMenu == 5)
				{
					m_posEye.x += 100.0f * tools::GetTimeDelta();
					m_isDraggingMusic = true;
				}
				if (input->getStickLeft().x < -50.0f && m_posEye.x > 869.5f && m_NavigationMenu == 5)
				{
					m_posEye.x -= 100.0f * tools::GetTimeDelta();
					m_isDraggingMusic = true;
				}
				if (input->getStickLeft().x > +50.0f && m_posOreil.x < 1100.f && m_NavigationMenu == 6)
				{
					m_posOreil.x += 100.0f * tools::GetTimeDelta();
					m_isDraggingSFX = true;
				}
				if (input->getStickLeft().x < -50.0f && m_posOreil.x > 869.5f && m_NavigationMenu == 6)
				{
					m_posOreil.x -= 100.0f * tools::GetTimeDelta();
					m_isDraggingSFX = true;
				}
				if (!input->getStickLeft().x > +50.0f && !input->getStickLeft().y < -50.0f)
				{
					m_isDraggingMusic = false;
					m_isDraggingSFX = false;
				}

				if (m_isDraggingMusic == true)
				{
					float x = m_posEye.x;
					if (x < 869.5f)
						x = 869.5f;
					else if (x > 1100.f)
						x = 1100.f;

					volumeMusic = (x - 869.5f) / 350.f;
					m_spriteEye.setPosition(x, m_posEye.y);
				}

				if (m_isDraggingSFX == true)
				{
					float x = m_posOreil.x;
					if (x < 869.5f)
						x = 869.5f;
					else if (x > 1100.f)
						x = 1100.f;

					volumeSFX = (x - 869.5f) / 350.f;
					m_spriteOreil.setPosition(x, m_posOreil.y);

				}

				}*/
				if (auto parent = getParents().lock())
				{
					m_keyTimer += tools::GetTimeDelta();
					auto scene = parent->getParent();
					if (auto sound = scene->getObjects("gameMusic"))
					{
						float tmp_volumeSound = sound->getComponents<Audio3D_Manager>()->getVolumeSound();
						float tmp_volumeMusic = sound->getComponents<Audio3D_Manager>()->getVolumeMusic();
						if (tmp_volumeSound >= 0 && tmp_volumeSound <= 100)
						{
							m_volumeSound = tmp_volumeSound;
						}
						if (tmp_volumeMusic >= 0 && tmp_volumeMusic <= 100)
						{
							m_volumeMusic = tmp_volumeMusic;
						}
					}

					updateSettingsMenuController();

					if (auto parent = getParents().lock())
					{
						auto scene = parent->getParent();
						if (auto sound = scene->getObjects("gameMusic"))
						{
							sound->getComponents<Audio3D_Manager>()->setAllGlobalVolume(m_volumeSound);
							sound->getComponents<Audio3D_Manager>()->setAllMusicVolume(m_volumeMusic);
						}
					}
				}



				//music.setVolume(volumeMusic * 100);
			}

#pragma endregion InOption

			if (m_NavigationMenu == 1)
			{
				m_textBackGame.setScale(sf::Vector2f(1.4f, 1.4f));
				if (input->getType(gp::Gamepad::A) == PRESSED && timerKey >= 0.2f)
				{
					m_NavigationMenu = 1;
					m_activeGame = false;
					timerKey = 0.0f;
					sp_input.reset();
					return;
				}
			}
			else
			{
				m_textBackGame.setScale(sf::Vector2f(1.2f, 1.2f));
			}
			if (m_NavigationMenu == 2)
			{
				m_textOption.setScale(sf::Vector2f(1.4f, 1.4f));
				if (input->getType(gp::Gamepad::A) == PRESSED && m_commande == false)
				{
					m_NavigationMenu = 5;
					m_menu_pause = false;
					m_option = true;
				}
			}
			else
			{
				m_textOption.setScale(sf::Vector2f(1.2f, 1.2f));
			}
			if (m_NavigationMenu == 3)
			{
				m_textCommande.setScale(sf::Vector2f(1.4f, 1.4f));
				if (input->getType(gp::Gamepad::A) == PRESSED && m_option == false)
				{
					m_menu_pause = false;
					m_commande = true;
				}
			}
			else
			{
				m_textCommande.setScale(sf::Vector2f(1.2f, 1.2f));
			}
			if (m_NavigationMenu == 4)
			{
				m_textQuitter.setScale(sf::Vector2f(1.4f, 1.4f));
			}
			else
			{
				m_textQuitter.setScale(sf::Vector2f(1.2f, 1.2f));
			}
			if (m_NavigationMenu == 5)
			{
				m_spriteMusique.setScale(sf::Vector2f(1.35f, 1.35f));
			}
			else
			{
				m_spriteMusique.setScale(sf::Vector2f(1.0f, 1.0f));
			}
			if (m_NavigationMenu == 6)
			{
				m_spriteSFX.setScale(sf::Vector2f(1.35f, 1.35f));
			}
			else
			{
				m_spriteSFX.setScale(sf::Vector2f(1.0f, 1.0f));
			}
			if (m_NavigationMenu == 7)
			{
				m_spriteFullScreenOFF.setScale(sf::Vector2f(1.35f, 1.35f));
				m_spriteFullScreenON.setScale(sf::Vector2f(1.35f, 1.35f));
			}
			else
			{
				m_spriteFullScreenOFF.setScale(sf::Vector2f(1.0f, 1.0f));
				m_spriteFullScreenON.setScale(sf::Vector2f(1.0f, 1.0f));
			}

			if (m_NavigationMenu == 1 && input->getStickLeft().y < -50.0f && timerKey >= 0.2f)
			{
				m_NavigationMenu = 2;
				timerKey = 0.0f;
			}
			if (m_NavigationMenu == 2 && input->getStickLeft().y > +50.0f && timerKey >= 0.2f)
			{
				m_NavigationMenu = 1;
				timerKey = 0.0f;
			}
			if (m_NavigationMenu == 2 && input->getStickLeft().y < -50.0 && timerKey >= 0.2f)
			{
				m_NavigationMenu = 3;
				timerKey = 0.0f;
			}
			if (m_NavigationMenu == 3 && input->getStickLeft().y > +50.0f && timerKey >= 0.2f)
			{
				m_NavigationMenu = 2;
				timerKey = 0.0f;
			}
			if (m_NavigationMenu == 3 && input->getStickLeft().y < -50.0f && timerKey >= 0.2f)
			{
				m_NavigationMenu = 4;
				timerKey = 0.0f;
			}
			if (m_NavigationMenu == 4 && input->getStickLeft().y > +50.0f && timerKey >= 0.2f)
			{
				m_NavigationMenu = 3;
				timerKey = 0.0f;
			}
			if (m_NavigationMenu == 5 && input->getStickLeft().y < -50.0f && timerKey >= 0.2f)
			{
				m_NavigationMenu = 6;
				timerKey = 0.0f;
			}
			if (m_NavigationMenu == 6 && input->getStickLeft().y > +50.0f && timerKey >= 0.2f)
			{
				m_NavigationMenu = 5;
				timerKey = 0.0f;
			}
			if (m_NavigationMenu == 6 && input->getStickLeft().y < -50.0f && timerKey >= 0.2f)
			{
				m_NavigationMenu = 7;
				timerKey = 0.0f;
			}
			if (m_NavigationMenu == 7 && input->getStickLeft().y > +50.0f && timerKey >= 0.2f)
			{
				m_NavigationMenu = 6;
				timerKey = 0.0f;
			}
		}
	}
}

void PauseGameCOMP::updateSettingsMenuController()
{
	int tmp_cursor = m_selected;
	if (auto mainMenu = getParents().lock())
	{
		auto Scene = mainMenu->getParent();
		if (auto inputObj = Scene->getObjects("Player"))
		{
			if (auto input = inputObj->getComponents<Input>())
			{
				if (input->moveDirection(gpDirection::DOWN) && m_keyTimer > 0.2)
				{
					if (m_selected < FULLSCREEN_SELECTED)
					{
						tmp_cursor++;
					}
					else
					{
						tmp_cursor = e_SETTING_SELECTED2::MUSIC_SELECTED;
					}
					m_keyTimer = 0;
				}
				if (input->moveDirection(gpDirection::UP) && m_keyTimer > 0.2)
				{
					if (m_selected > MUSIC_SELECTED)
					{
						tmp_cursor--;

					}
					else
					{
						tmp_cursor = e_SETTING_SELECTED2::FULLSCREEN_SELECTED;
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
						window.toggleFullScreen();
						m_keyTimer = 0;
					}
				}
			}
		}
		if (auto inputObj = Scene->getObjects("Player2"))
		{
			if (auto input = inputObj->getComponents<Input>())
			{
				if (input->moveDirection(gpDirection::DOWN) && m_keyTimer > 0.2)
				{
					if (m_selected < FULLSCREEN_SELECTED)
					{
						tmp_cursor++;
					}
					else
					{
						tmp_cursor = e_SETTING_SELECTED2::MUSIC_SELECTED;
					}
					m_keyTimer = 0;
				}
				if (input->moveDirection(gpDirection::UP) && m_keyTimer > 0.2)
				{
					if (m_selected > MUSIC_SELECTED)
					{
						tmp_cursor--;

					}
					else
					{
						tmp_cursor = e_SETTING_SELECTED2::FULLSCREEN_SELECTED;
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
						window.toggleFullScreen();
						m_keyTimer = 0;
					}
				}
			}
		}
	}
	m_selected = static_cast<e_SETTING_SELECTED2>(tmp_cursor);
}

void PauseGameCOMP::draw()
{
	if (m_activeGame)
	{
		sf::View tmpview = window.getWindow().getView();
		window.getWindow().setView(window.getWindow().getDefaultView());
		//TEXTURE
		window.draw(m_spriteFond);
		window.draw(m_spritePage_Option);
		//TEXTE
		if (m_menu_pause == true)
		{
			window.draw(m_textBackGame);
			window.draw(m_textOption);
			window.draw(m_textCommande);
			window.draw(m_textQuitter);
		}
		if (m_option == true)
		{
			/*window.draw(m_spriteBarMusique);
			window.draw(m_spriteMusique);
			window.draw(m_spriteEye);
			window.draw(m_spriteBarSFX);
			window.draw(m_spriteSFX);
			window.draw(m_spriteOreil);

			if (m_ScreenOFF_ON == false)
				window.draw(m_spriteFullScreenOFF);
			else
				window.draw(m_spriteFullScreenON);*/

			drawBarMusic();
			drawBarSound();
			drawFullscreenLogo();
			drawBackButton();
		}

		if (m_commande == true)
			window.draw(m_spriteCommade);
		
		window.getWindow().setView(tmpview);
	}
}

void PauseGameCOMP::setControlePause(std::shared_ptr<Input> _sp_input)
{
	sp_input = _sp_input;
}

void PauseGameCOMP::drawBackButton()
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
void PauseGameCOMP::drawBarSound()
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

void PauseGameCOMP::drawBarMusic()
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

void PauseGameCOMP::drawFullscreenLogo()
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