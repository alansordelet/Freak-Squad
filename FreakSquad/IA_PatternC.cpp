#include "IA_PatternC.h"
#include"Physique.h"
#include"Sounds3D.h"

//    Uppercut : anti air, coup classique, crochet
//    Jab : normal hit, double hit

//    Concepts : Le rythme de jeu qui change : 
			
//				 Il juge le joueur : rythme lent, avance doucement, tourne autour doucement, recule doucement.
//				 Aggro : rythme moyen pour s'approcher du joueur, si le joueur fui; tant pis sinon approche en haut bas,  turn uppercut, dash + direct, dash + 2 pas arrières
//				 Enclanche : rythme rapide, jab, double jab, contre + direct
//				 Désengage : rythme moyen, dash arrière, 2 pas arrières

IA_CLEEVER::IA_CLEEVER()
{
	m_spdLent = 110.f;
	c_timeSpawn = 3.f;
	m_pattern = SPAWN;
	//----------------------------------------------------------
	m_life = 100;
	m_dStun = 0.3f;
	t_avEjecL = 1;  //Temps avant de reset l'éjection quand tu te prends plus
	c_spdBack = 100.f;
	c_spdWalk = 250.f;
	//----------------------------------------------------------
	t_stun = 3;
	t_lockReleve = 10;   //VaBloquer l'IA sur : être éjecter et se relever 
	m_timerAtt = 13;

	m_dChargAtt = RANDOMCHARGETIMER;
	int a = tools::iRand(0, 100);
	m_distanceFlee = 420.f + a;
	m_distanceGo = 900.f;
}

IA_CLEEVER::IA_CLEEVER(bool _zombi)
{
	/*m_timer = 1.2;*/
	c_timeSpawn = 3.f;
	m_pattern = SPAWN;
	//----------------------------------------------------------
	m_life = 100;
	m_dStun = 0.3f;
	t_avEjecL = 1;  //Temps avant de reset l'éjection quand tu te prends plus
	c_spdBack = 100.f;
	c_spdWalk = 250.f;
	//----------------------------------------------------------
	t_stun = 3;
	t_lockReleve = 10;   //VaBloquer l'IA sur : être éjecter et se relever 
	m_timerAtt = 13;

	m_dChargAtt = RANDOMCHARGETIMER;
	int a = tools::iRand(0, 100);
	m_distanceFlee = 420.f + a;
	m_distanceGo = 900.f;
}

IA_CLEEVER::~IA_CLEEVER()
{
}

void IA_CLEEVER::update()
{
	if (m_active)
	{
		AllPointeur();    //Def tous les pointeurs
		/*if (m_fuitePatt)
			//std::cout << "le probleme c'est la fuite";*/

		if (physics->getComportement() == HitStun)
			m_fuitePatt = true;
		if (m_distanceToPlayer > 500.f)
			m_fuitePatt = false;
		
		if (physics->getComportement() == KnockDown)
			m_tRelev += tools::GetTimeDelta();
		else
			m_tRelev = 0;
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
			m_goAttack += tools::GetTimeDelta() * 8.f;

		updatePakage();
		if (action != NONE)
			m_TPA = 0;
	
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

void IA_CLEEVER::draw()
{
}

void IA_CLEEVER::behaviourTree()
{
	float disttoCharge = tools2::distance(transform->getPosition(), m_saveCharPos);
	bool help = false;
	if ((m_dirToPos.y < 0 && transform->getPosition().y > TransTarget->getPosition().y- m_randReposi))
		help = true;
	if ((m_dirToPos.y > 0 && transform->getPosition().y < TransTarget->getPosition().y+ m_randReposi))
		help = true;
	//---------------------------------------------------- //Priorité des comportements
/*  		 | | | | | | | | | | | | | | |																																					*/
/*			 v v v v v v v v v v v v v v v																																					*/
			//---------------------------------      BEHAVIOUR TREE

	if (m_timer < /*-*/3.f/*-*/) //temps de spawn
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
		else if (m_TPA > (m_tLockAtt + /*-*/1.2f/*-*/) && m_attacking) //temps de repos après un coup
		{
			int a = tools::iRand(0, 3);
			if (a != 0)
				m_fuitePatt = true;
			m_TPA = 0;
			action = ACTION::BREAK;
		}
		else if (m_pattern == BAACKT && m_TPA > 1.3f)
		{
			action = ACTION::IDLE;
		}
		else if (m_pattern == TURNAROUNDREMAKEE && same && m_timerTurn2 > m_timerTurn)
		{
			action = ACTION::IDLE;
		}
		else if (m_pattern == DASHAARR && m_TPA > 0.5f)
		{
			action = ACTION::IDLE;
		}
		else if (m_pattern == REPOSITIIONNE && help && m_goUppercut)
		{
			action = ACTION::UPPERCUT;
		}
		else if (m_pattern == REPOSITIIONNE && help)
		{
			action = ACTION::IDLE;
		}
		else if (m_distanceToPlayer < 400.f && m_pattern == IDLEE && m_goAttack>0.2f)
		{
			int a = tools::iRand(0, 6);
			if (a == 0)
			{
				action = ACTION::UPPERCUT;
			}
			else if (a == 1 || a == 2)
			{
				action = ACTION::DOUBLEJAB;
			}
			else
			{
				action = ACTION::JAB;
			}
		}
		else if (m_pattern == IDLEE && m_TPA > /*-*/m_randIdle/*-*/)
		{
			if (m_distanceToPlayer > 1300.f)
			{
				action = ACTION::CHARGE;
			}
			else if (m_distanceToPlayer > 1100.f)
			{
				action = ACTION::TURNAROUNDREMAKE;
			}
		/*	else if (m_distanceToPlayer > 900.f)
			{
				action = ACTION::BACK;
			}*/
			else if (m_fuitePatt)
			{
				
				int a = tools::iRand(0, 6);
				if (a == 0 )
				{
					action = ACTION::DASHARR;
				}
				else
				{
					action = ACTION::BACKT;
				}
			}
			else if (m_distanceToPlayer < 1300.f)
			{
				if (CONDITIONCHARGEY && m_distanceToPlayer <700.f)
				{
					int a = tools::iRand(0, 7);
					/*if (a == 0 )
					{
						action = ACTION::DASHANDBACK;
					}
					else */if (a == 1)
					{
						action = ACTION::GOTOUPPERCUT;
					}
					else 
					{
						action = ACTION::DASHANDJAB;
					}
				}
				else
				{
					int a = tools::iRand(0, 2);
					if (a == 0)
						action = ACTION::AVANCECRABE;
					else
					{
						action = ACTION::REPOSITIONNE;
					}
				}
				
			}

		}
		else if (!m_lockP)
		{
			action = ACTION::IDLE;
			m_TPA = 1.8f;
			//---------------------------------
/*			 ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^																																						*/
/*			 | | | | | | | | | | | | | | | |																																						*/
		}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			{
				action = ACTION::BACKT;
			}
	}

	if (physics->getCanMooved())
		action = HIT;
}

void IA_CLEEVER::GestionAnim()
{
	if (physics->getComportement() == Died)
		animator->playAnim("DEATH", false);
	else if (physics->getComportement() == HitStun || physics->getComportement() == Ejection || physics->getComportement() == KnockDown || physics->getComportement() == Grabed)
	{
		if (physics->getComportement() == KnockDown && m_tRelev < 0.7f)
			animator->playAnim("RELEVE", false);
		else if (physics->getComportement() == KnockDown)
			animator->playAnim("IDLEMOB", true);
		else if (physics->getComportement() == Ejection)
			animator->playAnim("PROJECTION", false);
		else if (physics->getComportement() == HitStun)
			animator->playAnim("HITTRASH", false);
		else if (physics->getComportement() == Grabed)
			animator->playAnim("PROJECTION", false);
		else
			animator->playAnim("DEATH", false);
	}
	else if (m_pattern == SPAWN && m_timer < 0.4f)
		animator->playAnim("SPAWNCORDE", false);
	else if (m_pattern == DASHAVANTT || m_pattern == DASHANDBAACK)
		animator->playAnim("DASHAVANT", true);
	else if (m_pattern == SPAWN && m_timer < 1.2f)
		animator->playAnim("SPAWNTOMBE", false);
	else if (m_pattern == SPAWN && m_timer < 1.7f)
		animator->playAnim("SPAWNSOL", false);
	else if (m_pattern == SPAWN)
		animator->playAnim("IDLEMOB", true);
	else if (m_pattern == IDLEE)
		animator->playAnim("IDLEMOB", true);
	else if (m_pattern == UUPERCUT && m_TPA < m_tLockAtt)
		animator->playAnim("UPPERCUT", false);
	else if (m_pattern == UUPERCUT)
		animator->playAnim("IDLEMOB", true);
	else if(m_pattern == DOUBLEJAAB && m_TPA > m_tLockAtt)
		animator->playAnim("IDLEMOB", true);
	else if (m_pattern == DOUBLEJAAB)
		animator->playAnim("JAB", true);
	else if (m_pattern == JABB && m_TPA < m_tLockAtt)
		animator->playAnim("JAB", false);
	else if (m_pattern == JABB)
		animator->playAnim("IDLEMOB", true);
	else if (m_pattern == CHARGING)
		animator->playAnim("MOVE", true);
	else if (action == TURNAROUND || m_pattern == GOBACKING || m_pattern == GOTOPLAYEER || m_pattern == MOVE || m_pattern == TURNED || m_pattern == REPOSITIIONNE || (m_pattern == DASHANDBAACK && m_TPA>0.5f)|| m_pattern == BAACKT || m_pattern == AVANCECRABBE || m_pattern == TURNAROUNDREMAKEE)
		animator->playAnim("MOVE", true);
	else if (m_pattern == IDLEE)
		animator->playAnim("IDLEMOB", true);
	else if (m_pattern == TURNAROUNDD)
		animator->playAnim("MOVE", true);
	else if(m_pattern == DASHAARRIER)
		animator->playAnim("DASHARRIERE", true);

	else if (body->getSpeed() == sf::Vector2f(0, 0) && !m_attacking && m_timer > 1.32 && m_pattern != TURNED)
		animator->playAnim("IDLEMOB", true);

	if (action == JAB || action == DOUBLEHIT || action == UPPERCUT || action == GRAB || action == LONGHIT || action == TROLL || action == DOUBLEJAB)
	{
		if (auto parent = getParents().lock())
		{
			auto scene = parent->getParent();
			if (auto sound = scene->getObjects("gameMusic"))
			{
				sound->getComponents<Audio3D_Manager>()->getSound3D("woodhit2").play();
			}
		}
		m_goUppercut = false;
		m_attacking = true;
		m_timerAtt = 0;
		if (action != GRAB)
			body->setSpeed(sf::Vector2f(0, 0));
		m_lockP = true;
		m_dChargAtt = RANDOMCHARGETIMER;
		m_goAttack = 0;
	}
	if (m_attacking || m_pattern == HIIT || m_pattern == DASHANDJAAB || m_life <= 0) {}
	else if (TransTarget->getPosition().x - transform->getPosition().x < 0)
		physics->setLook(LookLeft);
	else
		physics->setLook(LookRight);

	if (physics->getComportement() == HitStun && m_CGetHit && physics->getLife()>0)
	{
		animator->setCurrentFrame(1);
		animator->play();
	}
	else if (physics->getComportement() == HitStun && !m_CGetHit && physics->getLife() > 0)
	{
		animator->setCurrentFrame(0);
		animator->play();
	}
	else if (physics->getComportement() == Grabed && animator->getCurrentFrame() == 0)
		animator->pause();
	else if (physics->getComportement() == KnockDown && animator->getCurrentFrame() == 6)
		animator->pause();
	else
		animator->play();

	/*if (physics->getComportement() == HitStun && m_CGetHit && animator->getCurrentFrame()==1)
	{
		animator->pause();
	}
	else if (physics->getComportement() == HitStun && m_CGetHit && animator->getCurrentFrame() == 0)
	{
		animator->pause();
	}*/
}