#include "CollisionMask.h"

CollisionMask::CollisionMask()
{
	m_screen1Mask = RessourceManager::get()->getSceneTexture("screen1Mask.png").copyToImage();
	m_screen2Mask = RessourceManager::get()->getSceneTexture("screen2Mask.png").copyToImage();
	m_screen3Mask = RessourceManager::get()->getSceneTexture("screen3Mask.png").copyToImage();
	m_screen4Mask = RessourceManager::get()->getSceneTexture("screen4Mask.png").copyToImage();
	m_screen5Mask = RessourceManager::get()->getSceneTexture("screen5Mask.png").copyToImage();
	m_screen6Mask = RessourceManager::get()->getSceneTexture("screen6Mask.png").copyToImage();
	m_screen7Mask = RessourceManager::get()->getSceneTexture("screen7Mask.png").copyToImage();
	m_zoneBossMask = RessourceManager::get()->getSceneTexture("maskZoneBoss.png").copyToImage();
	m_souteMask = RessourceManager::get()->getSceneTexture("maskSoute.png").copyToImage();
}

CollisionMask::~CollisionMask()
{

}

void CollisionMask::update()
{

}

void CollisionMask::draw()
{
	/*sf::Sprite sprite;
	sprite.setPosition(m_screen1Pos);
	sprite.setTexture(RessourceManager::get()->getSceneTexture("screen1Mask.png"));
	window.draw(sprite);
	sprite.setPosition(m_screen2Pos);
	sprite.setTexture(RessourceManager::get()->getSceneTexture("screen2Mask.png"));
	window.draw(sprite);
	sprite.setPosition(m_screen3Pos);
	sprite.setTexture(RessourceManager::get()->getSceneTexture("screen3Mask.png"));
	window.draw(sprite);
	sprite.setPosition(m_zoneBossPos);
	sprite.setTexture(RessourceManager::get()->getSceneTexture("maskZoneBoss.png"));
	window.draw(sprite);*/
}


bool CollisionMask::checkCollisionMap(e_CHECKAXE _AXE, std::shared_ptr<GameObject> _actor)
{
	//auto parent = _actor->getParents().lock();//player ou IA
	auto type = _actor->getComponents<Identity>()->getType();
	float posX = _actor->getComponents<ObjectTransform>()->getPosition().x;
	float posZ = _actor->getComponents<ObjectTransform>()->getZBuffer();
	auto body = _actor->getComponents<RigidBody>();
	sf::Vector2f speed = body->getSpeed();
	sf::Vector2f posTmp{ 0.f,0.f };

	//on calcule la position afin que le joueur ne soit pas complètement bloqué en voulant aller dans la direction opposée!

	sf::Vector2f futurePos;//le y correspond au Z qui est la profondeur pour simplifier l'utilisation

	if (_AXE == X)
	{
		futurePos = sf::Vector2f(posX + (speed.x * 2 * tools::GetTimeDelta()), posZ);
	}
	else if (_AXE == Y)
	{
		futurePos = sf::Vector2f(posX, posZ + (speed.y * 2 * tools::GetTimeDelta()));
	}

	//couleur du masque de collision
	sf::Color colorMask = sf::Color::Red;

	if (futurePos.x >= m_screen1Pos.x && futurePos.x < m_screen2Pos.x\
		&& futurePos.y>m_screen1Pos.y && futurePos.y < m_screen1Pos.y + m_screen1Mask.getSize().y)//limite en X de la premiere map
	{
		posTmp.x = futurePos.x - m_screen1Pos.x;
		posTmp.y = futurePos.y - m_screen1Pos.y;

		colorMask = m_screen1Mask.getPixel(posTmp.x, posTmp.y - 30);
		//colorMaskY = m_screen1Mask.getPixel(posTmp.x, posTmp.y + (speed.y * 2 * tools::GetTimeDelta()) - 30);
	}
	else if (futurePos.x >= m_screen2Pos.x && futurePos.x < m_screen3Pos.x\
		&& futurePos.y>m_screen2Pos.y && futurePos.y < m_screen2Pos.y + m_screen2Mask.getSize().y)//limite en X de la deuxieme map
	{
		posTmp.x = futurePos.x - m_screen2Pos.x;
		posTmp.y = futurePos.y - m_screen2Pos.y;

		colorMask = m_screen2Mask.getPixel(posTmp.x, posTmp.y);
		//colorMaskY = m_screen2Mask.getPixel(posTmp.x, posTmp.y + (speed.y * tools::GetTimeDelta()));
	}
	else if (futurePos.x >= m_screen3Pos.x && futurePos.x < m_screen4Pos.x\
		&& futurePos.y>m_screen3Pos.y && futurePos.y < m_screen3Pos.y + m_screen3Mask.getSize().y)//limite en X de la troisieme map
	{
		posTmp.x = futurePos.x - m_screen3Pos.x;
		posTmp.y = futurePos.y - m_screen3Pos.y;

		colorMask = m_screen3Mask.getPixel(posTmp.x, posTmp.y);
		//colorMaskY = m_screen3Mask.getPixel(posTmp.x, posTmp.y + (speed.y * tools::GetTimeDelta()));
	}
	else if (futurePos.x >= m_screen4Pos.x && futurePos.x < m_screen5Pos.x\
		&& futurePos.y>m_screen4Pos.y && futurePos.y < m_screen4Pos.y + m_screen4Mask.getSize().y)//limite en X de la quatrieme map
	{
		posTmp.x = futurePos.x - m_screen4Pos.x;
		posTmp.y = futurePos.y - m_screen4Pos.y;

		colorMask = m_screen4Mask.getPixel(posTmp.x, posTmp.y);
		//colorMaskY = m_screen4Mask.getPixel(posTmp.x, posTmp.y + (speed.y * tools::GetTimeDelta()));
	}
	else if (futurePos.x >= m_screen5Pos.x - 1 && futurePos.x < m_screen6Pos.x\
		&& futurePos.y>m_screen5Pos.y && futurePos.y < m_screen5Pos.y + m_screen5Mask.getSize().y)//limite en X de la cinquieme map
	{
		posTmp.x = futurePos.x - m_screen5Pos.x;
		posTmp.y = futurePos.y - m_screen5Pos.y;

		colorMask = m_screen5Mask.getPixel(posTmp.x, posTmp.y);
		//colorMaskY = m_screen5Mask.getPixel(posTmp.x, posTmp.y + (speed.y * tools::GetTimeDelta()));
	}
	else if (futurePos.x >= m_screen6Pos.x && futurePos.x < m_screen7Pos.x\
		&& futurePos.y>m_screen6Pos.y && futurePos.y < m_screen6Pos.y + m_screen6Mask.getSize().y)//limite en X de la quatrieme map
	{
		posTmp.x = futurePos.x - m_screen6Pos.x;
		posTmp.y = futurePos.y - m_screen6Pos.y;

		colorMask = m_screen6Mask.getPixel(posTmp.x, posTmp.y);
		//colorMaskY = m_screen6Mask.getPixel(posTmp.x, posTmp.y + (speed.y * tools::GetTimeDelta()));
	}
	else if (futurePos.x >= m_screen7Pos.x && futurePos.x < m_screen7Pos.x + m_screen7Mask.getSize().x\
		&& futurePos.y > m_screen7Pos.y && futurePos.y < m_screen7Pos.y + m_screen7Mask.getSize().y)//limite en X de la quatrieme map
	{
		posTmp.x = futurePos.x - m_screen7Pos.x;
		posTmp.y = futurePos.y - m_screen7Pos.y;

		colorMask = m_screen7Mask.getPixel(posTmp.x, posTmp.y);
		//colorMaskY = m_screen7Mask.getPixel(posTmp.x, posTmp.y + (speed.y * tools::GetTimeDelta()));
	}
	else if (futurePos.x >= m_zoneBossPos.x\
		&& futurePos.y > m_zoneBossPos.y && futurePos.y < m_zoneBossPos.y + m_zoneBossMask.getSize().y)//check de la zone du boss ajouter +100 en X pour rentrer avec le glitch du portail
	{
		posTmp.x = futurePos.x - m_zoneBossPos.x;
		posTmp.y = futurePos.y - m_zoneBossPos.y;

		colorMask = m_zoneBossMask.getPixel(posTmp.x, posTmp.y);
	}
	else if (futurePos.x >= m_soutePos.x && futurePos.x < m_soutePos.x + m_souteMask.getSize().x\
		&& futurePos.y > m_soutePos.y && futurePos.y < m_soutePos.y + m_souteMask.getSize().y)
	{
		posTmp.x = futurePos.x - m_soutePos.x;
		posTmp.y = futurePos.y - m_soutePos.y;

		colorMask = m_souteMask.getPixel(posTmp.x, posTmp.y);
	}

	if (colorMask != sf::Color::Red)//verification horizontale
	{
		//printf("je sors de la map en X\n");
		return true;
	}
	else//sinon renvoie faux
	{
		return false;
	}
	//}
	return false;
}

bool CollisionMask::checkCollisionBossMap(std::shared_ptr<GameObject> _actor)
{
	//la zone fait un ecran de large et 2 écran de haut
	//position minimum Y = 640
	//zone a eviter :
	// _ 511x247  à 1410x480
	// _ 299x119 à 1621x643
	// _ 154x157 à 1765x765


	auto type = _actor->getComponents<Identity>()->getType();
	float posX = _actor->getComponents<ObjectTransform>()->getPosition().x;
	float posZ = _actor->getComponents<ObjectTransform>()->getZBuffer();
	auto body = _actor->getComponents<RigidBody>();
	sf::Vector2f speed = body->getSpeed();
	sf::Vector2f posTmp{ 0.f,0.f };

	sf::Vector2f futurePos;
	return false;
}