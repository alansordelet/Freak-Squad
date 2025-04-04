//#include "IADictionnary.h"
//#include"Game.h"
//#include"CoffeeCore.hpp"
//#include"IA_Pattern.h"
//#include"Physique.h"
////#include"IADictionnary.h"
////
////void IAFonction::walkToPlayer()
////{
////
////	m_attacking = false;
////	m_lockP = false;
////	m_pattern = MOVE;
////	body->setSpeed(m_position * _spd);
////	m_lHitGo = false;
////}
//
//void IAFonction::mooveToPlay(Game* _game, const std::shared_ptr<RigidBody>& _body, const std::shared_ptr<IAMOTHER>& _ia)
//{
//	std::shared_ptr<GameObject> target;
//	for (auto& it : GameObject::l_Player)
//	{
//		_ia->m_attacking = false;
//		_ia->m_lockP = false;
//		_ia->m_pattern = MOVE;
//		_body->setSpeed(_ia->m_position * 250.f);
//		_ia->m_lHitGo = false;
//	}
//}
//
//void IAFonction::back(Game* _game, const std::shared_ptr<RigidBody>& _body, const std::shared_ptr<IAMOTHER>& _ia)
//{
//	_body->setSpeed( sf::Vector2f( - 250.f,0));
//	/*_ia->m_pattern = MOVE;
//	_ia->body->setSpeed(-_ia->m_position * _ia->c_spdBack);
//	if (_ia->physics->m_typeMob == T)
//	{
//		if (_ia->transPlayer->getPosition().x - _ia->transform->getPosition().x < 0)
//			_ia->body->setSpeed(sf::Vector2f(_ia->c_spdBack, -_ia->m_position.y * _ia->c_spdBack));
//		else
//			_ia->body->setSpeed(sf::Vector2f(-_ia->c_spdBack, -_ia->m_position.y * _ia->c_spdBack));
//	}*/
//}
//
//void IAFonction::monte(Game* _game, const std::shared_ptr<RigidBody>& _body, const std::shared_ptr<IAMOTHER>& _ia)
//{
//	_body->setSpeed(sf::Vector2f(0, -250.f));
//}
//
//bool IAFonction::cMooveToPlayTrash(Game* _game, const std::shared_ptr<IAMOTHER>& _ia)
//{
//	if (_ia->m_distanceToPlayer > 500.f) return true;
//	return false;
//}
//
//bool IAFonction::cMonteTrash(Game* _game, const std::shared_ptr<IAMOTHER>& _ia)
//{
//	if (_ia->m_distanceToPlayer < 200.f) return true;
//	return false;
//}
