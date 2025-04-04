#include "Ui_Player.h"
#include "Package.h"
int Lifebar::m_playerNbr = -1;
int Score::nbrPlayer = -1;
float Score::timer = 0.0f;
Lifebar::Lifebar(Personnage _personnage)
{
	personnage = _personnage;
	//if (personnage != Personnage::UI_KIMPAH)
		m_playerNbr++;
	b_showProfiPicture = true;

	switch (personnage)
	{
	case UI_BIGBOY:
		s_personnageProfil.setTexture(RessourceManager::get()->getSceneTexture("bigboyIcon.png"));
		s_nomPersonnage.setTexture(RessourceManager::get()->getSceneTexture("bigboyName.png"));
		// LE NOM DU PERSO 

		s_personnageProfil.setPosition(m_pos);
		s_nomPersonnage.setScale(m_scale, m_scale);

		// LE CADRE DU JOUEUR 

		s_cadrePlayer.setTexture(RessourceManager::get()->getSceneTexture("playerContour.png"));
		s_cadrePlayer.setColor(sf::Color::Black);

		// SI 1 JOUEUR BLEU SINON ROUGE 

		if (m_playerNbr == 0)
			s_fondCadre.setTexture(RessourceManager::get()->getSceneTexture("playerFondBleu.png"));
		else
			s_fondCadre.setTexture(RessourceManager::get()->getSceneTexture("playerFondRed.png"));


		//CONTOUR LIFE

		s_cadreLife.setTexture(RessourceManager::get()->getSceneTexture("playerBarre.png"));
		s_cadreLife.setColor(sf::Color::Black);
		s_cadreLife.setScale(m_scale, m_scale);
		// LIFE BAR VERTE 
		m_life = 0.f;
		s_lifeBar.setTexture(RessourceManager::get()->getSceneTexture("playerLifeBar.png"));
		s_lifeBarGRIS.setTexture(RessourceManager::get()->getSceneTexture("playerLifeBar.png"));
		s_lifeBar.setScale(s_lifeBar.getScale().x - 0.37, m_scale);
		s_lifeBarGRIS.setScale(s_lifeBarGRIS.getScale().x - 0.37, m_scale);
		s_lifeBarGRIS.setColor(sf::Color(211.f, 211.f, 211.f, 255.f));
		m_fullLifeBar = s_lifeBar.getScale().x;
		// VIE 1 ou 2 (plus tard avec le starter)
		s_possibleLife.setTexture(RessourceManager::get()->getSceneTexture("lifeBar1.png"));
		s_possibleLife.setScale(m_scale, m_scale);
		// BARRE D'ULTI

		s_cadreUlti.setTexture(RessourceManager::get()->getSceneTexture("ultBarEmpty.png"));
		s_cadreUlti.setColor(sf::Color::Black);
		s_barreUlti.setTexture(RessourceManager::get()->getSceneTexture("ult.png"));

		s_barreUltiGris.setTexture(RessourceManager::get()->getSceneTexture("ult.png"));
		s_barreUlti.setColor(sf::Color(24, 176, 208, 255));

		s_barreUltiGris.setColor(sf::Color(211.f, 211.f, 211.f, 255.f));

		m_fullUlti = s_barreUlti.getScale().x;
		s_vieBonus.setTexture(RessourceManager::get()->getSceneTexture("lifeBar2.png"));
		s_vieBonus.setScale(m_scale, m_scale);
		break;
	case UI_BLOODLUST:
		s_personnageProfil.setTexture(RessourceManager::get()->getSceneTexture("bloodlustIcon.png"));
		s_nomPersonnage.setTexture(RessourceManager::get()->getSceneTexture("bloodlustName.png"));
		// LE NOM DU PERSO 

		s_personnageProfil.setPosition(m_pos);
		s_nomPersonnage.setScale(m_scale, m_scale);

		// LE CADRE DU JOUEUR 

		s_cadrePlayer.setTexture(RessourceManager::get()->getSceneTexture("playerContour.png"));
		s_cadrePlayer.setColor(sf::Color::Black);

		// SI 1 JOUEUR BLEU SINON ROUGE 

		if (m_playerNbr == 0)
			s_fondCadre.setTexture(RessourceManager::get()->getSceneTexture("playerFondBleu.png"));
		else
			s_fondCadre.setTexture(RessourceManager::get()->getSceneTexture("playerFondRed.png"));


		//CONTOUR LIFE

		s_cadreLife.setTexture(RessourceManager::get()->getSceneTexture("playerBarre.png"));
		s_cadreLife.setColor(sf::Color::Black);
		s_cadreLife.setScale(m_scale, m_scale);
		// LIFE BAR VERTE 
		m_life = 0.f;
		s_lifeBar.setTexture(RessourceManager::get()->getSceneTexture("playerLifeBar.png"));
		s_lifeBarGRIS.setTexture(RessourceManager::get()->getSceneTexture("playerLifeBar.png"));
		s_lifeBar.setScale(s_lifeBar.getScale().x - 0.37, m_scale);
		s_lifeBarGRIS.setScale(s_lifeBarGRIS.getScale().x - 0.37, m_scale);
		s_lifeBarGRIS.setColor(sf::Color(211.f, 211.f, 211.f, 255.f));
		m_fullLifeBar = s_lifeBar.getScale().x;
		// VIE 1 ou 2 (plus tard avec le starter)
		s_possibleLife.setTexture(RessourceManager::get()->getSceneTexture("lifeBar1.png"));
		s_possibleLife.setScale(m_scale, m_scale);
		// BARRE D'ULTI

		s_cadreUlti.setTexture(RessourceManager::get()->getSceneTexture("ultBarEmpty.png"));
		s_cadreUlti.setColor(sf::Color::Black);
		s_barreUlti.setTexture(RessourceManager::get()->getSceneTexture("ult.png"));

		s_barreUltiGris.setTexture(RessourceManager::get()->getSceneTexture("ult.png"));
		s_barreUlti.setColor(sf::Color(24, 176, 208, 255));

		s_barreUltiGris.setColor(sf::Color(211.f, 211.f, 211.f, 255.f));

		m_fullUlti = s_barreUlti.getScale().x;
		s_vieBonus.setTexture(RessourceManager::get()->getSceneTexture("lifeBar2.png"));
		s_vieBonus.setScale(m_scale, m_scale);
		break;
	case UI_KIMPAH:
		s_personnageProfil.setTexture(RessourceManager::get()->getSceneTexture("kimpah_boss.png"));
		s_nomPersonnage.setTexture(RessourceManager::get()->getSceneTexture("kimpah_bossName.png"));
		// LE NOM DU PERSO 
		s_personnageProfil.setPosition(m_pos);
		// LE CADRE DU JOUEUR 

		s_cadrePlayer.setTexture(RessourceManager::get()->getSceneTexture("contour_boss.png"));
		s_cadrePlayer.setColor(sf::Color::Black);

		s_fondCadre.setTexture(RessourceManager::get()->getSceneTexture("fond_vignette.png"));

		//CONTOUR LIFE

		s_cadreLife.setTexture(RessourceManager::get()->getSceneTexture("barre_boss.png"));
		s_cadreLife.setColor(sf::Color::Black);
		// LIFE BAR VERTE 
		m_life = 0.f;
		s_lifeBar.setTexture(RessourceManager::get()->getSceneTexture("playerLifeBar.png"));
		s_lifeBar.setScale(1.f, m_scale);
		s_lifeBarGRIS.setTexture(RessourceManager::get()->getSceneTexture("playerLifeBar.png"));
		s_lifeBarGRIS.setScale(1.f, m_scale);

		s_lifeBarGRIS.setColor(sf::Color(211.f, 211.f, 211.f, 255.f));
		m_fullLifeBar = s_lifeBar.getScale().x;
		break;
	}

	ColorLife();
	ScaleLife();
	s_lifeBarGRIS.setScale(s_lifeBar.getScale().x, m_scale);
	b_vieBonus = false;
}

Lifebar::~Lifebar()
{
	m_playerNbr--;
}


void Lifebar::setShowProfilePicture(bool _b_bool)
{
	b_showProfiPicture = _b_bool;
}

void Lifebar::ColorLife()
{


	if (auto p = getParents().lock())
	{
		if (auto parent = p->getParent())
		{
			if (auto life = parent->getComponents<Physique>())
			{
				m_life = life->getLife();
				m_ulti = life->ChargeUltimate;
			}
		}
	}
	float maxHp = 100.f;
	float tmp = static_cast<float>(m_life) / maxHp;
	s_lifeBar.setColor(sf::Color((1 - tmp) * 255, tmp * 255, 25));
}

void Lifebar::ScaleLife()
{
	float maxHp = 0.f;
	//LIFEBAR
	if (personnage == Personnage::UI_KIMPAH)
		maxHp = 160.5f;
	else
		maxHp = 100.f;

	float tmp = static_cast<float>(m_life) / maxHp;

	float targetScaleX = m_fullLifeBar;

	float currentScaleX = s_cadreLife.getScale().x;
	float newScaleX = tools::lerp(0, m_fullLifeBar, tmp);
	s_lifeBar.setScale(newScaleX, s_lifeBar.getScale().y);

	//ULTI


	int maxUlti = 100;

	float tmpUlti = static_cast<float>(m_ulti) / maxUlti;

	float targetScaleXUlti = 0.f / tmpUlti;
	float currentScaleXUlti = s_barreUlti.getScale().x;
	float newScaleXUlti = tools::lerp(0, m_fullUlti, tmpUlti);
	s_barreUlti.setScale(newScaleXUlti, s_lifeBar.getScale().y);
}

void Lifebar::initAllSpritePos()
{
	if (auto p = getParents().lock())
	{
		if (auto pos = p->getComponents<ObjectTransform>())
		{
			m_pos = pos->getPosition();
		}
		else
			m_pos = { 0.f,0.f };
	}

	if (auto p = getParents().lock())
		if (auto life = p->getComponents<Physique>())
			m_life = life->getLife();

	if (personnage == Personnage::UI_KIMPAH)
	{
		s_personnageProfil.setPosition(m_pos.x + 30.f, m_pos.y + 29.f);
		s_cadrePlayer.setPosition(m_pos.x + 80.f, m_pos.y + 80.f);
		s_nomPersonnage.setPosition(m_pos.x + 350.f, m_pos.y + 70.f);
		s_fondCadre.setPosition(s_cadrePlayer.getPosition().x + 4.f, s_cadrePlayer.getPosition().y + 4.f);
		s_cadreLife.setPosition(m_pos.x + 325.f, m_pos.y + 120.f);
		s_lifeBar.setPosition(s_cadreLife.getPosition().x + 5.f, s_cadreLife.getPosition().y + 3.f);
		s_lifeBarGRIS.setPosition(s_cadreLife.getPosition().x + 3.f, s_cadreLife.getPosition().y + 3.f);
	}
	else
	{
		s_personnageProfil.setPosition(m_pos);
		s_nomPersonnage.setPosition(m_pos.x + 120.f, m_pos.y + 20.f);
		s_cadrePlayer.setPosition(m_pos.x - 28.f, m_pos.y + 28.f);
		s_fondCadre.setPosition(s_cadrePlayer.getPosition().x + 4.f, s_cadrePlayer.getPosition().y + 4.f);
		s_cadreLife.setPosition(m_pos.x + 100.f, m_pos.y + 84.f);
		s_lifeBar.setPosition(s_cadreLife.getPosition().x + 92.f, s_cadreLife.getPosition().y + 3.f);
		s_lifeBarGRIS.setPosition(s_cadreLife.getPosition().x + 92.f, s_cadreLife.getPosition().y + 3.f);
		s_possibleLife.setPosition(m_pos.x + 110.f, m_pos.y + 92.f);
		s_cadreUlti.setPosition(m_pos.x + 350.f, m_pos.y + 140.f);
		s_barreUlti.setPosition(m_pos.x + 365.f, m_pos.y + 150.f);
		s_barreUltiGris.setPosition(m_pos.x + 360.f, m_pos.y + 148.f);
	}



}

void Score::setRouletteActif(bool m_bool)
{
	b_rouletteActive = m_bool;
}

int Lifebar::getPlayerNbr()
{
	return m_playerNbr;
}

void Lifebar::setPersonnageType(Personnage _personnage)
{
	personnage = _personnage;
}

sf::Vector2f Lifebar::getPos()
{
	return m_pos;
}

void Lifebar::LinkPlayerToUI(std::shared_ptr<Physique> _physique)
{
	wp_physique = _physique;
}

void Lifebar::setBonusLife(bool _vieBonus)
{
	b_vieBonus = _vieBonus;
}



void Lifebar::update()
{
	m_timer += tools::GetTimeDelta();

	//if (b_vieBonus)
	//{
	//	//CODE
	//}
	if (personnage == Personnage::UI_KIMPAH)
	{
		std::cout << "fuohieushfisfhyiesfhuishfuisehfuishfuihfukyishfhkyhjkhgvb ";
	}
}

void Lifebar::draw()
{
	sf::View currentView = window.getWindow().getView();
	window.getWindow().setView(window.getWindow().getDefaultView());

	// SET 
	ColorLife();
	ScaleLife();

	//ALL DRAW
	window.draw(s_nomPersonnage);
	window.draw(s_fondCadre);
	window.draw(s_cadrePlayer);
	if (b_showProfiPicture)
		window.draw(s_personnageProfil);
	window.draw(s_lifeBarGRIS);
	window.draw(s_lifeBar);
	window.draw(s_cadreLife);
	window.draw(s_possibleLife);
	if (personnage != Personnage::UI_KIMPAH)
	{
		window.draw(s_barreUltiGris);
		window.draw(s_barreUlti);
		window.draw(s_cadreUlti);
	}
	window.getWindow().setView(currentView);

}

////////////////
/////////////////////////////////  	SCORE  	 /////////////////////////////////////////////////////////
							   ////////////////

Score::Score()
{
	nbrPlayer++;

	m_nbrCombo = 0;
	m_nbrScoreHundreds = 0;
	m_nbrScoreThousands = 0;
	m_textScoreThousands.setFont(RessourceManager::get()->getFont("Scoring.otf"));
	m_texteScoreHundreds.setFont(RessourceManager::get()->getFont("Scoring.otf"));

	//Size police
	m_texteScoreHundreds.setCharacterSize(50.f);
	m_textScoreThousands.setCharacterSize(50.f);
	//Size bordure 
	m_textScoreThousands.setOutlineThickness(5.f);
	m_texteScoreHundreds.setOutlineThickness(5.f);
	// Color bordure
	m_texteScoreHundreds.setOutlineColor(sf::Color::Black);
	m_textScoreThousands.setOutlineColor(sf::Color::Black);
	////Origin
	//m_textScoreThousands.setOrigin(m_textScoreThousands.getGlobalBounds().width / 2.0f, m_textScoreThousands.getGlobalBounds().height / 2.0f);
	//m_texteScoreHundreds.setOrigin(m_texteScoreHundreds.getGlobalBounds().width / 2.0f, m_texteScoreHundreds.getGlobalBounds().height / 2.0f);
	//Pos tmp
	b_Comboing = false;
	if (auto p = getParents().lock())
	{
		if (auto pos = p->getComponents<ObjectTransform>())
		{
			m_pos = pos->getPosition();
			m_posCombo = pos->getPosition();
		}
		else
			m_pos = { 0.f,0.f };
	}
	m_ComboHit.setFont(RessourceManager::get()->getFont("Scoring.otf"));
	m_ComboHit.setCharacterSize(50.f);
	m_ComboHit.setString("COMBO X " + std::to_string(m_nbrCombo));
	m_ComboHit.setOrigin(m_ComboHit.getGlobalBounds().width / 2.0f, m_ComboHit.getGlobalBounds().height / 2.0f);
	m_ComboHit.setPosition(m_pos.x - 120.f, m_pos.y + 175.f);
	m_ComboHit.setOutlineThickness(5.f);
	m_ComboHit.setOutlineColor(sf::Color::Black);


	switch (m_nbrCombo % 5)
	{
	case 0:
		m_ComboHit.setFillColor(sf::Color::Red);
		break;
	case 1:
		m_ComboHit.setFillColor(sf::Color(229, 92, 63, 255));
		break;
	case 2:
		m_ComboHit.setFillColor(sf::Color::Yellow);
		break;
	case 3:
		m_ComboHit.setFillColor(sf::Color::Yellow);
		break;
	case 4:
		m_ComboHit.setFillColor(sf::Color::Yellow);
		break;

	}

	///Roulette
	m_spriteRoulette.setTexture(RessourceManager::get()->getSceneTexture("0boost_degat.png"));
	b_rouletteActive = false;
	m_roulette = 0;
	timerRoulette = 0.f;


	tmpTour = 0;
}

Score::~Score()
{
	nbrPlayer--;
}

int Score::getTotalScore()
{
	return totalScore;
}

void Score::initAllPos()
{
	if (auto p = getParents().lock())
	{
		if (auto pos = p->getComponents<ObjectTransform>())
		{
			m_pos = pos->getPosition();
			m_posCombo = pos->getPosition();
		}
		else
			m_pos = { 0.f,0.f };
	}
	m_textScoreThousands.setPosition(m_pos.x, m_pos.y);
	m_texteScoreHundreds.setPosition(m_pos.x + 80.f, m_textScoreThousands.getPosition().y);
	m_spriteRoulette.setPosition(m_pos.x - 388, m_pos.y + 17);

}

int Score::getMaxCombo()
{
	return m_maxCombo;
}

int Score::getScoreTotal()
{
	return totalScore;
}

void Score::setTextWhite()
{
	m_textScoreThousands.setFillColor(sf::Color::White);
	m_texteScoreHundreds.setFillColor(sf::Color::White);

}

int Score::getNbrPlayer()
{
	return nbrPlayer;
}

void Score::scoreAdd(int _scoreThousands, int _scoreHundreds)
{
	m_nbrScoreThousands += _scoreThousands;
	m_nbrScoreHundreds += _scoreHundreds;

	m_nbrHit++;
	m_nbrCombo++;
	b_Comboing = true;
	timer = 0.0f;


	if (m_nbrCombo >= 10)
	{
		//m_ComboHit.setFillColor(sf::Color(229, 92, 63, 255));
		m_ComboHit.setFillColor(sf::Color(252, 51, 8, 255));

		m_ComboHit.setRotation(0.f);
		m_ComboHit.setOutlineThickness(m_ComboHit.getOutlineThickness());
	}
	else
	{
		switch (m_nbrCombo % 5)
		{
		case 0:
			m_ComboHit.setFillColor(sf::Color(252, 51, 8, 255));
			m_ComboHit.setRotation(-7.5f);
			break;
		case 1:
			m_ComboHit.setFillColor(sf::Color(sf::Color::White));
			m_ComboHit.setRotation(0.f);
			break;
		case 2:
			m_ComboHit.setFillColor(sf::Color(229, 171, 63, 255));
			m_ComboHit.setRotation(5.f);
			break;
		case 3:
			m_ComboHit.setFillColor(sf::Color(229, 141, 63, 255));
			m_ComboHit.setRotation(-5.f);
			break;
		case 4:
			m_ComboHit.setFillColor(sf::Color(229, 114, 63, 255));
			m_ComboHit.setRotation(7.5f);
			break;
		}
		m_ComboHit.setOutlineThickness(m_ComboHit.getOutlineThickness() + 0.2);
	}


}

void Score::justAddScore(int _scoreThousands, int _scoreHundreds)
{
	m_nbrScoreThousands += _scoreThousands;
	m_nbrScoreHundreds += _scoreHundreds;

}

void Score::checkScoreLargage()
{
	if (totalScore >= 8000)
	{
		m_textScoreThousands.setFillColor(sf::Color::Green);
		m_texteScoreHundreds.setFillColor(sf::Color::Green);
	}
	else
	{
		m_textScoreThousands.setFillColor(sf::Color::Red);
		m_texteScoreHundreds.setFillColor(sf::Color::Red);
	}
}


void Score::update()
{

	if (b_colisDrop)
	{
		timerFiniRoulette += tools::GetTimeDelta();

		if (timerFiniRoulette > 3.0f)
		{
			b_colisDrop = false;
			timerFiniRoulette = 0.0f;
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		m_nbrScoreHundreds += 500;

	// Si 999, + 1 sur les milliers et set -999 sur les centaines 
	if (m_nbrScoreHundreds >= 1000)
	{
		m_nbrScoreHundreds -= 1000;
		m_nbrScoreThousands += 1;
	}
	if (m_nbrScoreHundreds <= 9)
		m_texteScoreHundreds.setString("00" + std::to_string(m_nbrScoreHundreds));
	else if (m_nbrScoreHundreds <= 99)
		m_texteScoreHundreds.setString("0" + std::to_string(m_nbrScoreHundreds));
	else if (m_nbrScoreHundreds <= 999)
		m_texteScoreHundreds.setString(std::to_string(m_nbrScoreHundreds));

	if (m_nbrScoreThousands <= 9)
		m_textScoreThousands.setString("00" + std::to_string(m_nbrScoreThousands));
	else if (m_nbrScoreThousands <= 99)
		m_textScoreThousands.setString("0" + std::to_string(m_nbrScoreThousands));
	else if (m_nbrScoreThousands <= 999)
		m_textScoreThousands.setString(std::to_string(m_nbrScoreThousands));



	if (b_Comboing)
	{
		timer += tools::GetTimeDelta();
		if (timer > 5.f)
		{
			b_Comboing = false;
			m_nbrCombo = 0;
			m_ComboHit.setScale(1.f, 1.f);
			m_ComboHit.setOutlineThickness(5.f);
		}
	}

	if (m_maxCombo < m_nbrCombo)
		m_maxCombo = m_nbrCombo;

	totalScore = (m_nbrScoreThousands * 1000) + m_nbrScoreHundreds;

	if (m_texteScoreHundreds.getFillColor() == sf::Color::Red || m_texteScoreHundreds.getFillColor() == sf::Color::Green)
		timerColor += tools::GetTimeDelta();

	if (timerColor > 1.0f)
	{
		m_texteScoreHundreds.setFillColor(sf::Color::White);
		m_textScoreThousands.setFillColor(sf::Color::White);
		timerColor = 0.0f;
	}

	if (b_rouletteActive)
	{
		timerRoulette += tools::GetTimeDelta();
		if (timerRoulette > 0.1f)
		{
			timerRoulette = 0.f;
			m_roulette++;
			tmpTour++;
			switch (m_roulette % 4)
			{
			case 0: m_spriteRoulette.setTexture(RessourceManager::get()->getSceneTexture("0boost_degat.png")); break;
			case 1: m_spriteRoulette.setTexture(RessourceManager::get()->getSceneTexture("0boost_invincible.png")); break;
			case 2: m_spriteRoulette.setTexture(RessourceManager::get()->getSceneTexture("0boost_score.png")); break;
			default: m_spriteRoulette.setTexture(RessourceManager::get()->getSceneTexture("0boost_vitesse.png")); break;
			}
			if (tmpTour >= 24)
			{
				b_finalLargage = true;
				b_rouletteActive = false;
				tmpTour = 0;
			}
		}
	}
	if (b_finalLargage)
	{
		timerFiniRoulette += tools::GetTimeDelta();
		if (auto p = getParents().lock()->getParent()->getParent())
		{
			if (auto player = getParents().lock()->getParent())
			{
				int random = tools::iRand(1, 5);

				switch (random)
				{
				case 1:
					m_spriteRoulette.setTexture(RessourceManager::get()->getSceneTexture("0boost_vitesse.png"));
					colis = Colis::createDrop(BLEU, sf::Vector2f(player->getComponents<ObjectTransform>()->getPosition().x, player->getComponents<ObjectTransform>()->getZBuffer() - 1000.f), sf::Vector2f(player->getComponents<ObjectTransform>()->getPosition().x, player->getComponents<ObjectTransform>()->getZBuffer()));
					//m_ui_colis = UI_COLIS::BLEU_UI;
					std::cout << "BLEU" << std::endl;
					break;
				case 2:
					m_spriteRoulette.setTexture(RessourceManager::get()->getSceneTexture("0boost_score.png"));
					colis = Colis::createDrop(JAUNE, sf::Vector2f(player->getComponents<ObjectTransform>()->getPosition().x, player->getComponents<ObjectTransform>()->getZBuffer() - 1000.f), sf::Vector2f(player->getComponents<ObjectTransform>()->getPosition().x, player->getComponents<ObjectTransform>()->getZBuffer()));
					//m_ui_colis = UI_COLIS::JAUNE_UI
					std::cout << "JAUNE" << std::endl;
					break;
				case 3:
					m_spriteRoulette.setTexture(RessourceManager::get()->getSceneTexture("0boost_degat.png"));
					colis = Colis::createDrop(ROUGE, sf::Vector2f(player->getComponents<ObjectTransform>()->getPosition().x, player->getComponents<ObjectTransform>()->getZBuffer() - 1000.f), sf::Vector2f(player->getComponents<ObjectTransform>()->getPosition().x, player->getComponents<ObjectTransform>()->getZBuffer()));
					//m_ui_colis = UI_COLIS::ROUGE_UI;
					std::cout << "ROUGE" << std::endl;

					break;
				case 4:
					m_spriteRoulette.setTexture(RessourceManager::get()->getSceneTexture("0boost_invincible.png"));
					colis = Colis::createDrop(VERT, sf::Vector2f(player->getComponents<ObjectTransform>()->getPosition().x, player->getComponents<ObjectTransform>()->getZBuffer() - 1000.f), sf::Vector2f(player->getComponents<ObjectTransform>()->getPosition().x, player->getComponents<ObjectTransform>()->getZBuffer()));
					//m_ui_colis = UI_COLIS::VERT_UI;
					std::cout << "VERT" << std::endl;

					break;
				}
				player->addGameObject(colis);
				justAddScore(-8, 0);
				b_colisDrop = true;
				b_finalLargage = false;
			}

		}
	}
}

bool Score::getFinitoRoulette()
{
	return b_colisDrop;
}

void Score::setFinitoRoulette(bool _colisDrop)
{
	b_colisDrop = _colisDrop;
}

void Score::draw()
{
	sf::View currentView = window.getWindow().getView();
	window.getWindow().setView(window.getWindow().getDefaultView());


	m_textScoreThousands.setPosition(m_pos.x, m_pos.y);
	m_texteScoreHundreds.setPosition(m_pos.x + 80.f, m_textScoreThousands.getPosition().y);

	window.draw(m_textScoreThousands);
	window.draw(m_texteScoreHundreds);
	if (b_rouletteActive || b_finalLargage || b_colisDrop)
	{
		window.draw(m_spriteRoulette);
		if (auto p = getParents().lock()->getParent())
			if (auto life = p->getObjects("LIFEBAR_UI")->getComponents<Lifebar>())
				life->setShowProfilePicture(false);
	}
	else
		if (auto p = getParents().lock()->getParent())
			if (auto life = p->getObjects("LIFEBAR_UI")->getComponents<Lifebar>())
				life->setShowProfilePicture(true);
	if (b_Comboing)
	{
		m_ComboHit.setString("COMBO x " + std::to_string(m_nbrCombo));
		if (m_nbrCombo <= 10)
			m_ComboHit.setScale(1.f + (static_cast<float>(m_nbrCombo) / 13.60f), 1.f + static_cast<float>(m_nbrCombo) / 13.60f);

		m_ComboHit.setPosition(m_pos.x - 240.f, m_pos.y + 150.f);
		window.draw(m_ComboHit);
	}

	window.getWindow().setView(currentView);
}

void Score::setTypeColisUI(std::shared_ptr<GameObject> _go)
{
	if (auto colis = _go->getComponents<Package>())
	{
		if (colis->getType() == TYPE_COLIS::BLEU)
			m_ui_colis = UI_COLIS::BLEU_UI;
		if (colis->getType() == TYPE_COLIS::ROUGE)
			m_ui_colis = UI_COLIS::ROUGE_UI;
		if (colis->getType() == TYPE_COLIS::JAUNE)
			m_ui_colis = UI_COLIS::JAUNE_UI;
		if (colis->getType() == TYPE_COLIS::VERT)
			m_ui_colis = UI_COLIS::VERT_UI;
	}
}