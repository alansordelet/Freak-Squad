#include "Timer.h"

Timer::Timer()
{
	m_timer = 0.0f;

	m_textTimer.setFont(RessourceManager::get()->getFont("Scoring.otf"));
	m_textTimer.setCharacterSize(60);
	m_textTimer.setString(std::to_string(0));
	m_textTimer.setOrigin({ m_textTimer.getGlobalBounds().width / 2.0f, m_textTimer.getGlobalBounds().height / 2.0f });
	m_textTimer.setPosition({ 960.0f, 80.0f });
	m_textTimer.setOutlineThickness(7);
	m_textTimer.setOutlineColor(sf::Color::Black);
}

Timer::~Timer()
{
}

void Timer::update()
{
	m_timer += tools::GetTimeDelta();
}

void Timer::draw()
{
	m_textTimer.setString(std::to_string(static_cast<int>(m_timer)));
	m_textTimer.setOrigin({ m_textTimer.getGlobalBounds().width / 2.0f, m_textTimer.getGlobalBounds().height / 2.0f });
	m_textTimer.setPosition({ 960.0f, 90.0f });

	sf::View tmpview = window.getWindow().getView();
	window.getWindow().setView(window.getWindow().getDefaultView());

	window.draw(m_textTimer);

	window.getWindow().setView(tmpview);
}

int Timer::getTimer()
{
	return static_cast<int>(m_timer);
}
