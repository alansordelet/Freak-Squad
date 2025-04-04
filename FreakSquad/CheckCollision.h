#pragma once
#include "CoffeeCore.hpp"


class  CheckCollision : public GameComponent
{
public:
	CheckCollision();
	~CheckCollision();

	void update();
	void draw();
	void check();

	
	void addfx(int type);
protected :


private :
	float timerSpawn;
	float timerParticules;
};

