#include "IA_PatternS.h"
#include"Physique.h"
IA_SPIKER::IA_SPIKER()
{
	m_pattern = SPAWN;
	//----------------------------------------------------------
	m_life = 60;
	m_dStun = 0.3f;
	t_avEjecL = 1;  //Temps avant de reset l'éjection quand tu te prends plus
	c_spdBack = 200.f;
	c_spdWalk = 450.f;
	//----------------------------------------------------------
	t_stun = 3;
	t_lockReleve = 10;   //VaBloquer l'IA sur : être éjecter et se relever 
	m_timerAtt = 13;

	m_dChargAtt = RANDOMCHARGETIMER;
	int a = tools::iRand(0, 100);
	m_distanceFlee = 520.f + a;
	m_distanceGo = 900.f;
}

IA_SPIKER::~IA_SPIKER()
{
}

void IA_SPIKER::update()
{
	if (m_active)
	{
		AllPointeur();    //Def tous les pointeurs
		m_target = TransTarget->getPosition();
		m_position = tools2::direction(transform->getPosition(), m_target);
		m_distanceToPlayer = tools2::distance(transform->getPosition(), m_target);
		bool arriv = arrived();

			m_timer += tools::GetTimeDelta();
			if (m_lockP)
				m_TPA += tools::GetTimeDelta();
			m_addLongAtt += tools::GetTimeDelta() * 500;
			m_tReleve += tools::GetTimeDelta();
			if (m_pattern == IDLEE && CONDITIONCHARGEY && m_distanceToPlayer < 900.f) // rajouter le check Zbuffer)
				m_goAttack += tools::GetTimeDelta();
			if (physics->getComportement() == KnockDown)
				m_tKnock += tools::GetTimeDelta();
			else
				m_tKnock = 0;

			updatePakage();
			if (action != NONE)
			{
				m_TPA = 0;
			}
			action = NONE;
	}
	else
	{
		if (!m_desactivation) //Destruction du code
		{
			/*this->setActive(false);*/
			body->setSpeed(sf::Vector2f(0, 0));
			transform->setPosition(sf::Vector2f(-5000, -5000));
			transform->setActive(false);
			body->setActive(false);
			animator->setActive(false);
			animator->pause();
			sprite->setActive(false);
			physics->setActive(false);
			collid->setActive(false);
			m_desactivation = true;
		}
	}
}

void IA_SPIKER::draw()
{
}

void IA_SPIKER::behaviourTree()
{
	bool help = false;
	if ((m_dirToPos.y < 0 && transform->getPosition().y > TransTarget->getPosition().y))
		help = true;
	if ((m_dirToPos.y > 0 && transform->getPosition().y < TransTarget->getPosition().y))
		help = true;
	//---------------------------------------------------- //Priorité des comportements
/*  		 | | | | | | | | | | | | | | |																																					*/
/*			 v v v v v v v v v v v v v v v																																					*/
			//---------------------------------      BEHAVIOUR TREE
	if (m_timer < 1.2f)
		m_pattern = SPAWN;
	else
	{
		if (physics->getComportement() == Died)
			dead();
		else if (m_TPA > m_dStun && m_lockP && m_pattern == HIIT)
			action = ACTION::BREAK;
		else if (m_TPA > (m_tLockAtt + /*-*/2.f/*-*/) && m_attacking) //temps de repos après un coup
		{
			m_goAttack = 0;
			m_TPA = 0;
			action = ACTION::BREAK;
		}
		else if (m_pattern == IDLEE && CONDITIONCHARGEY && m_goAttack > 0.5f)
		{
			m_TPA = 0;
			int a = tools::iRand(0, 12);
			if (a == 0)
				action = ACTION::TROLL;
			else if (a == 1|| a == 2)
			{
				action = ACTION::GRAB;
			}
			else
			{
				action = ACTION::LONGHIT;
			}
		}
		else if (m_pattern == GOBACKING && m_TPA > 1.5f)
		{
			action = ACTION::REPOSITIONNE;
		}
		else if (m_pattern == TURNAROUNDREMAKEE && same && m_timerTurn2 > m_timerTurn)
		{
			action = ACTION::IDLE;
		}
		else if (m_pattern == TURNAROUNDD && m_TPA > 2.f)
		{
			action = ACTION::BREAK;
		}
		else if (m_pattern == REPOSITIIONNE && help)
		{
			action = ACTION::IDLE;
		}
		else if (m_pattern == AVANCCE && m_distanceToPlayer < 900.f)
			action = ACTION::IDLE;
		else if (m_pattern == IDLEE && m_TPA > 1.2f)
		{
			if (m_distanceToPlayer > 1100.f)
				action = ACTION::AVANCE;
			else if (m_distanceToPlayer < 550.f)
			{
				action = ACTION::REPOSITIONNE;
			}
			else
			{
				int a = tools::iRand(0, 5);
				if (a == 0)
					action = ACTION::TURNAROUNDREMAKE;
				else
					action = ACTION::GOBACK;
				m_TPA = 0;
			}
		}
		else if (!m_lockP)
		{
				m_TPA = 1.8f;
				action = ACTION::IDLE;
			//---------------------------------
/*			 ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^																																						*/
/*			 | | | | | | | | | | | | | | | |																																						*/
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && t_stun > 0.1)
		{
			/*action = ACTION::DOUBLEHIT;*/
			/*m_life -= 10;*/
			action = ACTION::LONGHIT;
		}
	}

	if (physics->getCanMooved())
		action = HIT;
}

void IA_SPIKER::GestionAnim()
{
	if (physics->getComportement() == Died)
		animator->playAnim("DEATH", false);

	if (physics->getComportement() == Died) {}
	else if (m_timer < 1.2)
		animator->playAnim("SPAWN", false);
	else if (physics->getComportement() == HitStun || physics->getComportement() == Ejection || physics->getComportement() == KnockDown || physics->getComportement() == Grabed)
	{
		if (physics->getComportement() == KnockDown && m_tKnock>=0.8f)
			animator->playAnim("RELEVE", false);
		else
			animator->playAnim("PROJECTION", true);
	}
	else if (m_pattern == TROOLL)
	{
		animator->playAnim("IDLEMOB", true);
	}
	else if (m_pattern == REPOSITIIONNE)
		animator->playAnim("MOVE", true);
	else if (m_pattern == LONGHIIT && m_TPA < 0.55)
		animator->playAnim("MOVE", true);
	else if (m_pattern == LONGHIIT && m_TPA < 1.25)
		animator->playAnim("LONGHIT", false);
	else if (m_pattern == LONGHIIT)
		animator->playAnim("IDLEMOB", true);
	else if (m_pattern == GRAAB && m_TPA < 1.f)
	{
		animator->playAnim("IDLEMOB", true);
	}
	else if (m_pattern == GRAAB && m_TPA > 2.6)
		animator->playAnim("IDLEMOB", true);
	else if (m_pattern == GRAAB)
	{
		animator->playAnim("GRAB", false);
	}
	else if (action == CHARGE || m_pattern == TURNAROUNDD || m_pattern == GOBACKING || m_pattern == AVANCCE || m_pattern == REPOSITIONNE || m_pattern == TURNAROUNDREMAKEE)
	{
		animator->playAnim("MOVE", true);
		action = NONE;
	}
	else if ((m_pattern == MOVE || m_pattern == TURNED))
		animator->playAnim("MOVE", true);
	else if (body->getSpeed() == sf::Vector2f(0, 0) && !m_attacking && m_timer > 1.32 && m_pattern != TURNED)
		animator->playAnim("IDLEMOB", true);

	if (action == JAB || action == DOUBLEHIT || action == UPPERCUT || action == GRAB || action == LONGHIT || action == TROLL)
	{
		m_attacking = true;
		m_timerAtt = 0;
		m_tCharg = 0;
		m_timerIdle = 0;
		if (action == GRAB && m_TPA > 0.5f) {}
		else	body->setSpeed(sf::Vector2f(0, 0));
		m_lockP = true;
		action = NONE;
		m_dChargAtt = RANDOMCHARGETIMER;
	}

	if (m_attacking || m_pattern == HIIT || m_life <= 0) {}
	else if (TransTarget->getPosition().x - transform->getPosition().x < 0)
		physics->setLook(LookLeft);
	else
		physics->setLook(LookRight);

	if ((physics->getComportement() == HitStun || physics->getComportement() == Grabed) && animator->getCurrentFrame() == 2)
		animator->pause();
	else if (physics->getComportement() == Ejection && animator->getCurrentFrame() == 4)
		animator->pause();
	else if (physics->getComportement() == KnockDown && animator->getCurrentFrame() == 9 && m_tKnock <= 0.8f)
		animator->pause();
	else
		animator->play();

	if (m_pattern == GRAAB && m_TPA < 1.f)
	{
		sprite->getSprite().setColor(sf::Color(255, 255 - (0.85 * m_TPA * 255), 255 - (0.85 * m_TPA * 255), 255));
	}
	else if (m_pattern == GRAAB && m_TPA < 1.5f)
		sprite->getSprite().setColor(sf::Color(255, 0 + (0.85 * (m_TPA - 1) * 255) * 2, 0 + (0.85 * (m_TPA - 1) * 255) * 2, 255));
	else
		sprite->getSprite().setColor(sf::Color(255, 255, 255, 255));
}