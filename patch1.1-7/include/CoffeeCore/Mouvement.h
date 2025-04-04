#pragma once
#include "GameComponent.h"

class COFFEECORE_API Mouvement : public GameComponent {
public:
	Mouvement();
	~Mouvement();

	void update();
	void draw();
};
