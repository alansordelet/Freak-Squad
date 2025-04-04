#include "Blood.h"

Blood::Blood()
{
	m_positionBlood = { 0.0f, 0.0f };
	m_vitesseBlood = { 0.0f, 0.0f };
	m_scaleBlood = { 1.0f,1.0f };
	m_originBlood = { 177.0f / 2.0f, 56.0f / 2.0f };
	m_originBlood2 = { 70.0f / 2.0f, 76.0f / 2.0f };
	m_originBlood3 = { 62.0f / 2.0f, 52.0f / 2.0f };
	m_transBlood = 100.0f;
	m_TMPtransBlood = 0.0f;
	m_angleBlood = 0.0f;
	m_timerPlaquer = 0.0f;
	m_TMPtimerPlaquer = 0.0f;
	m_angleDirection = 0.0f;

	m_spriteBlood.setTexture(RessourceManager::get()->getSceneTexture("blood.png"));
	m_spriteBlood.setPosition(m_positionBlood);
	m_spriteBlood.setScale(m_scaleBlood);
	m_spriteBlood.setOrigin(m_originBlood);
	m_spriteBlood.setRotation(m_angleBlood);
}

Blood::Blood(sf::Sprite _spriteBlood, sf::Vector2f _positionBlood, int _m_direction)
{
	m_spriteBlood = _spriteBlood;
	m_positionBlood = _positionBlood;
	m_direction = _m_direction;
	m_scaleBlood.x = tools::frand(0.8f, 1.2f);
	m_scaleBlood.y = tools::frand(0.8f, 1.2f);
	m_angleBlood = tools::iRand(0, 360);
	m_transBlood = tools::frand(150.0f, 255.0f);
	m_vitesseBlood.x = tools::iRand(700, 1200);
	m_vitesseBlood.y = tools::iRand(700, 1200);
	m_angleDirection = tools::iRand(150, 100);
	m_angleDirection = m_angleDirection - 90;
	m_TMPtimerPlaquer = tools::frand(0.1f, 0.2f);
	m_timerPlaquer = 0.0f;
	m_TMPtransBlood = 700;
}

Blood::~Blood()
{
}

void Blood::GoPushBlood(sf::Vector2f _positionBlood, int _direction)
{
	for (int i = 0; i < 8; i++)
	{
		BLOOD.push_back(new Blood(m_spriteBlood, sf::Vector2f(_positionBlood.x + tools::iRand(-5, +5), _positionBlood.y + tools::iRand(-5, +5)), _direction));
	}
}

void Blood::update()
{
	for (Blood* b : BLOOD)
	{
		b->m_timerPlaquer += tools::GetTimeDelta();

		if (b->m_timerPlaquer < b->m_TMPtimerPlaquer)
		{
			if (b->m_direction == 0)
			{
				b->m_positionBlood.x += sin((3.1416 / 180) * b->m_angleDirection) * b->m_vitesseBlood.x * tools::GetTimeDelta();
				b->m_positionBlood.y += cos((3.1416 / 180) * b->m_angleDirection) * -b->m_vitesseBlood.y * tools::GetTimeDelta();
			}
			if (b->m_direction == 1)
			{
				b->m_positionBlood.x += sin((3.1416 / 180) * b->m_angleDirection) * -b->m_vitesseBlood.x * tools::GetTimeDelta();
				b->m_positionBlood.y += cos((3.1416 / 180) * b->m_angleDirection) * -b->m_vitesseBlood.y * tools::GetTimeDelta();
			}
			b->m_positionBlood.y += 1200.0f * tools::GetTimeDelta();
		}

		if (b->m_timerPlaquer >= 0.15f)
		{
			b->m_transBlood -= b->m_TMPtransBlood * tools::GetTimeDelta();
		}
		if (b->m_transBlood <= 0.0f)
		{
			b->m_transBlood = 0.0f;
		}

		b->m_spriteBlood.setPosition(b->m_positionBlood);
		b->m_spriteBlood.setRotation(b->m_angleBlood);
		b->m_spriteBlood.setScale(b->m_scaleBlood);
		b->m_spriteBlood.setColor(sf::Color(255.0f, 255.0f, 255.0f, b->m_transBlood));
	}
	for (int i = 0; i < BLOOD.size(); i++)
	{
		if (BLOOD[i]->m_transBlood <= 0.0f)
		{
			BLOOD.erase(BLOOD.begin() + i);
		}
	}
}

void Blood::draw()
{
	for (Blood* b : BLOOD)
	{
		window.draw(b->m_spriteBlood);
	}
}
