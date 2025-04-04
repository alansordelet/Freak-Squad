#include "Fly.h"
#include "Player.h"

Fly::Fly()
{
}

Fly::Fly(std::shared_ptr<ObjectTransform> _transform)
{
	m_positionFly = { 0.0f, 0.0f };
	m_vitesseFly = { 0.0f,0.0f };
	m_scaleFly = { 0.03f, 0.03f };
	m_originFly = { 379.0f / 2.0f, 385.0f / 2.0f };
	m_angleFly = 0.0f;
	m_fuite = false;
	m_transFly = 0.0f;
	m_timerChangeAngle = 0.0f;
	m_TMPtimerChangeAngle = 0.0f;
	m_vitesseAngle = 0.0f;
	m_TMPvitesseAngle = 0.0f;
	m_choixMouvement = 1;
	m_choixMouvement2 = 1;
	m_timerTrans = 0.0f;
	m_TMPtimerTrans = 0.0f;
	m_InverseTrans = false;

	m_spriteFly.setTexture(RessourceManager::get()->getSceneTexture("Mouche.png"));
	m_spriteFly.setPosition(m_positionFly);
	m_spriteFly.setScale(m_scaleFly);
	m_spriteFly.setOrigin(m_originFly);
	m_spriteFly.setColor(sf::Color(255.0f, 255.0f, 255.0f, 255.0f));

	recFly.setRadius(3);
	recFly.setPosition(m_positionFly);
	recFly.setOrigin(recFly.getRadius(), recFly.getRadius());
	recFly.setFillColor(sf::Color(0, 0, 0, 255.0f));

	//FLY.push_back(new Fly(m_spriteFly, sf::Vector2f(_transform->getPosition()), sf::Vector2f(_transform->getPosition())));
	FLY.push_back(new Fly(recFly, sf::Vector2f(_transform->getPosition()), sf::Vector2f(_transform->getPosition())));
}

Fly::Fly(sf::Sprite _spriteFly, sf::Vector2f _positionFly, sf::Vector2f _positionSuive)
{
	m_spriteFly = _spriteFly;
	m_positionFly = _positionFly;
	m_angleFly = 0.0f;
	m_angleFly = tools::frand(m_angleFly, -m_angleFly);
	m_vitesseFly = { 200.0f, 200.0f };
	m_positionSAVE = _positionSuive;
	m_fuite = false;
	m_transFly = 255.0f;
	m_timerChangeAngle = 0.0f;
	m_TMPtimerChangeAngle = tools::frand(0.1, 0.5);
	m_vitesseAngle = tools::iRand(50.0, 360.0f);
	m_TMPvitesseAngle = tools::iRand(50.0, 360.0f);
	m_choixMouvement = tools::iRand(1, 2 + 1);
	m_choixMouvement2 = tools::iRand(1, 2 + 1);
	m_timerTrans = 0.0f;
	m_TMPtimerTrans = tools::frand(0.7, 1.0f);
	m_InverseTrans = false;
}

Fly::Fly(sf::CircleShape _spriteFly, sf::Vector2f _positionFly, sf::Vector2f _positionSuive)
{
	recFly = _spriteFly;
	m_positionFly = _positionFly;
	m_angleFly = 0.0f;
	m_angleFly = tools::frand(m_angleFly, -m_angleFly);
	m_vitesseFly = { 200.0f, 200.0f };
	m_positionSAVE = _positionSuive;
	m_fuite = false;
	m_transFly = 100.0f;
	m_timerChangeAngle = 0.0f;
	m_TMPtimerChangeAngle = tools::frand(0.1, 0.5);
	m_vitesseAngle = tools::iRand(50.0, 360.0f);
	m_TMPvitesseAngle = tools::iRand(50.0, 360.0f);
	m_choixMouvement = tools::iRand(1, 2 + 1);
	m_choixMouvement2 = tools::iRand(1, 2 + 1);
	m_timerTrans = 0.0f;
	m_TMPtimerTrans = tools::frand(0.7, 1.0f);
	m_InverseTrans = false;
}

Fly::~Fly()
{
}

void Fly::initFly(std::shared_ptr<GameObject> _object)
{
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<GameObject> fly = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idfly = std::shared_ptr<Identity>(new Identity("Fly", OBJECT));
		std::shared_ptr<ObjectTransform> transformfly = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 1250.f,1430.f }, NON_STATIC));

		fly->addComponents<Identity>(idfly);
		fly->addComponents<ObjectTransform>(transformfly);
		std::shared_ptr<Fly> FLY = std::shared_ptr<Fly>(new Fly(transformfly));
		fly->addComponents<Fly>(FLY);
		_object->addGameObject(fly);
	}

	for (int i = 0; i < 7; i++)
	{
		std::shared_ptr<GameObject> fly = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idfly = std::shared_ptr<Identity>(new Identity("Fly", OBJECT));
		std::shared_ptr<ObjectTransform> transformfly = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 2803.0f,1580.f }, NON_STATIC));

		fly->addComponents<Identity>(idfly);
		fly->addComponents<ObjectTransform>(transformfly);
		std::shared_ptr<Fly> FLY = std::shared_ptr<Fly>(new Fly(transformfly));
		fly->addComponents<Fly>(FLY);
		_object->addGameObject(fly);
	}
	for (int i = 0; i < 7; i++)
	{
		std::shared_ptr<GameObject> fly = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idfly = std::shared_ptr<Identity>(new Identity("Fly", OBJECT));
		std::shared_ptr<ObjectTransform> transformfly = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 4100,2010 }, NON_STATIC));

		fly->addComponents<Identity>(idfly);
		fly->addComponents<ObjectTransform>(transformfly);
		std::shared_ptr<Fly> FLY = std::shared_ptr<Fly>(new Fly(transformfly));
		fly->addComponents<Fly>(FLY);
		_object->addGameObject(fly);
	}
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<GameObject> fly = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idfly = std::shared_ptr<Identity>(new Identity("Fly", OBJECT));
		std::shared_ptr<ObjectTransform> transformfly = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 4103,3179 }, NON_STATIC));

		fly->addComponents<Identity>(idfly);
		fly->addComponents<ObjectTransform>(transformfly);
		std::shared_ptr<Fly> FLY = std::shared_ptr<Fly>(new Fly(transformfly));
		fly->addComponents<Fly>(FLY);
		_object->addGameObject(fly);
	}
	for (int i = 0; i < 6; i++)
	{
		std::shared_ptr<GameObject> fly = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idfly = std::shared_ptr<Identity>(new Identity("Fly", OBJECT));
		std::shared_ptr<ObjectTransform> transformfly = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 8360,3700 }, NON_STATIC));

		fly->addComponents<Identity>(idfly);
		fly->addComponents<ObjectTransform>(transformfly);
		std::shared_ptr<Fly> FLY = std::shared_ptr<Fly>(new Fly(transformfly));
		fly->addComponents<Fly>(FLY);
		_object->addGameObject(fly);
	}
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<GameObject> fly = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idfly = std::shared_ptr<Identity>(new Identity("Fly", OBJECT));
		std::shared_ptr<ObjectTransform> transformfly = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 10430,3860 }, NON_STATIC));

		fly->addComponents<Identity>(idfly);
		fly->addComponents<ObjectTransform>(transformfly);
		std::shared_ptr<Fly> FLY = std::shared_ptr<Fly>(new Fly(transformfly));
		fly->addComponents<Fly>(FLY);
		_object->addGameObject(fly);
	}
	for (int i = 0; i < 6; i++)
	{
		std::shared_ptr<GameObject> fly = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idfly = std::shared_ptr<Identity>(new Identity("Fly", OBJECT));
		std::shared_ptr<ObjectTransform> transformfly = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 14100,4000 }, NON_STATIC));

		fly->addComponents<Identity>(idfly);
		fly->addComponents<ObjectTransform>(transformfly);
		std::shared_ptr<Fly> FLY = std::shared_ptr<Fly>(new Fly(transformfly));
		fly->addComponents<Fly>(FLY);
		_object->addGameObject(fly);
	}
	for (int i = 0; i < 6; i++)
	{
		std::shared_ptr<GameObject> fly = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idfly = std::shared_ptr<Identity>(new Identity("Fly", OBJECT));
		std::shared_ptr<ObjectTransform> transformfly = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 13570,2750 }, NON_STATIC));

		fly->addComponents<Identity>(idfly);
		fly->addComponents<ObjectTransform>(transformfly);
		std::shared_ptr<Fly> FLY = std::shared_ptr<Fly>(new Fly(transformfly));
		fly->addComponents<Fly>(FLY);
		_object->addGameObject(fly);
	}
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<GameObject> fly = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idfly = std::shared_ptr<Identity>(new Identity("Fly", OBJECT));
		std::shared_ptr<ObjectTransform> transformfly = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 14930,2720 }, NON_STATIC));

		fly->addComponents<Identity>(idfly);
		fly->addComponents<ObjectTransform>(transformfly);
		std::shared_ptr<Fly> FLY = std::shared_ptr<Fly>(new Fly(transformfly));
		fly->addComponents<Fly>(FLY);
		_object->addGameObject(fly);
	}
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<GameObject> fly = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idfly = std::shared_ptr<Identity>(new Identity("Fly", OBJECT));
		std::shared_ptr<ObjectTransform> transformfly = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 16450,2734 }, NON_STATIC));

		fly->addComponents<Identity>(idfly);
		fly->addComponents<ObjectTransform>(transformfly);
		std::shared_ptr<Fly> FLY = std::shared_ptr<Fly>(new Fly(transformfly));
		fly->addComponents<Fly>(FLY);
		_object->addGameObject(fly);
	}
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<GameObject> fly = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idfly = std::shared_ptr<Identity>(new Identity("Fly", OBJECT));
		std::shared_ptr<ObjectTransform> transformfly = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 19550,3150 }, NON_STATIC));

		fly->addComponents<Identity>(idfly);
		fly->addComponents<ObjectTransform>(transformfly);
		std::shared_ptr<Fly> FLY = std::shared_ptr<Fly>(new Fly(transformfly));
		fly->addComponents<Fly>(FLY);
		_object->addGameObject(fly);
	}
	for (int i = 0; i < 6; i++)
	{
		std::shared_ptr<GameObject> fly = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idfly = std::shared_ptr<Identity>(new Identity("Fly", OBJECT));
		std::shared_ptr<ObjectTransform> transformfly = std::shared_ptr<ObjectTransform>(new ObjectTransform({ 24620,4710 }, NON_STATIC));

		fly->addComponents<Identity>(idfly);
		fly->addComponents<ObjectTransform>(transformfly);
		std::shared_ptr<Fly> FLY = std::shared_ptr<Fly>(new Fly(transformfly));
		fly->addComponents<Fly>(FLY);
		_object->addGameObject(fly);
	}
}

float Fly::length(sf::Vector2f _vec)
{
	return std::sqrt(std::pow(_vec.x, 2) + std::pow(_vec.y, 2));
}

sf::Vector2f Fly::limit(sf::Vector2f _vec, float _limit)
{
	float mag = length(_vec);
	if (mag > _limit)
	{
		_vec /= mag;
		_vec *= _limit;
	}
	return _vec;
}

sf::Vector2f Fly::seek(sf::Vector2f _target, sf::Sprite _sprite, float _maxspeed, sf::Vector2f _velocity)
{
	sf::Vector2f desired = _target - _sprite.getPosition();
	desired = limit(desired, _maxspeed);
	return (desired - _velocity);
}

sf::Vector2f Fly::seek2(sf::Vector2f _target, sf::CircleShape _sprite, float _maxspeed, sf::Vector2f _velocity)
{
	sf::Vector2f desired = _target - _sprite.getPosition();
	desired = limit(desired, _maxspeed);
	return (desired - _velocity);
}

void Fly::update()
{
	for (Fly* f : FLY)
	{
		if (f->m_fuite == false)
		{
			f->m_timerTrans += tools::GetTimeDelta();
			f->m_timerChangeAngle += tools::GetTimeDelta();
			if (f->m_timerChangeAngle >= f->m_TMPtimerChangeAngle)
			{
				f->m_choixMouvement = tools::iRand(1, 2 + 1);
				f->m_choixMouvement2 = tools::iRand(1, 2 + 1);
				f->m_angleFly = tools::frand(f->m_angleFly, -f->m_angleFly);
				f->m_TMPvitesseAngle = tools::iRand(3000.0, 4000.0f);
				f->m_vitesseAngle = tools::iRand(50.0f, 360.0f);
				f->m_TMPtimerChangeAngle = tools::frand(0.2, 0.4);
				f->m_timerChangeAngle = 0.0f;
			}
			if (f->m_choixMouvement == 1)
			{
				f->m_vitesseAngle += f->m_TMPvitesseAngle * tools::GetTimeDelta();
			}
			if (f->m_choixMouvement == 2)
			{
				f->m_vitesseAngle -= f->m_TMPvitesseAngle * tools::GetTimeDelta();
			}

			f->m_angleFly += f->m_vitesseAngle * tools::GetTimeDelta();

			if (f->m_choixMouvement2 == 1)
			{
				f->m_positionFly.x += sin((3.1416 / 180) * f->m_angleFly) * f->m_vitesseFly.x * tools::GetTimeDelta();
				f->m_positionFly.y += cos((3.1416 / 180) * f->m_angleFly) * -f->m_vitesseFly.y * tools::GetTimeDelta();
			}

			if (f->m_choixMouvement2 == 2)
			{
				f->m_positionFly.x -= sin((3.1416 / 180) * f->m_angleFly) * f->m_vitesseFly.x * tools::GetTimeDelta();
				f->m_positionFly.y -= cos((3.1416 / 180) * f->m_angleFly) * -f->m_vitesseFly.y * tools::GetTimeDelta();
			}

			if (f->m_timerTrans >= f->m_TMPtimerTrans && f->m_transFly > 1.0f)
			{
				f->m_transFly -= 1000.0f * tools::GetTimeDelta();
			}
			if (f->m_transFly <= 1.0f)
			{
				f->m_InverseTrans = true;
				f->m_timerTrans = 0.0f;
			}
			if (f->m_InverseTrans == true)
			{
				f->m_transFly += 10000000.0f * tools::GetTimeDelta();
				f->m_positionFly.x = f->m_positionSAVE.x;
				f->m_positionFly.y = f->m_positionSAVE.y;
				f->m_InverseTrans = false;
			}
			if (f->m_transFly > 100.0f)
			{
				f->m_transFly = 100.0f;
			}

			f->recFly.setPosition(f->m_positionFly);
			f->recFly.setRotation(-f->m_angleFly + 90);
		}
		for (decltype(auto) i : GameObject::l_Player)
		{
			auto objTransform = i->getComponents<ObjectTransform>()->getPosition();


			if (tools::Circle_Collision(sf::Vector2f(f->m_positionFly.x, f->m_positionFly.y + 200), objTransform, 80, 80))
			{
				f->m_fuite = true;
			}

			if (f->m_fuite == true)
			{
				sf::Vector2f vecteur;
				float norme;
				vecteur = objTransform - f->m_positionFly;
				f->m_angleFly = atan2(-vecteur.y, -vecteur.x);

				f->m_transFly -= 200.0f * tools::GetTimeDelta();
				sf::Vector2f velocity = seek2(objTransform, f->recFly, 1.5f, f->m_vitesseFly);
				f->m_vitesseFly = velocity;
				f->m_vitesseFly = limit(f->m_vitesseFly + velocity, 1.5f);
				f->recFly.move(-f->m_vitesseFly * 0.2f);
				f->recFly.setRotation(f->m_angleFly * 180 / 3.1416);
			}

		}

		if (f->m_transFly <= 0.0f)
		{
			f->m_transFly = 0.0f;
		}

		f->recFly.setFillColor(sf::Color(0, 0, 0, f->m_transFly));
	}
	for (int i = 0; i < FLY.size(); i++)
	{
		if (FLY[i]->m_transFly <= 0.0f)
		{
			FLY.erase(FLY.begin() + i);
		}
	}
}

void Fly::draw()
{
	for (Fly* f : FLY)
	{
		window.draw(f->recFly);
	}
}