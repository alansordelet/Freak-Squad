#include "Collectible.h"

int Collectible::s_idCollectible{ 0 };

Collectible::Collectible()
{
	m_intRect = { 0,0,0,0 };
	m_isCollected = false;
	m_isTouchable = false;
	m_type = SOIN;
	m_timerWaving = 0.0f;
	m_startPosY = 0.0f;
}

Collectible::Collectible(TypeCollectible _type)
{
	m_type = _type;
	m_intRect = { 0,0,0,0 };
	m_isCollected = false;
	m_isTouchable = false;
	m_spriteButton.setTexture(RessourceManager::get()->getSceneTexture("touche_b.png"));
	m_spriteButton.setOrigin({ m_spriteButton.getGlobalBounds().width / 2.0f, m_spriteButton.getGlobalBounds().height / 2.0f });
	m_spriteButton.setScale({ 0.5f, 0.5f });
	m_timerWaving = 0.0f;
	m_startPosY = 0.0f;
}

Collectible::~Collectible()
{
}

std::shared_ptr<GameObject> Collectible::createCollectible(TypeCollectible _type, sf::Vector2f _position)
{
	s_idCollectible++;

	if (_type == PUCE)
	{
		std::string name;
		name = "Puce" + std::to_string(s_idCollectible);
		std::shared_ptr<GameObject> collectible = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idcollectible = std::shared_ptr<Identity>(new Identity(name, COLLECTIBLE));
		std::shared_ptr<ObjectTransform> transformcollectible = std::shared_ptr<ObjectTransform>(new ObjectTransform({ _position.x,_position.y}, _position.y + 460.f, STATIC));
		std::shared_ptr<Sprite> spritecollectible = std::shared_ptr<Sprite>(new Sprite());
		std::shared_ptr<Animation> animationCollectible = std::shared_ptr<Animation>(new Animation());
		std::shared_ptr<Collectible> collectibleObj = std::shared_ptr<Collectible>(new Collectible(PUCE));

		animationCollectible->addAnimation("IDLE", "puce.png", 6, 0.1f, true);

		collectible->addComponents<Identity>(idcollectible);
		collectible->addComponents<ObjectTransform>(transformcollectible);

		collectible->addComponents<Sprite>(spritecollectible);
		collectible->addComponents<Animation>(animationCollectible);
		collectible->addComponents<Collectible>(collectibleObj);

		animationCollectible->playAnim("IDLE", true);

		spritecollectible->getSprite().setOrigin({ spritecollectible->getSprite().getGlobalBounds().width / 2.0f, spritecollectible->getSprite().getGlobalBounds().height / 2.0f });
		spritecollectible->getSprite().setScale({ 0.3f, 0.3f });

		collectibleObj->setPosButton({ _position.x + (spritecollectible->getSprite().getGlobalBounds().width / 6.0f) / 2.0f ,_position.y  - 75.0f});

		collectibleObj->setRect({ static_cast<int>(_position.x), static_cast<int>(_position.y), static_cast<int>(spritecollectible->getSprite().getGlobalBounds().width / 6.0f), static_cast<int>(spritecollectible->getSprite().getGlobalBounds().height) });

		collectibleObj->setStartPosY(_position.y);

		return collectible;
	}
	else if (_type == SOIN)
	{
		std::string name;
		name = "Soin" + std::to_string(s_idCollectible);
		std::shared_ptr<GameObject> collectible = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idcollectible = std::shared_ptr<Identity>(new Identity(name, COLLECTIBLE));
		std::shared_ptr<ObjectTransform> transformcollectible = std::shared_ptr<ObjectTransform>(new ObjectTransform({ _position.x,_position.y }, _position.y + 102, STATIC));
		std::shared_ptr<Sprite> spritecollectible = std::shared_ptr<Sprite>(new Sprite("Soin.png"));
		std::shared_ptr<Collectible> collectibleObj = std::shared_ptr<Collectible>(new Collectible(SOIN));


		collectible->addComponents<Identity>(idcollectible);
		collectible->addComponents<ObjectTransform>(transformcollectible);
		collectible->addComponents<Sprite>(spritecollectible);
		collectible->addComponents<Collectible>(collectibleObj);

		spritecollectible->getSprite().setOrigin({ spritecollectible->getSprite().getGlobalBounds().width / 2.0f, spritecollectible->getSprite().getGlobalBounds().height / 2.0f });
		collectibleObj->setPosButton({ _position.x,_position.y });

		collectibleObj->setRect({ static_cast<int>(_position.x) - static_cast<int>(spritecollectible->getSprite().getGlobalBounds().width / 2.0f) , static_cast<int>(_position.y) - static_cast<int>(spritecollectible->getSprite().getGlobalBounds().height / 2.0f - 150.f), static_cast<int>(spritecollectible->getSprite().getGlobalBounds().width), static_cast<int>(spritecollectible->getSprite().getGlobalBounds().height) });
		
		collectibleObj->setStartPosY(_position.y);

		spritecollectible->getSprite().setScale({ 0.7f, 0.7f });

		return collectible;
	}
	else if (_type == ULTI)
	{
		std::string name;
		name = "Ulti" + std::to_string(s_idCollectible);
		std::shared_ptr<GameObject> collectible = std::shared_ptr<GameObject>(new GameObject());
		std::shared_ptr<Identity> idcollectible = std::shared_ptr<Identity>(new Identity(name, COLLECTIBLE));
		std::shared_ptr<ObjectTransform> transformcollectible = std::shared_ptr<ObjectTransform>(new ObjectTransform({ _position.x,_position.y }, _position.y + 102.f, STATIC));
		std::shared_ptr<Sprite> spritecollectible = std::shared_ptr<Sprite>(new Sprite("Ulti.png"));
		std::shared_ptr<Collectible> collectibleObj = std::shared_ptr<Collectible>(new Collectible(ULTI));


		collectible->addComponents<Identity>(idcollectible);
		collectible->addComponents<ObjectTransform>(transformcollectible);
		collectible->addComponents<Sprite>(spritecollectible);
		collectible->addComponents<Collectible>(collectibleObj);

		spritecollectible->getSprite().setOrigin({ spritecollectible->getSprite().getGlobalBounds().width / 2.0f, spritecollectible->getSprite().getGlobalBounds().height / 2.0f });
		collectibleObj->setPosButton({ _position.x,_position.y });

		collectibleObj->setRect({ static_cast<int>(_position.x) - static_cast<int>(spritecollectible->getSprite().getGlobalBounds().width / 2.0f) , static_cast<int>(_position.y) - static_cast<int>(spritecollectible->getSprite().getGlobalBounds().height / 2.0f), static_cast<int>(spritecollectible->getSprite().getGlobalBounds().width), static_cast<int>(spritecollectible->getSprite().getGlobalBounds().height) });

		spritecollectible->getSprite().setScale({ 0.7f, 0.7f });

		collectibleObj->setStartPosY(_position.y);

		return collectible;
	}
}

void Collectible::update()
{
	m_timerWaving += tools::GetTimeDelta() * 5.0f;

	if (auto objTrans = getParents().lock()->getComponents<ObjectTransform>())
	{
		float offset = m_startPosY + (15.0f * std::sin(m_timerWaving));
		objTrans->setPosition({ objTrans->getPosition().x, offset });
	}
}

void Collectible::draw()
{
	if (m_isTouchable)
		window.draw(m_spriteButton);
}

TypeCollectible& Collectible::getTypeCollectible()
{
	return m_type;
}

void Collectible::setIsLootable(bool _set)
{
	m_isTouchable = _set;
}

void Collectible::setPosButton(sf::Vector2f _vect2)
{
	m_spriteButton.setPosition(_vect2);
}

sf::IntRect& Collectible::getRectCollectible()
{
	return m_intRect;
}

void Collectible::setRect(sf::IntRect _intrect)
{
	m_intRect = _intrect;
}

void Collectible::setStartPosY(float _pos)
{
	m_startPosY = _pos;
}
