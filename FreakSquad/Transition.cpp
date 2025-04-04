#include "Transition.h"
#include "Game.h"
#include "Sounds3D.h"

Transition::Transition()
{

	m_doTransitToMenu = false;
	m_opacity = 254.5f;
	m_timerTransition = 0.0f;
	m_timerFonduLerp = 0.0f;
	m_timerFonduLerp2 = 0.0f;
	m_mooveCam = false;
	m_transitionCam = false;
	m_bFonduLerp = false;
	m_bFonduLerp2 = false;
	m_isDoingTp = false;
	m_isDoingTp2 = false;
	m_activeBackMenu = false;
	m_activeFinLevel = false;
	m_activeDechirureLevel = false;
	m_intrectBande = { 0,0,1920,1080 };
	m_timerBande = 0.0f;
	m_frameXBande = 0.0f;
	m_timerActiveFondu = 0.0f;
	m_activeFinScore = false;
	m_opacityScore = 0.0f;
	m_positionFondScore = { -1000.0f,270.0f };
	m_NEWpositionFondScore = m_positionFondScore;
	m_positionBandeScore = { 1000.0f,-2516.0 };
	m_NEWpositionBandeScore = m_positionBandeScore;
	m_timerPositionScore = 0.0f;
	m_timerPositionFondScore = 0.0f;
	m_opacityBoutonA = 0.0f;
	m_opacityBoutonA2 = 0.0f;

	m_Score = 0;
	m_ScoreTemps = 1;
	m_ScoreCombo = 1;
	m_ScoreTotal = 1;

	m_opacityDegrader_Crane = 0.0f;
	m_opacityGameOver = 0.0f;
	m_makeFonduMORT = false;
	m_timerFonduMORT = 0.0f;
	m_timerFonduLerpMORT = 0.0f;
	m_bFonduLerpMORT = false;
	m_isDoingpMORT = false;
	m_opacityGris = 0.0f;
	m_timerFonduMenu = 0.0f;

	m_opacitySkip = 0.0f;

	m_posYCredit = 1080.0f;
	m_activeCredit = false;
	m_timertemp = 0.0f;
	m_NBTemps = 0.0f;
	m_afficeScore = false;

	m_recFondu.setSize(sf::Vector2f(1920.0f, 1080.0f));
	m_recFondu.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, m_opacity));

	m_recFonduScore.setSize(sf::Vector2f(1920.0f, 1080.0f));
	m_recFonduScore.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, m_opacityScore));

	m_spriteBandeDebut.setTexture(RessourceManager::get()->getSceneTexture("debut_fin_niv.png"));
	m_spriteBandeDebut.setTextureRect(m_intrectBande);
	m_spriteBandeFin.setTexture(RessourceManager::get()->getSceneTexture("fin_niv.png"));
	m_spriteBandeFin.setTextureRect(m_intrectBande);
	m_spriteFondScore.setTexture(RessourceManager::get()->getSceneTexture("fenetre_opac.png"));
	m_spriteBandeScore.setTexture(RessourceManager::get()->getSceneTexture("bar.png"));

	/////////
	textScore.setFont(RessourceManager::get()->getFont("Gras.otf"));
	textScore.setCharacterSize(40);
	textScore.setString("Score :");
	textTemps.setFont(RessourceManager::get()->getFont("Gras.otf"));
	textTemps.setCharacterSize(40);
	textTemps.setString("Time :");
	textComboMax.setFont(RessourceManager::get()->getFont("Gras.otf"));
	textComboMax.setCharacterSize(40);
	textComboMax.setString("Max Combo :");
	textScoreTotal.setFont(RessourceManager::get()->getFont("Gras.otf"));
	textScoreTotal.setCharacterSize(40);
	textScoreTotal.setString("Total Score :");

	textNBScore.setFont(RessourceManager::get()->getFont("Gras.otf"));
	textNBScore.setCharacterSize(40);
	textNBScore.setString(std::to_string(m_Score));
	textNBScore.setFillColor(sf::Color::Black);
	textNBTemps.setFont(RessourceManager::get()->getFont("Gras.otf"));
	textNBTemps.setCharacterSize(40);
	textNBTemps.setString(std::to_string(m_ScoreTemps));
	textNBTemps.setFillColor(sf::Color::Black);
	textNBComboMax.setFont(RessourceManager::get()->getFont("Gras.otf"));
	textNBComboMax.setCharacterSize(40);
	textNBComboMax.setString(std::to_string(m_ScoreCombo));
	textNBComboMax.setFillColor(sf::Color::Black);
	textNBScoreTotal.setFont(RessourceManager::get()->getFont("Gras.otf"));
	textNBScoreTotal.setCharacterSize(40);
	textNBScoreTotal.setString(std::to_string(m_ScoreTotal));
	textNBScoreTotal.setFillColor(sf::Color::Black);

	m_spriteBoutonA.setTexture(RessourceManager::get()->getSceneTexture("touche_aC.png"));
	m_spriteBoutonA.setColor(sf::Color(255.0f, 255.0f, 255.0f, m_opacityBoutonA));
	m_spriteBoutonA2.setTexture(RessourceManager::get()->getSceneTexture("touche_aC.png"));
	m_spriteBoutonA2.setColor(sf::Color(255.0f, 255.0f, 255.0f, m_opacityBoutonA2));

	m_textSkip.setFont(RessourceManager::get()->getFont("Gras.otf"));
	m_textSkip.setCharacterSize(30);
	m_textSkip.setString("Skip");
	m_textSkip.setFillColor(sf::Color(255.0f, 255.0f, 255.0f, m_opacitySkip));

	//Game over
	m_recFondGris.setSize(sf::Vector2f(1920.0f, 1080.0f));
	m_recFondGris.setFillColor(sf::Color(118.0f, 118.0f, 118.0f, m_opacityGris));
	m_spriteFondDegrader.setTexture(RessourceManager::get()->getSceneTexture("fonDegrad.png"));
	m_spriteFondDegrader.setColor(sf::Color(255.0f, 255.0f, 255.0f, m_opacityDegrader_Crane));
	m_spriteFondCrane.setTexture(RessourceManager::get()->getSceneTexture("trame.png"));
	m_spriteFondCrane.setColor(sf::Color(255.0f, 255.0f, 255.0f, m_opacityDegrader_Crane));
	m_spriteGameOver.setTexture(RessourceManager::get()->getSceneTexture("game_over.png"));
	m_spriteGameOver.setColor(sf::Color(255.0f, 255.0f, 255.0f, m_opacityGameOver));
	m_recFonduGameOver.setSize(sf::Vector2f(1920.0f, 1080.0f));
	m_recFonduGameOver.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, m_opacityScore));

	//credit
	m_spriteCredit.setTexture(RessourceManager::get()->getSceneTexture("credit1.png"));
	m_spriteCredit2.setTexture(RessourceManager::get()->getSceneTexture("credit2.png"));
	DoFondu(TRANS);
}

Transition::~Transition()
{
}

void Transition::update()
{
	m_timerBande += tools::GetTimeDelta();

	if (auto InputAuto = getParents().lock()) {
		auto input = InputAuto->getComponents<Input>();
		input->update();
		/////Update anime Fin de level ////////////////////////////////////////////////////////////////////
		if (m_activeFinLevel == true)
		{
			m_timerActiveFondu += tools::GetTimeDelta();
			if (m_timerBande > 0.09f)
			{
				m_frameXBande += 1;
				if (m_frameXBande > 5)
				{
					m_frameXBande = 5;
				}
				m_timerBande = 0.0f;
			}
			m_intrectBande.left = m_frameXBande * m_intrectBande.width;
			m_spriteBandeDebut.setTextureRect(m_intrectBande);
		}
		if (m_timerActiveFondu > 1.5f && m_activeFinLevel == true)
		{
			m_activeFinLevel = false;
			m_activeBackMenu = false;
			DoFondu(NOIR);
			m_activeDechirureLevel = true;
			m_frameXBande = 0;
			m_timerActiveFondu = 0.0f;
		}
		if (m_activeDechirureLevel == true)
		{
			m_timerActiveFondu += tools::GetTimeDelta();
			if (m_timerBande > 0.09f)
			{
				m_frameXBande += 1;
				if (m_frameXBande > 10)
				{
					m_frameXBande = 10;
				}
				m_timerBande = 0.0f;
			}
			m_intrectBande.left = m_frameXBande * m_intrectBande.width;
			m_spriteBandeFin.setTextureRect(m_intrectBande);
		}
		if (m_timerActiveFondu > 1.5f && m_activeDechirureLevel == true)
		{
			m_activeFinScore = true;
			m_activeDechirureLevel = false;
		}
		if (m_activeFinScore == true)
		{
			m_timerPositionScore += tools::GetTimeDelta();
			m_timerPositionFondScore += tools::GetTimeDelta() * 1.5;
			m_NEWpositionBandeScore.y = testelerp(m_positionBandeScore.y, m_positionBandeScore.y + 1997.0f, m_timerPositionScore);
			m_NEWpositionFondScore.x = testelerp(m_positionFondScore.x, m_positionFondScore.x + 1500.0f, m_timerPositionFondScore);
			if (m_timerPositionScore > 1.5f)
			{
				if (m_opacityBoutonA < 255.0f)
				{
					m_opacityBoutonA += 200 * tools::GetTimeDelta();
				}
				if (m_opacityBoutonA >= 255.0f)
				{
					m_opacityBoutonA = 255.0f;
				}
				if (m_opacityBoutonA >= 100)
				{
					if (input->getType(gp::Gamepad::A) == PRESSED)
					{
						m_afficeScore = true;
						m_lanceEnding = true; // Lance l'ending
						DoFonduScore(NOIR2);
					}
				}
			}
		}
		if (m_activeCredit == true)
		{
			
			if (m_posYCredit <= +600.0f)
			{
				if (m_opacityBoutonA2 < 255.0f)
				{
					m_opacitySkip += 255.0f * tools::GetTimeDelta();
					m_opacityBoutonA2 += 255.0f * tools::GetTimeDelta();
				}
				if (m_opacityBoutonA2 >= 255.0f)
				{
					m_opacityBoutonA2 = 255.0f;
				}
			}

			m_posYCredit -= 52.5f * tools::GetTimeDelta();

			if (m_opacityBoutonA2 >= 150.0f && InputAuto->getComponents<Input>()->getType(gp::Gamepad::A) == PRESSED)
			{
				m_activateEnd = true;
				m_posYCredit = m_posYCredit - 95000.0f;
			}
			else
			{
				m_activateEnd = false;
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	if (m_posYCredit <= -11500.0f)
	{
		m_activateEnd = true;
		m_doTransitToMenu = true;
	}
	else
		m_activateEnd = false;
	if (m_opacityScore >= 255.0f && m_activeBackMenu == true)
	{
		m_posYCredit = m_posYCredit - 95000.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		DoFonduMORT();
	}

	DisplayFonduSwap();
	DisplayFonduScore();
	DisplayFonduMORT();
	
}

void Transition::draw()
{
	textNBScore.setString(std::to_string(m_Score));
	textNBTemps.setString(std::to_string(m_ScoreTemps));
	textNBComboMax.setString(std::to_string(m_ScoreCombo));
	textNBScoreTotal.setString(std::to_string(m_ScoreTotal));

	sf::View tmpview = window.getWindow().getView();
	window.getWindow().setView(window.getWindow().getDefaultView());


	m_recFondu.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, m_opacity));
	m_recFonduScore.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, m_opacityScore));

	m_spriteBoutonA.setColor(sf::Color(255.0f, 255.0f, 255.0f, m_opacityBoutonA));
	m_spriteBoutonA2.setColor(sf::Color(255.0f, 255.0f, 255.0f, m_opacityBoutonA2));
	m_textSkip.setFillColor(sf::Color(255.0f, 255.0f, 255.0f, m_opacitySkip));
	m_spriteFondDegrader.setColor(sf::Color(255.0f, 255.0f, 255.0f, m_opacityDegrader_Crane));
	m_spriteFondCrane.setColor(sf::Color(255.0f, 255.0f, 255.0f, m_opacityDegrader_Crane));
	m_spriteGameOver.setColor(sf::Color(255.0f, 255.0f, 255.0f, m_opacityGameOver));
	m_recFondGris.setFillColor(sf::Color(118.0f, 118.0f, 118.0f, m_opacityGris));
	m_recFonduGameOver.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, m_opacityScore));

	window.getWindow().draw(m_recFondu);

	if (m_activeFinLevel == true)
	{
		window.getWindow().draw(m_spriteBandeDebut);
	}
	if (m_activeDechirureLevel == true)
	{
		window.getWindow().draw(m_spriteBandeFin);
	}
	m_spriteBoutonA.setPosition(WindowManager::getInstance()->getWindow()->getWindow().getPosition().x + 1800.0f, WindowManager::getInstance()->getWindow()->getWindow().getPosition().y + 925.0f);
	m_spriteBoutonA2.setPosition(WindowManager::getInstance()->getWindow()->getWindow().getPosition().x + 1800.0f, WindowManager::getInstance()->getWindow()->getWindow().getPosition().y + 925.0f);
	m_textSkip.setPosition(WindowManager::getInstance()->getWindow()->getWindow().getPosition().x + 1710.0f, WindowManager::getInstance()->getWindow()->getWindow().getPosition().y + 950.0f);
	m_spriteFondScore.setPosition(WindowManager::getInstance()->getWindow()->getWindow().getPosition().x + m_NEWpositionFondScore.x, WindowManager::getInstance()->getWindow()->getWindow().getPosition().y + m_NEWpositionFondScore.y);
	m_spriteBandeScore.setPosition(WindowManager::getInstance()->getWindow()->getWindow().getPosition().x + m_NEWpositionBandeScore.x, WindowManager::getInstance()->getWindow()->getWindow().getPosition().y + m_NEWpositionBandeScore.y);
	textScore.setPosition(m_NEWpositionFondScore.x + 150, m_NEWpositionFondScore.y + 60.0f);
	textTemps.setPosition(m_NEWpositionFondScore.x + 150, m_NEWpositionFondScore.y + 160.0f);
	textComboMax.setPosition(m_NEWpositionFondScore.x + 150, m_NEWpositionFondScore.y + 260.0f);
	textScoreTotal.setPosition(m_NEWpositionFondScore.x + 150, m_NEWpositionFondScore.y + 360.0f);

	textNBScore.setPosition(m_NEWpositionBandeScore.x + 50, m_NEWpositionBandeScore.y + 850.0f);
	textNBTemps.setPosition(m_NEWpositionBandeScore.x + 50, m_NEWpositionBandeScore.y + 950.0f);
	textNBComboMax.setPosition(m_NEWpositionBandeScore.x + 50, m_NEWpositionBandeScore.y + 1050.0f);
	textNBScoreTotal.setPosition(m_NEWpositionBandeScore.x + 5, m_NEWpositionBandeScore.y + 1150.0f);
	if (m_afficeScore == false)
	{
		window.getWindow().draw(m_spriteFondScore);
		window.getWindow().draw(textScore);
		window.getWindow().draw(textTemps);
		window.getWindow().draw(textComboMax);
		window.getWindow().draw(textScoreTotal);
		window.getWindow().draw(m_spriteBandeScore);
		window.getWindow().draw(textNBScore);
		window.getWindow().draw(textNBTemps);
		window.getWindow().draw(textNBComboMax);
		window.getWindow().draw(textNBScoreTotal);
		window.getWindow().draw(m_spriteBoutonA);
		window.getWindow().draw(m_recFonduScore);
	}
	//MORT
	m_recFondGris.setPosition(WindowManager::getInstance()->getWindow()->getWindow().getPosition().x, WindowManager::getInstance()->getWindow()->getWindow().getPosition().y);
	m_spriteFondDegrader.setPosition(WindowManager::getInstance()->getWindow()->getWindow().getPosition().x, WindowManager::getInstance()->getWindow()->getWindow().getPosition().y);
	m_spriteFondCrane.setPosition(WindowManager::getInstance()->getWindow()->getWindow().getPosition().x, WindowManager::getInstance()->getWindow()->getWindow().getPosition().y);
	m_spriteGameOver.setPosition(WindowManager::getInstance()->getWindow()->getWindow().getPosition().x + 400.0f, WindowManager::getInstance()->getWindow()->getWindow().getPosition().y + 400.0f);
	window.getWindow().draw(m_recFondGris);
	window.getWindow().draw(m_spriteFondDegrader);
	window.getWindow().draw(m_spriteFondCrane);
	window.getWindow().draw(m_spriteGameOver);
	window.getWindow().draw(m_recFonduGameOver);
	//CREDIT
	m_spriteCredit.setPosition(WindowManager::getInstance()->getWindow()->getWindow().getPosition().x, WindowManager::getInstance()->getWindow()->getWindow().getPosition().y + m_posYCredit);
	window.getWindow().draw(m_spriteCredit);
	m_spriteCredit2.setPosition(WindowManager::getInstance()->getWindow()->getWindow().getPosition().x, WindowManager::getInstance()->getWindow()->getWindow().getPosition().y + m_posYCredit + 7804);
	window.getWindow().draw(m_spriteCredit2);
	window.getWindow().draw(m_spriteBoutonA2);
	window.getWindow().draw(m_textSkip);

	window.getWindow().setView(tmpview);
}

void Transition::DoFondu(FONDU _choix)
{
	if (!m_isDoingTp)
	{
		m_type = _choix;
		m_makeFondu = true;
		m_timerFondu = 0.0f;
		m_timerFonduLerp = 0.0f;
		m_bFonduLerp = false;
		m_isDoingTp = true;
	}
}

void Transition::DoFonduScore(FONDU2 _choix)
{
	if (!m_isDoingTp2)
	{
		m_type2 = _choix;
		m_makeFondu2 = true;
		m_timerFondu2 = 0.0f;
		m_timerFonduLerp2 = 0.0f;
		m_bFonduLerp2 = false;
		m_isDoingTp2 = true;
	}
}

void Transition::DoFonduMORT()
{
	if (!m_isDoingpMORT)
	{
		m_makeFonduMORT = true;
		m_timerFonduMORT = 0.0f;
		m_timerFonduLerpMORT = 0.0f;
		m_bFonduLerpMORT = false;
		m_isDoingpMORT = true;
	}
}

void Transition::DisplayFonduSwap()
{
	if (m_type == NOIR)
	{
		if (m_makeFondu)
		{
			m_timerFondu += tools::GetTimeDelta();
			m_timerFonduLerp += tools::GetTimeDelta() / 5.0f;
			if (m_timerFondu < 2.0f)
			{
				if (!m_bFonduLerp)
				{
					if (m_timerFondu > 1.5f)
					{
						m_isDoingTp = false;
					}
					m_opacity = tools::lerp(m_opacity, 255.0f, m_timerFonduLerp);
				}
			}
			else
			{
				m_bFonduLerp = true;
				m_timerFondu = 0.0f;
				m_timerFonduLerp = 0.0f;
			}
			if (m_timerFondu > 0.5f && m_bFonduLerp)
			{
				m_opacity = 255.0f;
				m_makeFondu = false;
				m_timerFondu = 0.0f;
			}
		}
	}
	if (m_type == TRANS)
	{
		if (m_makeFondu)
		{
			m_timerFondu += tools::GetTimeDelta();
			m_timerFonduLerp += tools::GetTimeDelta() / 5.0f;
			if (m_timerFondu < 2.0f)
			{
				if (!m_bFonduLerp)
				{
					if (m_timerFondu > 1.5f)
					{
						m_isDoingTp = false;
					}
					m_opacity = tools::lerp(m_opacity, 0.0f, m_timerFonduLerp);
				}
			}
			else
			{
				m_bFonduLerp = true;
				m_timerFondu = 0.0f;
				m_timerFonduLerp = 0.0f;
			}
			if (m_opacity <= 0.0f)
			{
				m_opacity = 0.0f;
			}
			if (m_timerFondu > 0.5f && m_bFonduLerp)
			{
				m_opacity = 0.0f;
				m_makeFondu = false;
				m_timerFondu = 0.0f;
			}
		}
	}
}

void Transition::DisplayFonduScore()
{
	if (m_type2 == NOIR2)
	{
		if (m_makeFondu2)
		{
			m_timerFondu2 += tools::GetTimeDelta();
			m_timerFonduLerp2 += tools::GetTimeDelta() / 5.0f;
			if (m_timerFondu2 < 2.0f)
			{
				if (!m_bFonduLerp2)
				{
					if (m_timerFondu2 > 1.5f)
					{
						m_isDoingTp2 = false;
					}
					m_opacityScore = tools::lerp(m_opacityScore, 255.0f, m_timerFonduLerp2);
				}
			}
			else
			{
				m_bFonduLerp2 = true;
				m_timerFondu2 = 0.0f;
				m_timerFonduLerp2 = 0.0f;
			}
			if (m_timerFondu2 > 0.5f && m_bFonduLerp2)
			{
				m_opacityScore = 255.0f;
				m_makeFondu2 = false;
				m_timerFondu2 = 0.0f;
			}
		}
	}
	if (m_type2 == TRANS2)
	{
		if (m_makeFondu2)
		{
			m_timerFondu2 += tools::GetTimeDelta();
			m_timerFonduLerp2 += tools::GetTimeDelta() / 5.0f;
			if (m_timerFondu2 < 2.0f)
			{
				if (!m_bFonduLerp2)
				{
					if (m_timerFondu2 > 1.5f)
					{
						m_isDoingTp2 = false;
					}
					m_opacityScore = tools::lerp(m_opacityScore, 0.0f, m_timerFonduLerp2);
				}
			}
			else
			{
				m_bFonduLerp2 = true;
				m_timerFondu2 = 0.0f;
				m_timerFonduLerp2 = 0.0f;
			}
			if (m_timerFondu2 > 0.5f && m_bFonduLerp2)
			{
				m_opacityScore = 0.0f;
				m_makeFondu2 = false;
				m_timerFondu2 = 0.0f;
			}
		}
	}
}

void Transition::DisplayFonduMORT()
{
	if (m_makeFonduMORT)
	{
		m_timerFonduMORT += tools::GetTimeDelta();
		m_timerFonduLerpMORT += tools::GetTimeDelta() / 5.0f;
		m_timerFonduMenu += tools::GetTimeDelta();
		if (m_timerFonduMORT < 2.0f)
		{
			if (!m_bFonduLerpMORT)
			{
				if (m_timerFonduMORT > 1.5f)
				{
					m_isDoingpMORT = false;
				}
				m_opacityDegrader_Crane = tools::lerp(m_opacityDegrader_Crane, 255.0f, m_timerFonduLerpMORT);
				m_opacityGameOver = tools::lerp(m_opacityGameOver, 255.0f, m_timerFonduLerpMORT / 10.0f);
				m_opacityGris = tools::lerp(m_opacityGris, 205.0f, m_timerFonduLerpMORT);
			}
		}
		else
		{
			m_bFonduLerpMORT = true;
			m_timerFonduMORT = 0.0f;
			m_timerFonduLerpMORT = 0.0f;
		}
		if (m_timerFonduMORT > 0.5f && m_bFonduLerpMORT)
		{
			m_opacityDegrader_Crane = 255.0f;
			m_opacityGameOver = 255.0f;
			m_opacityGris = 205.0f;
			m_timerFonduMORT = 0.0f;
		}
		if (m_timerFonduMenu > 4.0f)
		{
			m_activeBackMenu = true;
			DoFonduScore(NOIR2);
			m_makeFonduMORT = false;
		}
	}
}

float Transition::testelerp(float start, float end, float t)
{
	t = std::clamp(t, 0.0f, 1.0f);
	t = t * t * (3 - 2 * t);
	return (1 - t) * start + t * end;
}

bool Transition::getTransitToMenu()
{
	return m_doTransitToMenu;
}

void Transition::setBoolFinNiveau(bool _bool)
{
	m_activeFinLevel = _bool;
}

bool Transition::getBoolFinNiveau()
{
	return m_activeFinLevel;
}

bool Transition::getStartEnding()
{
	return m_lanceEnding;
}

bool Transition::getEnd()
{
	return m_activateEnd;
}

void Transition::setStartCredit(bool _start)
{
	m_activeCredit = _start;
}

void Transition::resetStartEnding()
{
	m_lanceEnding = false;
}

bool Transition::getRetourMenu()
{
	return m_doTransitToMenu;
}

int Transition::getScore()
{
	return m_Score;
}

int Transition::getTimer()
{
	return m_ScoreTemps;
}

int Transition::getCombo()
{
	return m_ScoreCombo;
}

void Transition::setScore(int _score)
{
	m_Score = _score;
}

void Transition::setTimer(int _timer)
{
	m_ScoreTemps = _timer;
}

void Transition::setCombo(int _Combo)
{
	m_ScoreCombo = _Combo;
}

void Transition::setPosition(float _posY)
{
	m_posYCredit = _posY;
}

void Transition::setTransitionMenu(bool _bool)
{
	m_doTransitToMenu = _bool;
}

void Transition::calculScore()
{
	m_ScoreTotal = m_Score * m_ScoreCombo;
}
