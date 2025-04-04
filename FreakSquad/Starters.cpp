#include "Starters.h"
#include "Camera.h"
#include "Physique.h"
#include "Sounds3D.h"
#include "Ui_Player.h"
bool reverseBool(bool value)
{
	return !value;
}

Starters::Starters()
{
	m_switchDescription = 0;

	m_screenLeft.setTexture(RessourceManager::get()->getSceneTexture("ecran_gauche.png"));
	m_screenLeft.setPosition(882, 275);

	m_screenRight.setTexture(RessourceManager::get()->getSceneTexture("ecran_droite.png"));
	m_screenRight.setPosition(2755, 328);

	m_startGlow.setTexture(RessourceManager::get()->getSceneTexture("glow_start_tuto.png"));
	m_startGlow.setPosition(745, 300);

	//BUTTONS
	for (int i = 0; i < 6; i++)
	{
		m_buttonX.push_back(sf::Sprite());
		m_buttonX[i].setTexture(RessourceManager::get()->getSceneTexture("touche_b.png"));
		m_buttonX[i].setScale(0.4, 0.4);
	}

	m_buttonX[0].setPosition(2095, 90);
	m_buttonX[1].setPosition(2272, 90);
	m_buttonX[2].setPosition(2432, 90);
	m_buttonX[3].setPosition(2590, 90);
	m_buttonX[4].setPosition(1040, 360);



	for (int i = 0; i < 19; i++)
	{
		m_spriteStartersSoute.push_back(sf::Sprite());
		m_spriteStartersSoute[i].setScale(0.5, 0.5);
	}

	//STARTERS ON WALL
	m_spriteStartersSoute[0].setTexture(RessourceManager::get()->getSceneTexture("degat_cadre_color.png"));
	m_spriteStartersSoute[0].setPosition(2045, 110);

	m_spriteStartersSoute[1].setTexture(RessourceManager::get()->getSceneTexture("vie_cadre_color.png"));
	m_spriteStartersSoute[1].setPosition(2220, 110);

	m_spriteStartersSoute[2].setTexture(RessourceManager::get()->getSceneTexture("score_cadre_color.png"));
	m_spriteStartersSoute[2].setPosition(2380, 110);

	m_spriteStartersSoute[3].setTexture(RessourceManager::get()->getSceneTexture("ulti_cadre_color.png"));
	m_spriteStartersSoute[3].setPosition(2540, 110);

	m_spriteStartersSoute[4].setTexture(RessourceManager::get()->getSceneTexture("degat_no_color.png"));
	m_spriteStartersSoute[4].setPosition(2045, 110);

	m_spriteStartersSoute[5].setTexture(RessourceManager::get()->getSceneTexture("vie_no_color.png"));
	m_spriteStartersSoute[5].setPosition(2220, 110);

	m_spriteStartersSoute[6].setTexture(RessourceManager::get()->getSceneTexture("score_no_color.png"));
	m_spriteStartersSoute[6].setPosition(2380, 110);

	m_spriteStartersSoute[7].setTexture(RessourceManager::get()->getSceneTexture("ult_no_color.png"));
	m_spriteStartersSoute[7].setPosition(2540, 110);

	m_spriteStartersSoute[8].setTexture(RessourceManager::get()->getSceneTexture("degat_choisi.png"));
	m_spriteStartersSoute[8].setPosition(2045, 110);

	m_spriteStartersSoute[9].setTexture(RessourceManager::get()->getSceneTexture("vie_choisi.png"));
	m_spriteStartersSoute[9].setPosition(2220, 110);

	m_spriteStartersSoute[10].setTexture(RessourceManager::get()->getSceneTexture("score_choisi.png"));
	m_spriteStartersSoute[10].setPosition(2380, 110);

	m_spriteStartersSoute[11].setTexture(RessourceManager::get()->getSceneTexture("ulti_choisi.png"));
	m_spriteStartersSoute[11].setPosition(2540, 110);

	m_spriteStartersSoute[12].setTexture(RessourceManager::get()->getSceneTexture("degat_color.png"));
	m_spriteStartersSoute[12].setPosition(2765, 350);

	m_spriteStartersSoute[13].setTexture(RessourceManager::get()->getSceneTexture("vie_color.png"));
	m_spriteStartersSoute[13].setPosition(2765, 350);

	m_spriteStartersSoute[14].setTexture(RessourceManager::get()->getSceneTexture("score_color.png"));
	m_spriteStartersSoute[14].setPosition(2765, 350);

	m_spriteStartersSoute[15].setTexture(RessourceManager::get()->getSceneTexture("ulti_color.png"));
	m_spriteStartersSoute[15].setPosition(2765, 350);

	m_spriteStartersSoute[16].setTexture(RessourceManager::get()->getSceneTexture("petit_ecran.png"));
	m_spriteStartersSoute[16].setPosition(2893, 211);

	m_spriteStartersSoute[17].setTexture(RessourceManager::get()->getSceneTexture("b_to_change_info.png"));
	m_spriteStartersSoute[17].setPosition(2903, 225);

	m_spriteStartersSoute[18].setTexture(RessourceManager::get()->getSceneTexture("cadre_consignes_tuto.png"));
	m_spriteStartersSoute[18].setScale(1.f, 1.f);

	m_spriteStartersSoute[18].setTexture(RessourceManager::get()->getSceneTexture("cadre_consignes_tuto.png"));
	m_spriteStartersSoute[18].setScale(1.f, 1.f);
	///RIGHT SCREEN

	m_textsSoute.push_back(sf::Text("Start Tutorial", RessourceManager::get()->getFont("steelfishNormal.otf"), 300));
	m_textsSoute.push_back(sf::Text("Gain More Score", RessourceManager::get()->getFont("steelfishNormal.otf"), 300));
	m_textsSoute.push_back(sf::Text("but do less dmg", RessourceManager::get()->getFont("steelfishNormal.otf"), 300));
	m_textsSoute.push_back(sf::Text("Do more dmg", RessourceManager::get()->getFont("steelfishNormal.otf"), 300));
	m_textsSoute.push_back(sf::Text("but receive more dmg", RessourceManager::get()->getFont("steelfishNormal.otf"), 300));
	m_textsSoute.push_back(sf::Text("Ultimate Charges", RessourceManager::get()->getFont("steelfishNormal.otf"), 300));
	m_textsSoute.push_back(sf::Text("Faster but is", RessourceManager::get()->getFont("steelfishNormal.otf"), 300));
	m_textsSoute.push_back(sf::Text("cancelled when hit", RessourceManager::get()->getFont("steelfishNormal.otf"), 300));
	m_textsSoute.push_back(sf::Text("Additional life", RessourceManager::get()->getFont("steelfishNormal.otf"), 300));
	m_textsSoute.push_back(sf::Text("but no ultimate", RessourceManager::get()->getFont("steelfishNormal.otf"), 300)); // 9th
	m_textsSoute[0].setPosition(1000, 300);
	m_textsSoute[0].setCharacterSize(37);
	m_textsSoute[1].setPosition(2845, 355);
	m_textsSoute[1].setCharacterSize(30);
	m_textsSoute[2].setPosition(2845, 385);
	m_textsSoute[2].setCharacterSize(30);
	m_textsSoute[3].setPosition(2852, 355);
	m_textsSoute[3].setCharacterSize(25);
	m_textsSoute[4].setPosition(2852, 385);
	m_textsSoute[4].setCharacterSize(25);
	m_textsSoute[5].setPosition(2845, 350);
	m_textsSoute[5].setCharacterSize(25);
	m_textsSoute[6].setPosition(2845, 375);
	m_textsSoute[6].setCharacterSize(25);
	m_textsSoute[7].setPosition(2845, 400);
	m_textsSoute[7].setCharacterSize(25);
	m_textsSoute[8].setPosition(2847, 355);
	m_textsSoute[8].setCharacterSize(30);
	m_textsSoute[9].setPosition(2847, 385);
	m_textsSoute[9].setCharacterSize(30);

	for (auto n : m_textsSoute)
	{
		n.setFillColor(sf::Color(255, 255, 255, 255));
	}

	for (int i = 0; i < 7; i++)
	{
		m_inputs.push_back(sf::Sprite());
		m_inputs[i].setScale(0.25, 0.25);
	}


	for (int i = 0; i < 2; i++)
		m_inputs[i].setTexture(RessourceManager::get()->getSceneTexture("touche_x.png"));
	m_inputs[2].setTexture(RessourceManager::get()->getSceneTexture("touche_a.png"));
	m_inputs[3].setTexture(RessourceManager::get()->getSceneTexture("touche_x.png"));
	m_inputs[4].setTexture(RessourceManager::get()->getSceneTexture("touche_y.png"));
	m_inputs[5].setTexture(RessourceManager::get()->getSceneTexture("touche_rb.png"));

	m_textsSoute.push_back(sf::Text("to hit", RessourceManager::get()->getFont("steelfishNormal.otf"), 300));// 10th
	m_textsSoute.push_back(sf::Text("Hold                  to power hit", RessourceManager::get()->getFont("steelfishNormal.otf"), 300));
	m_textsSoute.push_back(sf::Text("to jump", RessourceManager::get()->getFont("steelfishNormal.otf"), 300));
	m_textsSoute.push_back(sf::Text("while jumping for jump-attack", RessourceManager::get()->getFont("steelfishNormal.otf"), 300));
	m_textsSoute.push_back(sf::Text("for ultimate attack when fully charged", RessourceManager::get()->getFont("steelfishNormal.otf"), 300));
	m_textsSoute.push_back(sf::Text("for boost delivery (costs score)", RessourceManager::get()->getFont("steelfishNormal.otf"), 300));//15th
	m_textsSoute.push_back(sf::Text("End Tutorial", RessourceManager::get()->getFont("steelfishNormal.otf"), 300));
	m_textsSoute[16].setPosition(1000, 300);
	m_textsSoute[16].setCharacterSize(37);
	m_startTuto = false;
	m_nbHOLO = -1;
}

Starters::~Starters()
{

}

void Starters::setSpriteStartersSouteTexture(int index)
{
	m_timerTuto += tools::GetTimeDelta();
	m_timerB += tools::GetTimeDelta();
	if (m_switchDescription > 3)
		m_switchDescription = 0;

	if (auto parent = getParents().lock())
	{
		if (auto BigBoy = getParents().lock()->getParent()->getObjects("gameMusic"))
		{
			BigBoy->getComponents<Audio3D_Manager>()->getSound3D("text").stop();
		}

		if (auto player = parent->getParent()->getObjects(PLAYER))
		{
			for (auto player : GameObject::l_Player)
			{
				auto position = player->getComponents<ObjectTransform>()->getPosition();
				m_buttonX[5].setPosition(position.x - 50, position.y - 550);


				//DESCRIPTION STARTERS
				if (position.y < 800)
				{
					if (position.x > 2700 && position.x < 3100)
					{
						float posy = 225 + 5 * std::sin(m_incrementation * 0.2);
						m_spriteStartersSoute[17].setPosition(2903, posy);
						m_incrementation += tools::GetTimeDelta() * 10.f;

						if (auto input = player->getComponents<Input>())
						{
							if (input->getType(gp::Gamepad::B) == PRESSED && m_timerTuto > 0.5)
							{
								parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("switchscreen").play();
								m_switchDescription += 1;
								m_timerTuto = 0;
							}
						}
					}

					if (position.x > 800 && position.x < 1250)
					{
						float posy = 360 + 5 * std::sin(m_incrementation * 0.2);
						m_buttonX[4].setPosition(1040, posy);
						m_incrementation += tools::GetTimeDelta() * 10.f;

						if (auto input = player->getComponents<Input>())
						{
							if (input->getType(gp::Gamepad::B) == PRESSED && m_timerTuto > 0.5)
							{

								if (m_startTuto == false)
								{
									parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("starttuto").play();
									m_nbHOLO += 1;
									m_startTuto = true;
									m_spawnHOLO = true;
								}
								else
								{
									parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("deadholo").play();
									m_startTuto = false;
									parent->getParent()->getObjects("trasherH" + std::to_string(m_nbHOLO))->setActive(false);
									m_spawnHOLO = false;
								}

								m_timerTuto = 0;
							}
						}
					}
				}

				//STARTERS
				if (position.y < 750)
				{
					auto spritePosition = m_spriteStartersSoute[index].getPosition().x;
					auto spriteWidth = m_spriteStartersSoute[index].getGlobalBounds().width;
					if (position.x > spritePosition && position.x < spritePosition + spriteWidth / 1.5)
					{
						window.draw(m_spriteStartersSoute[index]);
						window.draw(m_buttonX[index]);

						if (auto input = player->getComponents<Input>())
						{
							if (input->getType(gp::Gamepad::B) == PRESSED)
							{
								parent->getParent()->getObjects("gameMusic")->getComponents<Audio3D_Manager>()->getSound3D("boost").play();
								if (player->getComponents<Identity>()->getName() == "Player")
								{

									if (index == 0 && DegatStarterBB == false && VieStarterBB == false && ScoreStarterBB == false && UltiStarterBB == false && DegatStarterBL == false)
									{
										parent->getParent()->getObjects("Player")->getComponents<Physique>()->Starter = DamageDoubleTranchant;
										DegatStarterBB = true;

									}
									else if (index == 0 && DegatStarterBB == true)
									{
										parent->getParent()->getObjects("Player")->getComponents<Physique>()->Starter = NoStater;
										DegatStarterBB = false;
									}

									if (index == 1 && VieStarterBB == false && DegatStarterBB == false && ScoreStarterBB == false && UltiStarterBB == false && VieStarterBL == false)
									{
										parent->getParent()->getObjects("Player")->getComponents<Physique>()->Revive = 1;
										parent->getParent()->getObjects("Player")->getComponents<Physique>()->Starter = VieBonusNoUlti;
										if(auto p = getParents().lock())
											if (auto ui = p->getObjects("LIFEBAR_UI"))
											{
												ui->getComponents<Lifebar>()->setBonusLife(true);
											}
										VieStarterBB = true;
									}
									else if (index == 1 && VieStarterBB == true)
									{
										parent->getParent()->getObjects("Player")->getComponents<Physique>()->Revive = 0;
										parent->getParent()->getObjects("Player")->getComponents<Physique>()->Starter = NoStater;
										VieStarterBB = false;
									}

									if (index == 2 && ScoreStarterBB == false && DegatStarterBB == false && VieStarterBB == false && UltiStarterBB == false && ScoreStarterBL == false)
									{
										parent->getParent()->getObjects("Player")->getComponents<Physique>()->Starter = ScoreBonusMalusDegat;
										ScoreStarterBB = true;
									}
									else if (index == 2 && ScoreStarterBB == true)
									{
										parent->getParent()->getObjects("Player")->getComponents<Physique>()->Starter = NoStater;
										ScoreStarterBB = false;
									}

									if (index == 3 && UltiStarterBB == false && DegatStarterBB == false && VieStarterBB == false && ScoreStarterBB == false && UltiStarterBL == false)
									{
										parent->getParent()->getObjects("Player")->getComponents<Physique>()->Starter = BonusUltimeCanceled;
										UltiStarterBB = true;
									}
									else if (index == 3 && UltiStarterBB == true)
									{
										parent->getParent()->getObjects("Player")->getComponents<Physique>()->Starter = NoStater;
										UltiStarterBB = false;
									}


								}
								//L
								if (player->getComponents<Identity>()->getName() == "Player2")
								{
									if (index == 0 && DegatStarterBL == false && VieStarterBL == false && ScoreStarterBL == false && UltiStarterBL == false && DegatStarterBB == false)
									{
										parent->getParent()->getObjects("Player2")->getComponents<Physique>()->Starter = DamageDoubleTranchant;
										DegatStarterBL = true;

									}
									else if (index == 0 && DegatStarterBL == true)
									{
										parent->getParent()->getObjects("Player2")->getComponents<Physique>()->Starter = NoStater;
										DegatStarterBL = false;
									}

									if (index == 1 && VieStarterBL == false && DegatStarterBL == false && ScoreStarterBL == false && UltiStarterBL == false && VieStarterBB == false)
									{
										parent->getParent()->getObjects("Player2")->getComponents<Physique>()->Revive = 1;
										parent->getParent()->getObjects("Player2")->getComponents<Physique>()->Starter = VieBonusNoUlti;
										VieStarterBL = true;
									}
									else if (index == 1 && VieStarterBL == true)
									{
										parent->getParent()->getObjects("Player2")->getComponents<Physique>()->Revive = 0;
										parent->getParent()->getObjects("Player2")->getComponents<Physique>()->Starter = NoStater;
										VieStarterBL = false;
									}

									if (index == 2 && ScoreStarterBL == false && DegatStarterBL == false && VieStarterBL == false && UltiStarterBL == false && ScoreStarterBB == false)
									{
										parent->getParent()->getObjects("Player2")->getComponents<Physique>()->Starter = ScoreBonusMalusDegat;
										ScoreStarterBL = true;
									}
									else if (index == 2 && ScoreStarterBL == true)
									{
										parent->getParent()->getObjects("Player2")->getComponents<Physique>()->Starter = NoStater;
										ScoreStarterBL = false;
									}

									if (index == 3 && UltiStarterBL == false && DegatStarterBL == false && VieStarterBL == false && ScoreStarterBL == false && UltiStarterBB == false)
									{
										parent->getParent()->getObjects("Player2")->getComponents<Physique>()->Starter = BonusUltimeCanceled;
										UltiStarterBL = true;
									}
									else if (index == 3 && UltiStarterBL == true)
									{
										parent->getParent()->getObjects("Player2")->getComponents<Physique>()->Starter = NoStater;
										UltiStarterBL = false;
									}
								}
							}
						}
					}
				}
			}


		}
	}
}

bool Starters::getStarterboolperPlayer(std::string _player, std::string _starter)
{
	if (_player == "Player")
	{
		if (_starter == "VieStarter")
			return VieStarterBB;
		else if (_starter == "UltiStarter")
			return UltiStarterBB;
		else if (_starter == "DegatStarter")
			return DegatStarterBB;
		else if (_starter == "ScoreStarter")
			return ScoreStarterBB;
	}
	else if (_player == "Player2")
	{
		if (_starter == "VieStarter")
			return VieStarterBL;
		else if (_starter == "UltiStarter")
			return UltiStarterBL;
		else if (_starter == "DegatStarter")
			return DegatStarterBL;
		else if (_starter == "ScoreStarter")
			return ScoreStarterBL;
	}
}

bool Starters::getStartTutobool()
{
	return m_startTuto;
}

bool Starters::getSpawnHOLObool()
{
	return m_spawnHOLO;
}

void Starters::setStartTutobool(bool _newbool)
{
	m_startTuto = _newbool;
}

void Starters::setSpawnHOLObool(bool _newbool)
{
	m_spawnHOLO = _newbool;
}

void Starters::setBforZoneTrigger(bool _newbool)
{
	showB = _newbool;
}

void Starters::update()
{
}

void Starters::draw()
{
	window.draw(m_screenLeft);
	window.draw(m_screenRight);
	if (m_timerB < 1.5)
		showBtimer = true;


	if (m_timerB > 1.5)
      showBtimer = false;


	if (m_timerB > 3)
		m_timerB = 0;

	if (showB == true)
	{
		if (showBtimer == true)
			window.draw(m_buttonX[5]);
	}
	for (int i = 16; i < 18; i++)
	{
		m_spriteStartersSoute[i].setScale(1.f, 1.f);
		window.draw(m_spriteStartersSoute[i]);
	}

	for (int i = 12; i < 16; i++)
	{
		m_spriteStartersSoute[i].setScale(0.35f, 0.35f);
	}

	if (m_switchDescription == 0)
	{
		window.draw(m_spriteStartersSoute[14]);
		window.draw(m_textsSoute[1]);
		window.draw(m_textsSoute[2]);
	}
	if (m_switchDescription == 1)
	{
		window.draw(m_spriteStartersSoute[15]);
		window.draw(m_textsSoute[5]);
		window.draw(m_textsSoute[6]);
		window.draw(m_textsSoute[7]);
	}
	if (m_switchDescription == 2)
	{
		window.draw(m_spriteStartersSoute[12]);
		window.draw(m_textsSoute[3]);
		window.draw(m_textsSoute[4]);

	}
	if (m_switchDescription == 3)
	{
		window.draw(m_spriteStartersSoute[13]);
		window.draw(m_textsSoute[8]);
		window.draw(m_textsSoute[9]);
	}

	for (int i = 4; i < 8; i++)
	{
		window.draw(m_spriteStartersSoute[i]);
	}

	setSpriteStartersSouteTexture(0);
	setSpriteStartersSouteTexture(1);
	setSpriteStartersSouteTexture(2);
	setSpriteStartersSouteTexture(3);

	if (DegatStarterBB == true || DegatStarterBL == true)
		window.draw(m_spriteStartersSoute[8]);
	if (VieStarterBB == true || VieStarterBL == true)
		window.draw(m_spriteStartersSoute[9]);
	if (ScoreStarterBB == true || ScoreStarterBL == true)
		window.draw(m_spriteStartersSoute[10]);
	if (UltiStarterBB == true || UltiStarterBL == true)
		window.draw(m_spriteStartersSoute[11]);

	window.draw(m_buttonX[4]);

	if (m_startTuto == true)
	{
		window.draw(m_textsSoute[16]);

		window.getWindow().setView(window.getWindow().getDefaultView());

		m_spriteStartersSoute[18].setPosition(sf::Vector2f(100, 250));
		window.draw(m_spriteStartersSoute[18]);

		for (int n = 0; n < m_inputs.size(); n++)
		{
			m_inputs[n].setPosition(sf::Vector2f(m_spriteStartersSoute[18].getPosition().x + 65, (25 + m_spriteStartersSoute[18].getPosition().y) + (60 * n)));
			m_inputs[1].setPosition(sf::Vector2f(m_spriteStartersSoute[18].getPosition().x + 92, m_inputs[1].getPosition().y));
			window.draw(m_inputs[n]);
		}

		for (int n = 10; n < 16; n++)
		{
			m_textsSoute[n].setCharacterSize(25);
			m_textsSoute[n].setPosition(sf::Vector2f(m_spriteStartersSoute[18].getPosition().x + 110, (m_spriteStartersSoute[18].getPosition().y - 577) + (60 * n)));
			m_textsSoute[11].setPosition(sf::Vector2f(m_spriteStartersSoute[18].getPosition().x + 50, m_textsSoute[11].getPosition().y));
			window.draw(m_textsSoute[n]);
		}

		if (auto parent = getParents().lock())
		{
			window.getWindow().setView(parent->getParent()->getObjects("Camera")->getComponents<Camera>()->getView());
		}
	}
	else
	{
		window.draw(m_startGlow);
		window.draw(m_textsSoute[0]);
	}
}
