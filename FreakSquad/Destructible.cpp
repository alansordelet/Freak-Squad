#include "Destructible.h"
#include "Shake.h"

int Destructible::s_idDestructible{0};


Destructible::Destructible()
{
	m_intRect = { 0,0,0,0 };
	m_pv = 4;
	m_timerHit = 0.0f;
	m_mass = 250.0f;
	m_hasDestroyed = false;
	m_isHit = false;
	m_activeSet = false;
	m_textureDestroyedSet = false;
	m_yBoing = 0.0f;
	m_timerBlinking = 0.0f;
	m_timerDepop = 0.0f;
}

Destructible::Destructible(sf::IntRect _intRect, EnumAsset _type)
{
	m_hasDestroyed = false;
	m_textureDestroyedSet = false;
	m_isHit = false;
	m_activeSet = false;
	m_timerHit = 0.0f;
	m_pv = 4;
	m_intRect = _intRect;
	type = _type;
	m_mass = 250.0f;
	m_yBoing = 0.0f;
	m_timerDepop = 0.0f;
	m_timerBlinking = 0.0f;
}

Destructible::~Destructible()
{
}

std::shared_ptr<GameObject> Destructible::createDestructible(EnumAsset _type, float _posX, float _posY)
{
	s_idDestructible++;

	std::string name = "";

	if (_type == FRIGO)
		name = "Frigo" + std::to_string(s_idDestructible);
	else if (_type == MACHINELAVER)
		name = "MachineLaver" + std::to_string(s_idDestructible);
	else if (_type == DISTRIBUTEUR)
		name = "Distributeur" + std::to_string(s_idDestructible);

	std::shared_ptr<GameObject> destructible = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> iddestructible = std::shared_ptr<Identity>(new Identity(name, COLLECTIBLE));
	std::shared_ptr<Sprite> spritedestructible = std::shared_ptr<Sprite>(new Sprite());


	if (_type == FRIGO)
		spritedestructible->setTexture(RessourceManager::get()->getSceneTexture("collectibe_frigo1.png"));
	else if (_type == MACHINELAVER)
		spritedestructible->setTexture(RessourceManager::get()->getSceneTexture("collectibe_machine1.png"));
	else if (_type == DISTRIBUTEUR)
		spritedestructible->setTexture(RessourceManager::get()->getSceneTexture("collectible_distributeur1.png"));


		std::shared_ptr<RigidBody> rigidBody = std::shared_ptr<RigidBody>(new RigidBody());
		std::shared_ptr<ObjectTransform> transformdestructible = std::shared_ptr<ObjectTransform>(new ObjectTransform({ _posX,_posY }, _posY + spritedestructible->getSprite().getGlobalBounds().height + 30.0f, STATIC));
		std::shared_ptr<Destructible> Colliderdestructible = std::shared_ptr<Destructible>(new Destructible({ static_cast<int>(_posX), static_cast<int>(_posY), static_cast<int>(spritedestructible->getSprite().getGlobalBounds().width), static_cast<int>(spritedestructible->getSprite().getGlobalBounds().height) }, _type));
		std::shared_ptr<Shake> Shakedestructible = std::shared_ptr<Shake>(new Shake());


		destructible->addComponents<Identity>(iddestructible);
		destructible->addComponents<RigidBody>(rigidBody);
		destructible->addComponents<ObjectTransform>(transformdestructible);
		destructible->addComponents<Destructible>(Colliderdestructible);
		destructible->addComponents<Shake>(Shakedestructible);
		destructible->addComponents<Sprite>(spritedestructible);

		return destructible;
}

int Destructible::getPVDestructible()
{
	return m_pv;
}

void Destructible::setPVDestructible(int _pv)
{
	m_pv = _pv;
}

void Destructible::setHit(const bool _hit)
{
	m_isHit = _hit;
}

bool Destructible::getIsHit()
{
	return m_isHit;
}

void Destructible::setDestroyed()
{
	m_hasDestroyed = true;
	m_textureDestroyedSet = true;
}

void Destructible::update()
{
	switch (type)
	{
	case(FRIGO):
		if (m_textureDestroyedSet)
		{
			if (auto parent = getParents().lock())
			{
				parent->getComponents<Sprite>()->setTexture(RessourceManager::get()->getSceneTexture("collectibe_frigo2.png"));
				m_textureDestroyedSet = false;
			}
		}
		break;

	case(MACHINELAVER):
		if (m_textureDestroyedSet)
		{
			if (auto parent = getParents().lock())
			{
				parent->getComponents<Sprite>()->setTexture(RessourceManager::get()->getSceneTexture("collectibe_machine2.png"));
				m_textureDestroyedSet = false;
			}
		}
		break;

	case(DISTRIBUTEUR):
		if (m_textureDestroyedSet)
		{
			if (auto parent = getParents().lock())
			{
				parent->getComponents<Sprite>()->setTexture(RessourceManager::get()->getSceneTexture("collectible_distributeur2.png"));
				m_textureDestroyedSet = false;
			}
		}
		break;
	default:
		break;
	}

	if (m_isHit)
	{
		m_timerHit += tools::GetTimeDelta();

		if (m_timerHit > 0.2f)
		{
			m_isHit = false;
			m_timerHit = 0.0f;
		}
	}


	if (m_hasDestroyed)
	{
		m_timerBlinking += tools::GetTimeDelta();
		m_timerDepop += tools::GetTimeDelta();

		if (auto parent = getParents().lock())
		{
			if (m_timerDepop > 0.6f)
				parent->setActive(false);

			if (parent->getComponents<ObjectTransform>()->getPosition().y >= m_yBoing)
			{
				parent->getComponents<RigidBody>()->setSpeed({ (parent->getComponents<RigidBody>()->getSpeed().x * 0,95.f), parent->getComponents<RigidBody>()->getSpeed().y - 115.f });
			}
			

			parent->getComponents<RigidBody>()->setSpeed({ parent->getComponents<RigidBody>()->getSpeed().x, parent->getComponents<RigidBody>()->getSpeed().y + (9.81f * m_mass * tools::GetTimeDelta()) });

			sf::Vector2f nextPosition = { parent->getComponents<ObjectTransform>()->getPosition().x + (parent->getComponents<RigidBody>()->getSpeed().x * tools::GetTimeDelta()),
				parent->getComponents<ObjectTransform>()->getPosition().y + (parent->getComponents<RigidBody>()->getSpeed().y * tools::GetTimeDelta()) };

			parent->getComponents<ObjectTransform>()->setPosition(nextPosition);

			if (m_timerBlinking > 0.05f)
			{
				if (parent->getComponents<Sprite>()->getSprite().getColor().a == static_cast<sf::Uint8>(255))
				{
					parent->getComponents<Sprite>()->getSprite().setColor(sf::Color(255,255,255,0));
				}
				else
				{
					parent->getComponents<Sprite>()->getSprite().setColor(sf::Color(255, 255, 255, 255));
				}

				m_timerBlinking = 0.0f;

			}
		}
	}

}

void Destructible::draw()
{
}

sf::IntRect& Destructible::getRectDestruct()
{
	return m_intRect;
}

bool Destructible::getHasDestroyed()
{
	return m_hasDestroyed;
}
