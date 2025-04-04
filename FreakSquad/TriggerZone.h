#pragma once
#include "CoffeeCore.hpp"
#include <functional>


class TriggerZone : public GameComponent
{
private:
	bool m_isTriggered;
	sf::IntRect m_intRect;
	std::function<void()> m_hasTriggered;
	std::function<bool()> m_update;
	std::function<void()> m_end;
public:
	TriggerZone();
	~TriggerZone();

	void update();
	void draw();

	void setZone(sf::IntRect _intrect);
	void setTriggeredFunction(std::function<void()> _function);
	void setUpdateFunction(std::function<bool()> _function);
	void setEndFunction(std::function<void()> _function);
};

