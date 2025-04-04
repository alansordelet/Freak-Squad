#include "Go.h"

Go::Go()
{
	m_timerAffichage = 0.0f;
	m_affiche = true;
	m_repetition = 0;
	m_spriteGo.setTexture(RessourceManager::get()->getSceneTexture("go.png"));
	m_spriteGo.setPosition({ 1580.0f, 320.0f });
	m_spriteGo.setScale({ 0.3f, 0.3f });
}

Go::~Go()
{
}

void Go::update()
{
	if (!m_affiche)
	{
		m_timerAffichage += tools::GetTimeDelta();

		if (m_timerAffichage > 0.5f)
		{
			m_affiche = true;
			m_repetition++;
			m_timerAffichage = 0.0f;
		}
	}
	else
	{
		m_timerAffichage += tools::GetTimeDelta();

		if (m_timerAffichage > 0.7f)
		{
			m_affiche = false;
			m_timerAffichage = 0.0f;
		}
	}

	if (m_repetition == 4)
	{
		if (auto parent = getParents().lock())
		{
			parent->setActive(false);
			m_repetition = 0;
		}
	}
}

void Go::draw()
{
	if (m_affiche)
	{
		sf::View tmpView = window.getWindow().getView();
		window.getWindow().setView(window.getWindow().getDefaultView());

		window.draw(m_spriteGo);

		window.getWindow().setView(tmpView);
	}
}
