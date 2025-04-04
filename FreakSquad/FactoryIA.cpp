#include "FactoryIA.h"

FactoryIA::FactoryIA()
{
}

FactoryIA::~FactoryIA()
{
}

std::shared_ptr<GameObject> FactoryIA::createIA(std::string _name, TYPE_IA _type, sf::Vector2f _pos)
{
	switch (_type)
	{
	case TRASHER:
		break;
	case CLEVER:
		break;
	case SPIKER:
		break;
	default:
		break;
	}
	return std::shared_ptr<GameObject>();
}
