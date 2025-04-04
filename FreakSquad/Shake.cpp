#include "Shake.h"

Shake::Shake()
{
	m_positionSave = {0.0f, 0.0f};
	m_shakeTime = 0.0f;
	m_shakeIntensity = 10.0f;
	m_activeET = false;
}

Shake::~Shake()
{
}

void Shake::SetActiveShake(bool _bool)
{
	m_activeET = _bool;
}

void Shake::update()
{
	if (auto parent = getParents().lock())
	{
		//std::shared_ptr<ObjectTransform> position = parent->getComponents<ObjectTransform>();

		if (m_activeET == false)
		{
			m_positionSave = parent->getComponents<ObjectTransform>()->getPosition();
		}

		if (m_activeET == true)
		{
			m_shakeTime += 1.f * tools::GetTimeDelta();
			if (m_shakeTime < 0.2f)
			{				
				m_tmpposition.x = (std::rand() % static_cast<int>(m_shakeIntensity)) - m_shakeIntensity;
				m_tmpposition.y = (std::rand() % static_cast<int>(m_shakeIntensity)) - m_shakeIntensity;

				parent->getComponents<ObjectTransform>()->setPosition(sf::Vector2f(m_tmpposition.x + m_positionSave.x, m_tmpposition.y + m_positionSave.y));
			}
			else
			{
				m_shakeTime = 0.f;
				m_activeET = false;
			}			
		}
	}	
}

void Shake::draw()
{

}