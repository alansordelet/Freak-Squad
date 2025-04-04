#pragma once
#include"IA_Pattern.h"
class IAMOTHER;

class IA_TRASHER : public IAMOTHER
{
public:
	IA_TRASHER();
	~IA_TRASHER();

	void update();
	void draw();
	void behaviourTree();
	void GestionAnim();

protected:

private:

};
