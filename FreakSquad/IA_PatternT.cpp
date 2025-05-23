#include "IA_PatternT.h"
#include"Physique.h"
#include"Sounds3D.h"
IA_TRASHER::IA_TRASHER()
{
	m_timer = 0.0f;
	m_pattern = SPAWN;
	//----------------------------------------------------------
	m_life = 80;
	m_dStun = 0.3f;
	t_avEjecL = 1;  //Temps avant de reset l'�jection quand tu te prends plus
	c_spdBack = 500.f;
	c_spdWalk = 250.f;
	//----------------------------------------------------------
	t_stun = 3;
	t_lockReleve = 10;   //VaBloquer l'IA sur : �tre �jecter et se relever 
	m_timerAtt = 13;

	m_dChargAtt = RANDOMCHARGETIMER;
	int a = tools::iRand(0, 100);
	m_distanceFlee = 420.f + a;
	m_distanceGo = 900.f;
}

IA_TRASHER::~IA_TRASHER()
{
}

void IA_TRASHER::behaviourTree()
{
	float disttoCharge = tools2::distance(transform->getPosition(), m_saveCharPos);
	bool help = false; 
	if ((m_dirToPos.y < 0 && transform->getPosition().y > TransTarget->getPosition().y))
		help = true;
	if ((m_dirToPos.y > 0 && transform->getPosition().y < TransTarget->getPosition().y))
		help = true;
	//---------------------------------------------------- //Priorit� des comportements
/*  		 | | | | | | | | | | | | | | |																																					*/
/*			 v v v v v v v v v v v v v v v																																					*/
			//---------------------------------      BEHAVIOUR TREE

	if (m_timer < /*-*/1.32f/*-*/) //temps de spawn
		m_pattern = SPAWN;
	
	else
	{
		if (physics->getComportement() == Died)
			dead();
		else if (m_TPA > /*-*/m_dStun/*-*/ && m_lockP && m_pattern == HIIT)
		{
			m_TPA = 0;
			action = ACTION::BREAK;
		}
		else if (m_TPA > (m_tLockAtt + /*-*/2.f/*-*/)&& m_attacking) //temps de repos apr�s un coup
		{
			m_TPA = 0;
			action = ACTION::BREAK;
		}
		else if (m_pattern == CHARGING && m_distanceToPlayer < 300 && abs(transform->getZBuffer() - TransTarget->getZBuffer()) < 50)
		{
			action = ACTION::IDLE;
		}
		else if (m_pattern == TURNAROUNDREMAKEE && same && ((m_dirToPos.y >0 && transform->getPosition().y<TransTarget->getPosition().y) || (m_dirToPos.y < 0 && transform->getPosition().y > TransTarget->getPosition().y)))
		{
			action = ACTION::IDLE;
		}
		else if (m_pattern == CHARGING && disttoCharge < 10)
		{
			action = ACTION::IDLE;
		}
		else if (m_pattern == REPOSITIIONNE && help )
		{
			action = ACTION::IDLE;
		}
		else if (m_pattern == IDLEE && m_TPA > /*-*/3.f/*-*/) //Temps d'idle pr�t � attaquer
		{
			if (m_distanceToPlayer < /*-*/650.f/*-*/)
			{
				if (CONDITIONCHARGEY)
				{
					int a = tools::iRand(0, /*-*/8/*-*/);
					if (a == 0)
					{
						action = ACTION::CHARGE;
					}
					else
						m_TPA = 2.f;
				}
				else
				{
					int a = tools::iRand(0, /*-*/4/*-*/);
					if (a == 0)
						action = ACTION::GOBACK;
					else
						action = ACTION::REPOSITIONNE;
				}
			}
			else
			{
				int a = tools::iRand(0, /*-*/14/*-*/);
				if (a == 0 && !m_doTour)
				{
					action = ACTION::TURNAROUNDREMAKE;
				}
				else if (a == 1 || a == 2 || a == 3)
				{
					action = ACTION::GOBACK;
				}
				else if (a < 7)
				{
					action = ACTION::AVANCECRABE;
				}
				else 
				{
					action = ACTION::CHARGE;
				}
			}

		}
		else if (m_pattern == TURNAROUNDD && m_TPA > m_randIdle)
		{
			action = ACTION::IDLE;
		}
		else if (m_pattern == IDLEE && m_goAttack > /*-*/0.5f/*-*/) //temps pour attaquer en idle
		{
			if (auto parent = getParents().lock())
			{
				auto scene = parent->getParent();
				if (auto sound = scene->getObjects("gameMusic"))
				{
					sound->getComponents<Audio3D_Manager>()->getSound3D("woodhit").play();
				}
			}
			ATTTRASH
		}
		else if (m_pattern == GOBACKING && m_TPA > m_dGoBack)
		{
			action = ACTION::IDLE;
		}
		else if (!m_lockP)
		{
			action = ACTION::IDLE;
			m_TPA = 2.8;
			//---------------------------------
/*			 ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^																																						*/
/*			 | | | | | | | | | | | | | | | |																																						*/
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && t_stun > 0.1)
		{
			physics->setLife(-10);
		}

	}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			action = ACTION::TURNAROUNDREMAKE;

	if (physics->getCanMooved())
		action = HIT;
}

void IA_TRASHER::update()
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
			if (m_pattern == IDLEE && CONDITIONCHARGEY && m_distanceToPlayer < 500.f) // rajouter le check Zbuffer)
				m_goAttack += tools::GetTimeDelta();
			else if (m_pattern != CHARGING)
				m_goAttack = 0;
			else
				m_goAttack = 50.f;
	
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
			//ombre->setActive(false);
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

void IA_TRASHER::draw()
{
}

void IA_TRASHER::GestionAnim()
{
	if (physics->getComportement() == Died)
		animator->playAnim("DEATH", false);
	else if (physics->getComportement() == HitStun || physics->getComportement() == Ejection || physics->getComportement() == KnockDown || physics->getComportement() == Grabed)
	{
		if (physics->getComportement() == KnockDown && m_tReleve > 0.3)
			animator->playAnim("RELEVE", false);
		else
			animator->playAnim("DEATH", false);
	}
	else if (m_pattern == SPAWN && m_timer < 1.32f)
		animator->playAnim("SPAWN", false);
	else if (m_pattern == IDLEE)
		animator->playAnim("IDLEMOB", true);
	else if (m_pattern == DOUBLEHIIT && m_TPA > m_tLockAtt)
		animator->playAnim("IDLEMOB", true);
	else if (m_pattern == DOUBLEHIIT)
		animator->playAnim("DOUBLEHIT", false);
	else if (m_pattern == JABB && m_TPA > m_tLockAtt)
		animator->playAnim("IDLEMOB", true);
	else if (m_pattern == JABB)
		animator->playAnim("JAB", false);
	else if (action == CHARGE || action == TURNAROUND || m_pattern == GOBACKING || m_pattern == GOTOPLAYEER || m_pattern == MOVE || m_pattern == TURNED || m_pattern == REPOSITIIONNE || (m_pattern == AVANCECRABBE && m_TPA < 1.f)||m_pattern == TURNAROUNDREMAKEE)
		animator->playAnim("MOVE", true);
	else if (m_pattern == IDLEE)
		animator->playAnim("IDLEMOB", true);
	else if (m_pattern == TURNAROUNDD)
		animator->playAnim("MOVE", true);
	else if (body->getSpeed() == sf::Vector2f(0, 0) && !m_attacking && m_timer > 1.32 && m_pattern != TURNED)
		animator->playAnim("IDLEMOB", true);

	if (action == JAB || action == DOUBLEHIT || action == UPPERCUT || action == GRAB || action == LONGHIT || action == TROLL)
	{

		m_attacking = true;
		m_timerAtt = 0;
		if (action != GRAB)
			body->setSpeed(sf::Vector2f(0, 0));
		m_lockP = true;
		m_dChargAtt = RANDOMCHARGETIMER;
		m_goAttack = 0;
	}
	if (m_attacking || m_pattern == HIIT || m_life <= 0) {}
	else if (TransTarget->getPosition().x - transform->getPosition().x < 0)
		physics->setLook(LookLeft);
	else
		physics->setLook(LookRight);

	if ((physics->getComportement() == Grabed || physics->getComportement() == HitStun) && animator->getCurrentFrame() == 1)
		animator->pause();
	else if (physics->getComportement() == KnockDown && animator->getCurrentFrame() == 6 )
		animator->pause();
	else
		animator->play();
}