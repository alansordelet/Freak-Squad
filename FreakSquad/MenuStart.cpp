#include "MenuStart.h"

MenuStart::MenuStart()
{
	movieManager.addMovie("intro_logo_ga.mkv");
	m_moviePlaying = false;
	m_timerText = 0;
}

MenuStart::~MenuStart()
{
}

void MenuStart::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		movieManager.playMovie("intro_logo_ga.mkv");
		m_moviePlaying = true;
	}
	if (auto parent = getParents().lock())
	{
		auto scene = parent->getParent();
		if (auto inputObj = scene->getObjects("INPUT_J1"))
		{
			if (auto input = inputObj->getComponents<Input>())
			{
				if (input->getType(gp::Gamepad::A) == PRESSED)
				{
					if (movieManager.getGlobalMovie("intro_logo_ga.mkv").getStatus() != sfe::Playing)
					{
						movieManager.playMovie("intro_logo_ga.mkv");
						m_moviePlaying = true;
					}
				}
			}
		}
	}
	if (movieManager.getGlobalMovie("intro_logo_ga.mkv").getStatus() == sfe::Stopped && m_moviePlaying)
	{
		if (auto parent = getParents().lock())
		{
			auto scene = parent->getParent();
			if (auto mainMenu = scene->getObjects("MAIN_MENU"))
			{
				mainMenu->setActive(true);
				parent->setActive(false);
			}
		}
	}
	std::cout << movieManager.getGlobalMovie("intro_logo_ga.mkv").getStatus();
	m_timerText += tools::GetTimeDelta();
}

void MenuStart::draw()
{
	drawBackGround();
	drawText();
	movieManager.UpdateAndDrawMovie("intro_logo_ga.mkv", window.getWindow());
}

void MenuStart::drawText()
{
	sf::Text tmp_text;
	tmp_text.setStyle(sf::Text::Bold);
	tmp_text.setFont(RessourceManager::get()->getFont("italique_steelfish.otf"));
	tmp_text.setCharacterSize(70);
	tmp_text.setOutlineColor(sf::Color::Black);
	tmp_text.setOutlineThickness(1.f);
	tmp_text.setString("PRESS A TO CONTINUE");
	tmp_text.setPosition({ posText.x * window.getSize().x - tmp_text.getGlobalBounds().width / 2,posText.y * window.getSize().y });
	if (m_timerText > 0.5)
	{
		window.draw(tmp_text);
		if (m_timerText > 1)
		{
			m_timerText = 0;
		}
	}

}

void MenuStart::drawBackGround()
{
	sf::Sprite tmp_sprite;

	tmp_sprite.setTexture(RessourceManager::get()->getSceneTexture("copyright.png"));
	tmp_sprite.setPosition({ 0.f,0.f });
	window.draw(tmp_sprite);
}

