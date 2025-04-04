#include "IA_Pattern.h"
#include "Physique.h"
#include "Camera.h"
/*                                                 INSTRUCTIONS																																												*/

/*              Bienvenu dans la partie I.A du projet Freak Squad, ce module est con�u pour �tre modifiable par n'importe quel																												*/
/*              membre de l'�quipe, bien �videment, c'est assez "programmer friendly".																																						*/
/*																																																											*/
/*              Pour effectuer des modifications du behaviour three :																																										*/
/*              ->Allez dans la fonction behaviour three du monstre correspondant																																							*/
/*              ->Tu vas trouver un encadr� point� par des fl�ches, c'est ici que se jouent toutes les priorit�s de calcul																													*/
/* 			    ->Il y a en derni�re condition: else if (!m_lock) c'est ici que tu dois mettres tes action avec tes conditions																												*/
/* 			    ->Si tu demandes de faire des actions qui te bloque sur un pattern (ex: une attaque), il faudra mettre une condition de d�blocage avec la commande : action = ACTION::BREAK;										*/
/*																																																											*/
/* 			    PS: si vous avez des questions, n'h�sitez pas � venir me voir			
																																					*/
					

//                                                                  %%%%#(#%%%%                         
//                                                               %%*            %%                      
//                                                             (%.          ..... %%                    
//                                               .....        %%        ...........#%                   
//                                                ...      *%%           ...........%%                  
//                                                       %%               ..........%%                  
//                                      %%%             %%                .........%%                   
//                                  (%%                 %#             ..........#%(                    
//                                #%                   #%          ........../%%%.                      
//                               (%   %%%/  .%%%%     %%         ......#%%%#... *%%%%,      ,%%         
//                                %(%(             #%%    ...    .....%%%.  ,%%         ..... .%        
//                                 %%%,      .#%%%*                        %%%%         .....  %/       
//                                %                (%%                          %%#           #%        
//                          /   ,%,             /%%                         ...    %% %%     %%         
//                            *,      ..../%%%%(       (%.    #%            .....   %%  .%%%            
//                                .../%%/             .%#.     %.            ....    %                  
//                               ..%%                 %%..     (%                    %*        /%       
//                              ..%%.               #%....      /%                   %%       *%        
//                               .#%.              %%             %%%                 %%    %%#         
//                                  #%%(          ,%                  %%%                               
//                                      *%%        %                     *%%                            
//                                        %%       (%                      ,%.                          
//                                       %%          %%                     ,%                          
//                                                     %%(                  %%                          
//                                                        %%              %%*                           
//                                                         %%           *                               
//                                                         %# 						            
IAMOTHER::IAMOTHER() //Constructeur compacte
{
	m_pattern = SPAWN; action = NONE; m_desactivation = false; m_esquive = false; m_dChargAtt = 0.f; c_spdBack = 100.f, c_spdWalk = 250.f, m_life = 100; t_stun = 10.f; c_timeSpawn = 0.f; m_position = { 0,0 }; m_target = { 0,0 }; m_distance = { 0,0 }; m_repos1 = { 0,0 }; m_repos2 = { 0,0 }; randGD
	m_attacking = false; m_dStun = 0.f; t_avEjecL = 0.f; t_lockReleve = 0.f; t_dead = 0.f; m_tLockAtt = 0.f; m_timerAtt = 0.f; m_addLongAtt = 0.f; m_timer = 0.f; m_distanceToPlayer = 0.f; m_dirGD = 0.f; m_distanceFlee = 0.f; m_distanceGo = 0.f; m_frappeAct = false; m_tTurn = 0.f; m_turnL = 0.f; m_initP = false; m_lockP = false; m_tCharg = 0.f;
	m_spdModif = 1.f;
	if (auto parent = getParents().lock())
		transform = parent->getComponents<ObjectTransform>(), body = parent->getComponents<RigidBody>(), transPlayer = parent->getParent()->getObjects(PLAYER)->getComponents<ObjectTransform>(); 
	m_frappe.setFillColor(sf::Color(255, 255, 255, 155)); m_frappe.setSize(sf::Vector2f(60.f, 50.f)); m_frappe.setPosition(sf::Vector2f(500, 500));
}

IAMOTHER::~IAMOTHER() //Destructeur
{
}

void IAMOTHER::update()
{
}

void IAMOTHER::draw()
{
}

/*Fonctions meres |																										                                        */
/*				  v																																				*/
/*------------------------------------																															*/
void IAMOTHER::walkToPlayer(float _spd) //Marche vers le joueur
{
	m_attacking = false;
	m_lockP = false;
	m_pattern = MOVE;
	body->setSpeed(m_position * _spd);
	m_lHitGo = false;
}

void IAMOTHER::backPlayer(float _spd)
{
	m_pattern = MOVE;
	body->setSpeed(-m_position * _spd);
	if (physics->m_typeMob == S)
	{
		if (TransTarget->getPosition().x - transform->getPosition().x < 0)
			body->setSpeed(sf::Vector2f(_spd, -m_position.y * _spd));
		else
			body->setSpeed(sf::Vector2f(-_spd, -m_position.y * _spd));
	}
}

void IAMOTHER::gaucheDroite(float _spd)
{
	m_pattern = GD;
	if (m_tTurn > m_dGD)
	{
		m_tTurn = 0;
		if (m_turnL)
			m_turnL = false;
		else
			m_turnL = true;
		randGD
	}
	
	if(m_turnL)
		body->setSpeed(sf::Vector2f(0,_spd)); // Multiplier la vitesse par le delta de temps pour une animation fluide
	else
		body->setSpeed(sf::Vector2f(0, -_spd));
	if (m_turnL)
		body->setSpeed(sf::Vector2f(_spd*0.6,0 )); // Multiplier la vitesse par le delta de temps pour une animation fluide
	else
		body->setSpeed(sf::Vector2f(-_spd,0));

}

void IAMOTHER::GDFollow(float _spd)
{
	m_pattern = MOVE;
	if (m_tTurn > m_dGD)
	{
		m_tTurn = 0;
		if (m_turnL)
			m_turnL = false;
		else
			m_turnL = true;
		randGD
	}

	if (transform->getPosition().y  < TransTarget->getPosition().y - 100)
	{
		m_turnL = true;
		body->setSpeed(sf::Vector2f(0, _spd));
	}
	else if (transform->getPosition().y > TransTarget->getPosition().y +100)
	{
		m_turnL = false;
		body->setSpeed(sf::Vector2f(0, -_spd));
	}
	else if (m_turnL)
		body->setSpeed(sf::Vector2f(0, _spd)); // Multiplier la vitesse par le delta de temps pour une animation fluide
	else
		body->setSpeed(sf::Vector2f(0, -_spd));
}

void IAMOTHER::chargeInit()
{
	m_doTour = false;
	m_saveCharPos = m_target;
	if (TransTarget->getPosition().x - transform->getPosition().x < 0)//charge cuache
		m_saveCharPos.x += 100;
	else //charge droite
		m_saveCharPos.x -= 100;

	m_saveCharPos.y += 1;
	m_pattern = CHARGING;
	m_lockP = true;
}

void IAMOTHER::charge(float _spd)
{
	m_TPA = 0;
	m_position = tools2::direction(transform->getPosition(), m_saveCharPos);
	body->setSpeed(m_position * _spd);
}

void IAMOTHER::jab() //Lance un jab
{
	m_pattern = JABB;
	if (physics->m_typeMob == T)
		m_tLockAtt = /*0.5*/0.7f;
	else
		m_tLockAtt = 0.64f;
}

void IAMOTHER::uppercut() //Lance uppercut
{
	m_pattern = UUPERCUT;
	m_tLockAtt = 0.56f;
}

void IAMOTHER::doubleHit() //Lance double coup
{
	m_pattern = DOUBLEHIIT;
	m_tLockAtt = 1.f;
}

void IAMOTHER::dash_Grab() //Lance dash & grab
{
	m_pattern = GRAAB;
	m_tLockAtt = 2.6f;
	if (physics->getLook() == LookLeft)
		m_saveCharPos = sf::Vector2f(transform->getPosition().x - 800.f , transform->getPosition().y);
	else
		m_saveCharPos = sf::Vector2f(transform->getPosition().x + 800.f, transform->getPosition().y);
}

void IAMOTHER::longHit() //Lance long coup
{
	m_pattern = LONGHIIT;
	m_tLockAtt = 1.9f;
	m_addLongAtt = 0;
}

void IAMOTHER::dontMove()
{
	if (auto PhysiqueSys = getParents().lock()->getComponents<Physique>()) {
		if (!PhysiqueSys->getCanMooved())
			body->setSpeed(sf::Vector2f(0, 0));
	}
	m_pattern = NONEE;
}

void IAMOTHER::duringLongHit()
{
	if (m_pattern == LONGHIIT)
	{
		if (m_TPA < 0.55)
		{
			if (m_distanceToPlayer < 500.f)
			{
				m_TPA = 0.55;
			}
			body->setSpeed(m_position * c_spdWalk * 1.5f);
			m_initLHit = false;
		}
		else
		{
			if (!m_initLHit)
			{
				int a = tools::iRand(0, 5);
				if (m_lHitGo)
					a = 0;
				m_initLHit = true;
				if (!m_2PLayer)
				{
					if (a == 2 && physicsTarget->getComportement() != Grab && physicsTarget->getComportement() != HitStun && physicsTarget->getComportement() != KnockDown)
						feinte = true;
					else feinte = false;
				}
				else
				{
					if (a == 2)
						feinte = true;
					else feinte = false;
				}
			}
			if (feinte)
				backPlayer(c_spdBack);
			else
				body->resetSpeed();
		}
	}
}

void IAMOTHER::duringGrab()
{
	if (m_pattern == GRAAB )
	{
		if (animator->getCurrentFrame() == 6 && !m_asDASH)
		{
			if (physics->getLook() == LookLeft && transform->getPosition().x - 800.f < TransTarget->getPosition().x && TransTarget->getPosition().x < transform->getPosition().x && CONDITIONCHARGEY)
			{
				transform->setPosition(TransTarget->getPosition());
			}
			else if (physics->getLook() == LookRight && transform->getPosition().x + 800.f > TransTarget->getPosition().x && TransTarget->getPosition().x > transform->getPosition().x && CONDITIONCHARGEY)
			{
				transform->setPosition(TransTarget->getPosition());
			}
			else
			{
				transform->setPosition(m_saveCharPos);
			}
			m_asDASH = true;
		}
	}
	else
		m_asDASH = false;
}

void IAMOTHER::fourberie()
{
	m_pattern = TROOLL;
	m_tLockAtt = 8.f;
}

void IAMOTHER::duringFourberie()
{
	if (m_pattern == TROOLL)
	{
		if (physics->getLook() == LookLeft && transform->getPosition().x - 550.f < TransTarget->getPosition().x && CONDITIONCHARGEY)
		{
			action = LONGHIT;
			m_timerAtt = 0.4f;
			m_lHitGo = true;
			longHit();
		}
		else if (physics->getLook() == LookRight && transform->getPosition().x + 550.f > TransTarget->getPosition().x && CONDITIONCHARGEY)
		{
			action = LONGHIT;
			m_timerAtt = 0.4f;
			m_lHitGo = true;
			longHit();
		}
		else if (m_distanceToPlayer<150.f)
			m_timerAtt = m_tLockAtt;
		else
			body->resetSpeed();
	}
}

void IAMOTHER::goBack()
{
	DGOBACK
	m_lockP = true;
	m_pattern = GOBACKING;
	if (TransTarget->getPosition().x < transform->getPosition().x) //Si � droite
	{
		if (TransTarget->getPosition().y < transform->getPosition().y) //Si bas
		{
			m_savePosGo = sf::Vector2f(transform->getPosition().x + 200.f, transform->getPosition().y + 200.f);
		}
		else
		{
			m_savePosGo = sf::Vector2f(transform->getPosition().x + 200.f, transform->getPosition().y - 200.f);
		}
	}
	else  //a gauche
	{
		if (TransTarget->getPosition().y < transform->getPosition().y) //Si bas
		{
			m_savePosGo = sf::Vector2f(transform->getPosition().x - 200.f, transform->getPosition().y + 200.f);
		}
		else
		{
			m_savePosGo = sf::Vector2f(transform->getPosition().x - 200.f, transform->getPosition().y - 200.f);
		}
	}
	m_dirToPos = tools2::direction(transform->getPosition(), m_savePosGo);
}

void IAMOTHER::goingtoObj(float _spd)
{
	if (m_pattern == GOBACKING || m_pattern == GOTOPLAYEER || m_pattern == REPOSITIIONNE || m_pattern == AVANCECRABBE || m_pattern == DASHANDJAAB || m_pattern == DASHANDBAACK || m_pattern == DASHAARR || m_pattern == GOTOUPPERCUUT || m_pattern == TURNAROUNDREMAKEE || m_pattern == BACKTOSPANWN)
	{
		if ((m_pattern == GOBACKING && m_TPA > 1.f) || m_pattern == REPOSITIIONNE)
			body->setSpeed(sf::Vector2f(m_dirToPos.x * _spd * m_spdModif, -m_dirToPos.y * _spd * m_spdModif));
		else if (m_pattern == DASHANDJAAB || m_pattern == DASHANDBAACK || m_pattern == DASHAARR)
			body->setSpeed(m_dirToPos * _spd * 1.3f);
		else if (m_pattern == TURNAROUNDREMAKEE)
		{
			if (!same)
			{
				m_timerTurn += tools::GetTimeDelta();
				body->setSpeed(m_dirToPos * _spd * 2.2f);
			}
			else
			{
				m_timerTurn2 += tools::GetTimeDelta();
				body->setSpeed(sf::Vector2f(m_dirToPos.x * _spd * 1.9f, -m_dirToPos.y * _spd * 1.9f));
			}
			if ((m_dirToPos.x < 0 && transform->getPosition().x < TransTarget->getPosition().x && !same) || m_timerTurn >1.f)
				same = true;
			else if ((m_dirToPos.x > 0 && transform->getPosition().x > TransTarget->getPosition().x && !same) || m_timerTurn > 1.f)
				same = true;
		}
		else
			body->setSpeed(m_dirToPos * _spd * m_spdModif);
	}
}

void IAMOTHER::goToPlayer()
{
	m_lockP = true;
	if (TransTarget->getPosition().x < transform->getPosition().x) //Si � droite
	{
		if (TransTarget->getPosition().y < transform->getPosition().y) //Si bas
		{
			m_savePosGo = sf::Vector2f(transform->getPosition().x - 200.f, transform->getPosition().y - 200.f);
		}
		else
		{
			m_savePosGo = sf::Vector2f(transform->getPosition().x - 200.f, transform->getPosition().y + 200.f);
		}
	}
	else  //a gauche
	{
		if (TransTarget->getPosition().y < transform->getPosition().y) //Si bas
		{
			m_savePosGo = sf::Vector2f(transform->getPosition().x + 200.f, transform->getPosition().y - 200.f);
		}
		else
		{
			m_savePosGo = sf::Vector2f(transform->getPosition().x + 200.f, transform->getPosition().y + 200.f);
		}
	}
	m_dirToPos = tools2::direction(transform->getPosition(), m_savePosGo);
	m_pattern = GOTOPLAYEER;
}

bool IAMOTHER::arrived()
{
	if (m_dirToPos.x>0 && transform->getPosition().x>m_savePosGo.x) //Si � droite
	{
		if (m_dirToPos.y > 0 && transform->getPosition().y > m_savePosGo.y) //Si bas
			return true;
		else if (m_dirToPos.y < 0 && transform->getPosition().y < m_savePosGo.y) //Si haut
			return true;
	}
	else if(m_dirToPos.x < 0 && transform->getPosition().x < m_savePosGo.x) //a gauche
	{
		if (m_dirToPos.y > 0 && transform->getPosition().y > m_savePosGo.y) //Si bas
			return true;
		else if (m_dirToPos.y < 0 && transform->getPosition().y < m_savePosGo.y) //Si haut
			return true;
	}
	return false;
}

void IAMOTHER::idle()
{
	if (physics->m_typeMob == C)
		m_randIdle = tools::iRand(120, 180);
	else if(physics->m_typeMob == T)
		m_randIdle = tools::iRand(140, 190);
	else
		m_randIdle = tools::iRand(110, 160);

	m_randIdle /= 100;
	m_spdModif = 1.f;
	m_TPA = 0;
	body->resetSpeed();
	m_pattern = IDLEE;
	m_lockP = true;
	if (m_2PLayer)
	{
		float a = 50000.f;
		float b = 50000.f;
		if (m_2PLayer)
		{
			if (physicsPlayer->getLife() > 0)
				a = tools2::distance(transPlayer->getPosition(), transform->getPosition());
			if (physicsPlayer2->getLife() > 0)
				b = tools2::distance(transPlayer2->getPosition(), transform->getPosition());
			if (a < b)
			{
				TransTarget = transPlayer;
			}
			else
			{
				TransTarget = transPlayer2;
			}
		}
	}
}

void IAMOTHER::initTurnAround()
{
	m_sCenter = TransTarget->getPosition();
	m_sRayon = m_distanceToPlayer;
	if (m_sRayon > 900.f) m_sRayon = 900.f;
	m_lockP = true;
	m_pattern = TURNAROUNDD;
	m_doTour = true;
	//m_sAngle = 0.f;
	if (m_dirToPos.x > 0 && transform->getPosition().x > m_savePosGo.x) //Si � droite
	{
		if (m_dirToPos.y > 0 && transform->getPosition().y > m_savePosGo.y) //Si bas
		{
			m_sAngle = 120.f;//sur
			m_sensD = 1;
		}
		else if (m_dirToPos.y < 0 && transform->getPosition().y < m_savePosGo.y) //Si haut
		{
			m_sAngle = 180.f;
			/*m_sAngle = 3.1415f * 360.f;*/
			m_sensD = 2;
		}
	}
	else if (m_dirToPos.x < 0 && transform->getPosition().x < m_savePosGo.x) //a gauche
	{
		if (m_dirToPos.y > 0 && transform->getPosition().y > m_savePosGo.y) //Si bas
		{
			m_sensD = 0;
			m_sAngle = 120.f; // sur
			/*m_sAngle = -3.1415f * 360.f*3.f;*/
		}
		else if (m_dirToPos.y < 0 && transform->getPosition().y < m_savePosGo.y) //Si haut
		{
			m_sensD = 3;
			m_sAngle = 180.f;
			/*m_sAngle = 3.1415f * 360.f * 3.f;*/
		}
	}
}

void IAMOTHER::turnAournd()
{
	if (m_pattern == TURNAROUNDD)
	{
		m_tTurnAround += tools::GetTimeDelta();
		
		//Mouvement circulaire, il a a juste a changer l'angle
		float x;
		float y;
		if (m_sensD == 0 || m_sensD == 1)
		{
			m_sAngle += tools::GetTimeDelta() * 60;
			x =/* m_sCenter.x +*/ m_sRayon * std::cos(m_sAngle * 3.14f / 180.f) * 1.2;
			y =/* m_sCenter.y +*/ m_sRayon * std::sin(m_sAngle * 3.14f / 180.f) * 0.63f;
		}
		else
		{
			m_sAngle += tools::GetTimeDelta() * 40;
			x =/* m_sCenter.x +*/ m_sRayon * std::cos(m_sAngle * 3.14f / 180.f) ;
			y =/* m_sCenter.y +*/ m_sRayon * std::sin(m_sAngle * 3.14f / 180.f) * 0.63f*0.6;
		}

		if( m_sensD == 1)
			body->setSpeed(sf::Vector2f(x, y));
		else if (m_sensD == 0)
			body->setSpeed(sf::Vector2f(-x, y));
		else if (m_sensD == 2)
			body->setSpeed(sf::Vector2f(x, -y));
		else if(m_sensD == 3)
			body->setSpeed(sf::Vector2f(-x, -y));
			

	}
}

void IAMOTHER::dash()
{
	m_pattern = DASSH;
	m_lockP = true;
}

void IAMOTHER::isDashing()
{
	if (m_pattern == DASSH)
	{
		if (m_dashG)
			body->setSpeed(sf::Vector2f(-c_spdWalk*1.7, 0));
		else
			body->setSpeed(sf::Vector2f(c_spdWalk*1.7, 0));
	}
}

void IAMOTHER::getGrab()
{
	if(physics->getComportement()==Grabed)
	{

	}
}

void IAMOTHER::mapCollision()
{
	physics->checkMask();
}

void IAMOTHER::behaviourTree()
{
}

void IAMOTHER::GestionAnim()
{
}

void IAMOTHER::initReposi()
{
	m_randReposi = tools::iRand(-20, 60);
	m_pattern = REPOSITIIONNE;
	m_lockP = true;
	if (TransTarget->getPosition().x < transform->getPosition().x) //Si � droite
	{
		if (TransTarget->getPosition().y < transform->getPosition().y) //Si bas
		{
			m_savePosGo = sf::Vector2f(transform->getPosition().x - 200.f, transform->getPosition().y + 800.f);
		}
		else
		{
			m_savePosGo = sf::Vector2f(transform->getPosition().x - 200.f, transform->getPosition().y - 800.f);
		}
	}
	else  //a gauche
	{
		if (TransTarget->getPosition().y < transform->getPosition().y) //Si bas
		{
			m_savePosGo = sf::Vector2f(transform->getPosition().x + 200.f, transform->getPosition().y + 800.f);
		}
		else
		{
			m_savePosGo = sf::Vector2f(transform->getPosition().x + 200.f, transform->getPosition().y - 800.f);
		}
	}
	m_dirToPos = tools2::direction(transform->getPosition(), m_savePosGo);
}

void IAMOTHER::initAvance()
{
	m_pattern = AVANCCE;
	m_lockP = true;
}

void IAMOTHER::avance()
{
	if (m_pattern == AVANCCE)
	{
		body->setSpeed(m_position * c_spdWalk);
	}
}

void IAMOTHER::doubleJab()
{
	m_pattern = DOUBLEJAAB;
	m_tLockAtt = 0.64f*2.f;
}

void IAMOTHER::initDash(bool _av)
{
	m_TPA = 0;
	if (_av)
		m_pattern = DASHAVANTT;
	else
		m_pattern = DASHAARRIER;
	m_lockP = true;
}

void IAMOTHER::initAvCrabe()
{
	m_TPA = 0;
	m_pattern = AVANCECRABBE;
	m_lockP = true;
	if (TransTarget->getPosition().x < transform->getPosition().x) //Si � droite
	{
		if (TransTarget->getPosition().y < transform->getPosition().y) //Si bas
		{
			m_savePosGo = sf::Vector2f(transform->getPosition().x - 200.f, transform->getPosition().y + 200.f);
		}
		else
		{
			m_savePosGo = sf::Vector2f(transform->getPosition().x - 200.f, transform->getPosition().y - 200.f);
		}
	}
	else  //a gauche
	{
		if (TransTarget->getPosition().y < transform->getPosition().y) //Si bas
		{
			m_savePosGo = sf::Vector2f(transform->getPosition().x + 200.f, transform->getPosition().y + 200.f);
		}
		else
		{
			m_savePosGo = sf::Vector2f(transform->getPosition().x + 200.f, transform->getPosition().y - 200.f);
		}
	}
	m_dirToPos = tools2::direction(transform->getPosition(), m_savePosGo);
}

void IAMOTHER::avCrabe()
{
	if (m_pattern == AVANCECRABBE)
	{
		if (m_TPA < 1.f/m_spdModif)
		{
			
		}
		else if (m_TPA < 1.8 && physics->m_typeMob == C)
		{
			body->resetSpeed();
		}
		else if (m_TPA < 2.8 && physics->m_typeMob == T)
		{
			body->resetSpeed();
		}
		else
		{
			initReposi();
		}
	}
}

void IAMOTHER::initDashAndJab()
{
	m_TPA = 0;
	if (action == DASHANDJAB)
		m_pattern = DASHANDJAAB;
	else if (action == DASHANDBACK)
		m_pattern = DASHANDBAACK;
	else
		m_pattern = DASHAARR;

	m_lockP = true;
	if (TransTarget->getPosition().x < transform->getPosition().x) //Si � droite
		m_savePosGo = sf::Vector2f(transform->getPosition().x - 200.f, transform->getPosition().y);
	else  //a gauche
		m_savePosGo = sf::Vector2f(transform->getPosition().x + 200.f, transform->getPosition().y);
	
	m_dirToPos = tools2::direction(transform->getPosition(), m_savePosGo);

	if (m_pattern == DASHAARR)
		m_dirToPos.x = -m_dirToPos.x;
}

void IAMOTHER::dashAndJab()
{
	if(m_pattern == DASHAARR)
		animator->playAnim("DASHARRIERE", false);

	if (m_pattern == DASHANDJAAB || m_pattern == DASHANDBAACK)
	{
		if (m_TPA < 0.5f)
		{
			animator->playAnim("DASHAVANT", false);
		}
		else
		{
			if (m_pattern == DASHANDJAAB)
			{
				action = JAB;
				jab();
			}
			else
			{
				m_pattern = BAACKT;
				backT();
			}
		}
	}
}

void IAMOTHER::initBackT()
{
	m_lockP = true;
	m_TPA = 0;
	m_pattern = BAACKT;
}

void IAMOTHER::backT()
{
	if (m_pattern == BAACKT)
	{
		if (abs(m_position.y) > 0.35f)
		{
			if (m_position.y > 0)
				m_position.y = 0.35f;
			else
				m_position.y = -0.35f;
		}
		body->setSpeed(-m_position * 200.f);
	}
}

void IAMOTHER::initGoUppercut()
{
	m_goUppercut = true;
	m_pattern = GOTOUPPERCUUT;
	m_lockP = true;
	if (TransTarget->getPosition().x < transform->getPosition().x) //Si � droite
		m_savePosGo = sf::Vector2f(transform->getPosition().x - 200.f, transform->getPosition().y);
	else  //a gauche
		m_savePosGo = sf::Vector2f(transform->getPosition().x + 200.f, transform->getPosition().y);

	m_dirToPos = tools2::direction(transform->getPosition(), m_savePosGo);
}

void IAMOTHER::goUppercut()
{
	if (m_pattern == GOTOUPPERCUUT)
	{
		if (m_TPA < 1)
		{
			animator->playAnim("MOVE", true);
		}
		else
		{
			m_spdModif = 1.5;
			action = AVANCECRABE;
			initAvCrabe();
		}
	}
}

void IAMOTHER::initTurnAroundRe()
{
	same = false;
	m_timerTurn = 0;
	m_timerTurn2 = 0;
	m_pattern = TURNAROUNDREMAKEE;
	m_lockP = true;
	if (TransTarget->getPosition().x < transform->getPosition().x) //Si � droite
	{
		if (TransTarget->getPosition().y < transform->getPosition().y) //Si bas
		{
			m_dirToPos = sf::Vector2f(-(float)sqrt(3)/2, 0.5);
		}
		else
		{
			m_dirToPos = sf::Vector2f(-(float)sqrt(3) / 2, -0.5);
		}
	}
	else  //a gauche
	{
		if (TransTarget->getPosition().y < transform->getPosition().y) //Si bas
		{
			m_dirToPos = sf::Vector2f((float)sqrt(3) / 2, 0.5);
		}
		else
		{
			m_dirToPos = sf::Vector2f((float)sqrt(3) / 2, 0.5);
		}
	}
}

void IAMOTHER::initBack2Spawn()
{
	m_pattern = BACKTOSPANWN;
	m_lockP = true;
	m_dirToPos = tools2::direction(transform->getPosition(), m_savePosGo);
}



//------------------------------------

void IAMOTHER::AllPointeur() //Def tous les pointeurs
{
	if (!m_initP)
	{
		if (auto parent = getParents().lock())
		{
			if (parent->l_Player.size() == 2)
				m_2PLayer = true;

			collid = parent->getComponents<Collider>();
			transform = parent->getComponents<ObjectTransform>();
			body = parent->getComponents<RigidBody>();
			//ombre = parent->getObjects("OmbreObj")->getComponents<Sprite>();

			if (!m_2PLayer)
			{
				TransTarget = parent->getParent()->getObjects(PLAYER)->getComponents<ObjectTransform>();
				physicsTarget = parent->getParent()->getObjects(PLAYER)->getComponents<Physique>();
			}
			else
			{
				transPlayer = parent->getParent()->getObjects("Player")->getComponents<ObjectTransform>();
				physicsPlayer = parent->getParent()->getObjects("Player")->getComponents<Physique>();
				transPlayer2 = parent->getParent()->getObjects("Player2")->getComponents<ObjectTransform>();
				physicsPlayer2 = parent->getParent()->getObjects("Player2")->getComponents<Physique>();
			}
			animator = parent->getComponents<Animation>();
			sprite = parent->getComponents<Sprite>();
			physics = parent->getComponents<Physique>();
			m_initP = true;

			if (m_2PLayer)
			{
				float a = 50000.f;
				float b = 50000.f;
				if (m_2PLayer)
				{
					if (physicsPlayer->getLife() > 0)
						a = tools2::distance(transPlayer->getPosition(), transform->getPosition());
					if (physicsPlayer2->getLife() > 0)
						b = tools2::distance(transPlayer2->getPosition(), transform->getPosition());
					if (a < b)
					{
						TransTarget = transPlayer;
					}
					else
					{
						TransTarget = transPlayer2;
					}
				}
			}

			if (physics->m_typeMob == H)
			{
				m_savePosGo = transform->getPosition();
			}
		}
	}
}

void IAMOTHER::acting() //Lance les actions selon le pattern mis dans l'arbre de comportement
{
	if (action == HIT)
		hit();
	else if (action == TROLL)
		fourberie();
	else if (action == AVANCE)
		initAvance();
	else if (action == TURNAROUND)
		initTurnAround();
	else if (action == AVANCECRABE)
		initAvCrabe();
	else if (action == GOTOUPPERCUT)
		initGoUppercut();
	else if (action == DASHANDJAB || action == DASHANDBACK || action == DASHARR)
		initDashAndJab();
	else if (action == REPOSITIONNE)
		initReposi();
	else if (action == GOBACK)
		goBack();
	else if (action == BACKT)
		initBackT();
	else if (action == GOTOPLAYER)
		goToPlayer();
	else if (action == LONGHIT)
		longHit();
	else if (action == DASHAVANT)
		initDash(true);
	else if (action == DASHARRIER)
		initDash(false);
	else if (action == GDFOLLOW)
		GDFollow(c_spdWalk);
	else if (action == IDLE)
		idle();
	else if (action == BACKTOSPAWN)
		initBack2Spawn();
	else if (action == WALKTOPLAYER || action == BREAK)
		walkToPlayer(m_spdLent);
	else if (action == BACK)
		backPlayer(c_spdBack);
	else if (action == GAUCHEDROITE)
		gaucheDroite(c_spdBack * 0.8);
	else if (action == CHARGE)
		chargeInit();
	else if (action == GRAB)
		dash_Grab();
	else if (action == UPPERCUT)
		uppercut();
	else if (action == TURNAROUNDREMAKE)
		initTurnAroundRe();
	else if (action == DOUBLEHIT)
		doubleHit();
	else if (action == JAB)
		jab();
	else if (action == DOUBLEJAB)
		doubleJab();
	else if (m_pattern == CHARGING)
		charge(c_spdWalk * 1.6f);
	else if (m_pattern == GD)
		gaucheDroite(c_spdBack/0.5);
}

void IAMOTHER::updatePakage()
{
	behaviourTree();  //Arbre de comportement
	acting();
	goingtoObj(c_spdWalk);
	turnAournd();
	duringLongHit();
	duringGrab();
	duringFourberie();
	/*		getGrab();*/
	mapCollision();
	avance();
	avCrabe();
	dashAndJab();
	GestionAnim();
	backT();
	goUppercut();
	if (auto parent = getParents().lock())
	{
		sf::Vector2f camPos = parent->getParent()->getObjects("Camera")->getComponents<Camera>()->getViewPos();
		float posX = transform->getPosition().x;
		float posZ = transform->getPosition().y;
		sf::Vector2f speed = body->getSpeed();
		sf::Vector2f posTmp{ 0.f,0.f };


		sf::Vector2f futurePos;//le y correspond au Z qui est la profondeur pour simplifier l'utilisation

		futurePos = sf::Vector2f(posX + (speed.x * 2 * tools::GetTimeDelta()), posZ + (speed.y * 2 * tools::GetTimeDelta()));
		if (physics->m_typeMob != H)
		{
			if ((m_position.x < 0 && body->getSpeed().x>0) || (m_position.x > 0 && body->getSpeed().x < 0))
			{
				if ((futurePos.x < camPos.x + 200 || futurePos.x> camPos.x + 1920 - 200) && (physics->getComportement() != Ejection && physics->getComportement() != KnockDown))
				{
					action = NONE;
					body->setSpeed(sf::Vector2f(m_position.x * 300.f, 0.f));
				}
				else if ((futurePos.x < camPos.x + 200 || futurePos.x> camPos.x + 1920 - 200))
					body->setSpeed(sf::Vector2f(0, body->getSpeed().y));
			}
			if ((m_position.y < 0 && body->getSpeed().y>0) || (m_position.y > 0 && body->getSpeed().y < 0))
			{
				if ((futurePos.y < camPos.y || futurePos.y> camPos.y + 1080) && (physics->getComportement() != Ejection && physics->getComportement() != KnockDown))
				{
					action = NONE;
					body->setSpeed(sf::Vector2f(0.f, m_position.y * 300.f));
				}
				else if ((futurePos.y < camPos.y || futurePos.y> camPos.y + 1080))
					body->setSpeed(sf::Vector2f(body->getSpeed().x, 0));
			}
		}
	}
	/*//std::cout << body->getSpeed().x << std::endl;*/

}

void IAMOTHER::InitGD()
{
	m_pattern = TURNED;
	m_dirGD = tools2::CalculAngle(transform->getPosition().x, transform->getPosition().y, transPlayer->getPosition().x, transPlayer->getPosition().y);
}

void IAMOTHER::dead() //Mise � mort
{
	t_dead += tools::GetTimeDelta();
	m_pattern = DEAD;

	transform->setZBuffer(TransTarget->getZBuffer() - 1);
	int a = (int)t_dead / 0.3;

	if (physics->m_typeMob == T)
	{
		if (t_dead > 3.5f)
		{
			m_active = false;
		}
	}
	else if (physics->m_typeMob == S)
	{
		if (t_dead > 2.5f)
			m_active = false;
	}
	else if (physics->m_typeMob == C)
	{
		if (t_dead > 2.5f)
			m_active = false;
	}
	else
	{
		if (t_dead > 3.5f)
		{
			transform->setPosition(m_savePosGo);
			physics->setLife(70);
			t_dead = 0;
			m_timer = 0.f;
			m_pattern = SPAWN;
			physics->setComportement(Iddle);
		}
	}
}

void IAMOTHER::hit() //Couleur selon les phases STUN / EJECTLEGER / AUSOL / RELEVE
{
	t_stun = 0;
	m_pattern = HIIT; 
}



