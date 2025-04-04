#pragma once
#include "CoffeeCore.hpp"

enum e_CHECKAXE
{
	X,
	Y,
	Z
};

class CollisionMask : public GameComponent
{
public:

	CollisionMask();
	~CollisionMask();

	bool checkCollisionMap(e_CHECKAXE _AXE, std::shared_ptr<GameObject>_actor);

	void update();
	void draw();


	const sf::Vector2f m_soutePos = sf::Vector2f(0.f, 0.f);
	const sf::Vector2f m_screen1Pos = sf::Vector2f(m_soutePos.x - 100.f, m_soutePos.y + SCREENSIZE_Y);
	const sf::Vector2f m_screen2Pos = sf::Vector2f(m_screen1Pos.x + SCREENSIZE_X - 1, m_screen1Pos.y);
	const sf::Vector2f m_screen3Pos = sf::Vector2f(m_screen2Pos.x + SCREENSIZE_X * (3), m_screen2Pos.y + SCREENSIZE_Y * 2);
	const sf::Vector2f m_screen4Pos = sf::Vector2f(m_screen3Pos.x + SCREENSIZE_X * 2 - 1, m_screen3Pos.y - SCREENSIZE_Y - 1);
	const sf::Vector2f m_screen5Pos = sf::Vector2f(m_screen4Pos.x + SCREENSIZE_X * 2 - 1, m_screen4Pos.y);
	const sf::Vector2f m_screen6Pos = sf::Vector2f(m_screen5Pos.x + SCREENSIZE_X * 1 - 8, m_screen5Pos.y);
	const sf::Vector2f m_screen7Pos = sf::Vector2f(m_screen6Pos.x + SCREENSIZE_X * 3.0f - 7, m_screen6Pos.y + SCREENSIZE_Y * 2.0f + 1);
	const sf::Vector2f m_zoneBossPos = sf::Vector2f(m_screen7Pos.x + SCREENSIZE_X * 2.f + 20+100, m_screen7Pos.y);//il y a un décalage de 100 avec les map d'où le +100 et +20 pour avoir une marge avec la fin du lvl

private:

	bool checkCollisionBossMap(std::shared_ptr<GameObject>_actor);

	sf::Image m_screen1Mask;
	sf::Image m_screen2Mask;
	sf::Image m_screen3Mask;
	sf::Image m_screen4Mask;
	sf::Image m_screen5Mask;
	sf::Image m_screen6Mask;
	sf::Image m_screen7Mask;
	sf::Image m_souteMask;
	sf::Image m_zoneBossMask;
};


