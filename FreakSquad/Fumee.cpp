#include "Fumee.h"
#include "CoffeeCore.hpp"

Fumee::Fumee()
{
	m_spriteSmoke.setTexture(RessourceManager::get()->getSceneTexture("smokeGrayLineless.png"));
	m_spriteSmoke.setPosition(m_positionSmoke);
	m_spriteSmoke.setScale(m_scaleSmoke);
	m_spriteSmoke.setColor(sf::Color(170, 170, 170, m_transSmoke));
	m_spriteSmoke.setOrigin(sf::Vector2f(383 / 2.0f, 359 / 2.0f));
}

Fumee::Fumee(sf::Sprite _spriteSmoke, sf::Vector2f _positionSmoke, sf::Vector2f _vitesseSmoke, sf::Vector2f _tmpvitesseSmoke, sf::Vector2f _scaleSmoke, float _targetAngle, float _tmpAngle2, float _tmpAngle3, float _red, float _green, float _blue)
{
	m_spriteSmoke = _spriteSmoke;
	m_positionSmoke = _positionSmoke;
	m_vitesseSmoke = _vitesseSmoke;
	m_tmpvitesseSmoke = _tmpvitesseSmoke;
	m_scaleSmoke = _scaleSmoke;
	m_transSmoke = 45.0f;
	m_targetAngle = _targetAngle;
	m_tmpAngle2 = _tmpAngle2;
	m_tmpAngle3 = _tmpAngle3;
	m_red = _red;
	m_green = _green;
	m_blue = _blue;
}

Fumee::~Fumee()
{
}

void Fumee::initFumee(std::shared_ptr<GameObject> _object)
{
	for (int i = 0; i < 1; i++)
	{
		std::shared_ptr<GameObject> fumee = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idfumee = std::shared_ptr<Identity>(new Identity("Fumee", OBJECT));
		std::shared_ptr<ObjectTransform> transformfumee = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 4640, 3100 }, STATIC));
		std::shared_ptr<Fumee> FumeeEnemy = std::shared_ptr<Fumee>(new Fumee());

		fumee->addComponents<Identity>(idfumee);
		fumee->addComponents<ObjectTransform>(transformfumee);
		fumee->addComponents<Fumee>(FumeeEnemy);

		_object->addGameObject(fumee);
	}
	for (int i = 0; i < 1; i++)
	{
		std::shared_ptr<GameObject> fumee = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idfumee = std::shared_ptr<Identity>(new Identity("Fumee", OBJECT));
		std::shared_ptr<ObjectTransform> transformfumee = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 13525, 3935 }, STATIC));
		std::shared_ptr<Fumee> FumeeEnemy = std::shared_ptr<Fumee>(new Fumee());

		fumee->addComponents<Identity>(idfumee);
		fumee->addComponents<ObjectTransform>(transformfumee);
		fumee->addComponents<Fumee>(FumeeEnemy);

		_object->addGameObject(fumee);
	}
	for (int i = 0; i < 1; i++)
	{
		std::shared_ptr<GameObject> fumee = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idfumee = std::shared_ptr<Identity>(new Identity("Fumee", OBJECT));
		std::shared_ptr<ObjectTransform> transformfumee = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 14795, 3230 }, STATIC));
		std::shared_ptr<Fumee> FumeeEnemy = std::shared_ptr<Fumee>(new Fumee());

		fumee->addComponents<Identity>(idfumee);
		fumee->addComponents<ObjectTransform>(transformfumee);
		fumee->addComponents<Fumee>(FumeeEnemy);

		_object->addGameObject(fumee);
	}
	for (int i = 0; i < 1; i++)
	{
		std::shared_ptr<GameObject> fumee = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idfumee = std::shared_ptr<Identity>(new Identity("Fumee", OBJECT));
		std::shared_ptr<ObjectTransform> transformfumee = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 19890, 4290 }, STATIC));
		std::shared_ptr<Fumee> FumeeEnemy = std::shared_ptr<Fumee>(new Fumee());

		fumee->addComponents<Identity>(idfumee);
		fumee->addComponents<ObjectTransform>(transformfumee);
		fumee->addComponents<Fumee>(FumeeEnemy);

		_object->addGameObject(fumee);
	}
}

void Fumee::update()
{
	m_timerRDM += tools::GetTimeDelta();
	m_keytimer += tools::GetTimeDelta();
	//variation de vitesse
	/*m_vitesseSmoke.x = tools::iRand(800.0f, 1000.0f);
	m_vitesseSmoke.y = tools::iRand(800.0f, 1000.0f);*/
	m_vitesseSmoke.x = tools::iRand(400.0f, 501.0f);
	m_vitesseSmoke.y = tools::iRand(400.0f, 501.0f);
	//angle de "recul"
	m_tmpAngle2 = tools::iRand(-10.0f, 10.0f);
	//angle de rotation
	m_tmpAngle3 = tools::iRand(0.0f, 360.0f);

	if (auto parent = getParents().lock())
	{
		std::shared_ptr<ObjectTransform> position = parent->getComponents<ObjectTransform>();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1) && m_red <255.0f)
		{
			m_red += 50 * tools::GetTimeDelta();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) && m_red > 0.0f)
		{
			m_red -= 50 * tools::GetTimeDelta();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3) && m_green < 255.0f)
		{
			m_green += 50 * tools::GetTimeDelta();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) && m_green > 0.0f)
		{
			m_green -= 50 * tools::GetTimeDelta();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) && m_blue < 255.0f)
		{
			m_blue += 50 * tools::GetTimeDelta();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) && m_blue > 0.0f)
		{
			m_blue -= 50 * tools::GetTimeDelta();
		}	
		/*if (m_choixPushFumer == 2)
		{
			if (m_keytimer > 0.0009f)
			{
				SMOKE.push_back(new Fumee(m_spriteSmoke, sf::Vector2f(position->getPosition().x + static_cast<float>(tools::iRand(-5, 5)), position->getPosition().y - 180.0f), sf::Vector2f(m_vitesseSmoke.x, m_vitesseSmoke.x), sf::Vector2f(1000.0f, 1000.0f), sf::Vector2f(0.05f, 0.05f), m_tmptAngle, m_tmpAngle2, m_tmpAngle3, m_red, m_green, m_blue));
				m_nbFumer += 1;
				m_keytimer = 0.0f;
			}
		}
		if (m_timerRDM >= 3.0f)
		{
			m_choixPushFumer = tools::iRand(1, 2 + 1);
			m_nbFumer = 0;
			m_timerRDM = 0;
		}*/
		if (m_keytimer > 0.01f)
		{
			SMOKE.push_back(new Fumee(m_spriteSmoke, sf::Vector2f(position->getPosition().x + static_cast<float>(tools::iRand(-45, 45)), (position->getPosition().y - 180.0f + static_cast<float>(tools::iRand(-5, 5)))), sf::Vector2f(m_vitesseSmoke.x, m_vitesseSmoke.x), sf::Vector2f(20.0f, 20.0f), sf::Vector2f(0.05f, 0.05f), m_tmptAngle, m_tmpAngle2, m_tmpAngle3, m_red, m_green, m_blue));
			m_keytimer = 0.0f;
		}
	}
	
	for (Fumee* s : SMOKE)
	{
		//augmente la taille de la fumée sur le temps
		if (s->m_scaleSmoke.x < 1.0f)
		{
			s->m_scaleSmoke.x += 1.0f * tools::GetTimeDelta();
		}
		if (s->m_scaleSmoke.y < 1.0f)
		{
			s->m_scaleSmoke.y += 1.0f * tools::GetTimeDelta();
		}
		if (s->m_vitesseSmoke.y > 0.0f)
		{
			//s->vitesseSmoke.x -= s->tmpvitesseSmoke.x * tools::GetTimeDelta();
			s->m_vitesseSmoke.y -= s->m_tmpvitesseSmoke.y * tools::GetTimeDelta();
		}

		//change de direction celon la pos de la sourie avec le "recul"
		s->m_positionSmoke.x += sin((3.1416 / 180) * (s->m_tmpAngle2)) * s->m_vitesseSmoke.x * tools::GetTimeDelta();
		s->m_positionSmoke.y += cos((3.1416 / 180) * (s->m_tmpAngle2)) * -s->m_vitesseSmoke.y * tools::GetTimeDelta();

		//baisse l'opaciter de la fumée
		s->m_transSmoke -= 70.0f * tools::GetTimeDelta();
		if (s->m_transSmoke <= 0.0f)
		{
			s->m_transSmoke = 0.0f;
		}

		//set tout les trucs
		s->m_spriteSmoke.setRotation(s->m_tmpAngle3);
		s->m_spriteSmoke.setPosition(s->m_positionSmoke);
		s->m_spriteSmoke.setScale(s->m_scaleSmoke);
		s->m_spriteSmoke.setColor(sf::Color(170, 170, 170, s->m_transSmoke));
	}
	for (int i = 0; i < SMOKE.size(); i++)
	{
		if (SMOKE[i]->m_transSmoke <= 0.0f)
		{
			SMOKE.erase(SMOKE.begin() + i);
		}
	}
}

void Fumee::draw()
{
	for (auto s : SMOKE)
	{
		window.draw(s->m_spriteSmoke);
	}
}
