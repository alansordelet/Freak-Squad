#pragma once
#include"CoffeeCore.hpp"
#include "BehaviorTree.h"


class AI : public GameComponent {
private:
	float timerAI;
	std::unique_ptr<NodeComposite> m_root;
public:
	AI(std::shared_ptr<GameObject> _parent);

	void setTree(std::shared_ptr<NodeComposite> _tree);
	void update();
	void draw();
	float getTimer();
	void addDeltaTimeToTimer();
	void resetTimer();
};