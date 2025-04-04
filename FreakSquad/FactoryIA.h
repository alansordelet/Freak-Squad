#pragma once
#include "CoffeeCore.hpp"

enum TYPE_IA
{
	TRASHER,
	CLEVER,
	SPIKER
};
typedef enum TYPE_IA TYPE_IA;

class FactoryIA
{
private : 


protected :


public :
	FactoryIA();
	~FactoryIA();

	static std::shared_ptr<GameObject> createIA(std::string _name, TYPE_IA _type,sf::Vector2f _pos);
};

