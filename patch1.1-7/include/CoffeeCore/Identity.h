#pragma once
#include "GameComponent.h"

class COFFEECORE_API Identity : public GameComponent {
private:
	int m_id;
	static int s_globalId;
	std::string m_name;
	Type type;
public:
	Identity(std::string _name, Type _type);
	~Identity();

	void update();
	void draw();

	int getId();
	int getTotalId();
	std::string getName();
	Type getType();
	
};
