#include "TriggerZone.h"

TriggerZone::TriggerZone()
{
	m_isTriggered = false;
	m_intRect = { 0,0,0,0 };
}

TriggerZone::~TriggerZone()
{
}

void TriggerZone::update()
{
	if (!m_isTriggered)
	{
		for (auto& player : GameObject::l_Player)
		{
			auto playerPos = static_cast<sf::Vector2i>(player->getComponents<ObjectTransform>()->getPosition());
			
			if (m_intRect.contains(playerPos) && !m_isTriggered)
			{
				m_hasTriggered();
				m_isTriggered = true;
			}
		}
	}
	else
	{
		if (m_update())
		{
			m_end();
			m_active = false;
		}
	}
}

void TriggerZone::draw()
{
}

void TriggerZone::setZone(sf::IntRect _intrect)
{
	m_intRect = _intrect;
}

void TriggerZone::setTriggeredFunction(std::function<void()> _function)
{
	m_hasTriggered = _function;

}

void TriggerZone::setUpdateFunction(std::function<bool()> _function)
{
	m_update = _function;
}

void TriggerZone::setEndFunction(std::function<void()> _function)
{
	m_end = _function;
}
