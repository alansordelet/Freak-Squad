#pragma once
#include"IA_Pattern.h"
class IAMOTHER;

class IA_CLEEVER : public IAMOTHER
{
public:
	IA_CLEEVER();
	IA_CLEEVER(bool _zombi);
	~IA_CLEEVER();

	void update();
	void draw();
	void behaviourTree();
	void GestionAnim();
protected:
	bool m_getHit;
private:

};
