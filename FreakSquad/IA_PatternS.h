#pragma once
#include"IA_Pattern.h"
class IAMOTHER;

class IA_SPIKER : public IAMOTHER
{
public:
	IA_SPIKER();
	~IA_SPIKER();

	void update();
	void draw();
	void behaviourTree();
	void GestionAnim();
protected:

private:

};
