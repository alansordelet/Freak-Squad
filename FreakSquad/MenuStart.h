#pragma once
#include "CoffeeCore.hpp"
class MenuStart : public GameComponent
{
private : 
	const sf::Vector2f posText{0.5,0.7};
	float m_timerText;
	MovieManager movieManager;
	bool m_moviePlaying;

	void drawText();
	void drawBackGround();
public :

	MenuStart();
	~MenuStart();

	void update();
	void draw();


};

