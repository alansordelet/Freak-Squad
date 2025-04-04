//#include "pch.h"
#include "AI.h"
//#include "CoffeeCore.hpp"

AI::AI(std::shared_ptr<GameObject> _parent) : timerAI(0.0f) {
	m_Parents = _parent;
	m_root = std::make_unique<NodeComposite>(m_Parents, SELECTOR);	
}

void AI::setTree(std::shared_ptr<NodeComposite> _tree)
{
	m_root->add(_tree);
}

void AI::update() {
	m_root->update();
}

void AI::draw()
{
}

float AI::getTimer()
{
	return timerAI;
}

void AI::addDeltaTimeToTimer()
{
	timerAI += tools::GetTimeDelta();
}

void AI::resetTimer()
{
	timerAI = 0.f;
}
