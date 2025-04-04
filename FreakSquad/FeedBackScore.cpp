#include "FeedBackScore.h"
#include "Score.h"

FeedBackScore::FeedBackScore()
{
	sf::FloatRect m_textRect = m_txHit.getLocalBounds();
	m_txHit.setFont(RessourceManager::get()->getFont("3Dventure.ttf"));
	m_txHit.setPosition(sf::Vector2f(900.0f, 100.0f));
	m_txHit.setCharacterSize(100);
	m_txHit.setScale(m_scaleEG);
	m_txHit.setOrigin(m_textRect.left + m_textRect.width / 2.0f,
		m_textRect.top + m_textRect.height / 2.0f);
	m_txHit.setFillColor(sf::Color::Red);

}

FeedBackScore::~FeedBackScore()
{
}

sf::Vector2f FeedBackScore::VsmoothstepPingPongLerp(sf::Vector2f start, sf::Vector2f end, float t)
{
	// ping-pong t between 0 and 1
	t = std::abs(fmod(t, 2.0f) - 1.0f);

	// Clamp t to the range [0, 1]
	t = std::clamp(t, 0.0f, 1.0f);

	// Evaluate the Hermite polynomial
	t = t * t * (3 - 2 * t);

	// Interpolate the position using lerp
	return (1 - t) * start + t * end;
}

void FeedBackScore::update()
{
	m_keytimer += tools::GetTimeDelta();
	m_timerEG += tools::GetTimeDelta() * 10;
	sf::FloatRect m_textRect = m_txHit.getLocalBounds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && m_keytimer > 0.2f)
	{
		m_score += 1;
		m_newscaleEG = { 1.0f,1.0f };
		m_scaleEG = { 1.0f,1.0f };
		m_timerEG = 0.0f;
		m_activeEG = true;
		m_stoprotation = true;
		m_keytimer = 0.0f;
	}

	if (m_activeEG == true)
	{
		m_timerStop += tools::GetTimeDelta();
		m_newscaleEG = VsmoothstepPingPongLerp(sf::Vector2f(m_scaleEG.x, m_scaleEG.y), sf::Vector2f(1.5f, 1.5f), m_timerEG);
	}
	if (m_timerStop >= 0.05f)
	{
		if ((m_newscaleEG.x >= 1.0f && m_newscaleEG.x <= 1.05f) && (m_newscaleEG.y >= 1.0f && m_newscaleEG.y <= 1.05))
		{
			m_newscaleEG = { 1.0f,1.0f };
			m_scaleEG = { 1.0f,1.0f };
			m_activeEG = false;
			m_timerEG = 0.0f;
			m_timerStop = 0.0f;
		}
	}

	if (m_stoprotation == true)
	{
		if (m_score < 10)
		{
			m_rotationEG = tools::iRand(-10, 10 + 1);
		}
		if (m_score > 9)
		{
			m_rotationEG = tools::iRand(-15, 15 + 1);
		}
		if (m_score > 99)
		{
			m_rotationEG = tools::iRand(-10, 10 + 1);
		}

		m_stoprotation = false;
	}

	m_txHit.setScale(m_newscaleEG);
	m_txHit.setOrigin(m_textRect.left + m_textRect.width / 2.0f,m_textRect.top + m_textRect.height / 2.0f);
	m_txHit.setRotation(m_rotationEG);
}

void FeedBackScore::draw()
{
	//window.draw(m_text);

}