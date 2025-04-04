#pragma once
#include "CoffeeCore.hpp"
class Player
{
private :


protected:


public : 
	Player();
	~Player();

	void initPlayer(std::shared_ptr<GameObject> _m_object, std::shared_ptr<Input> _input);
	void initBloodLust(std::shared_ptr<GameObject> _m_object, std::shared_ptr<Input> _input);

	void initFinalPlayableBoss(std::shared_ptr<GameObject> _m_object, std::shared_ptr<Input> _input);

	void Update(std::shared_ptr<GameObject> _m_object);
};

