#include "CoffeeCore.hpp"
#include "Game.h"
#include "Menu.h"


int main(int argc, char* argv[])
{
	CoffeeWindow window;

	window.setFirstScene(new Menu());
	window.createWindow("Freak Squad", sf::Vector2u(1920, 1080), true);
	window.runGameLoop();
	
	return 0;
}