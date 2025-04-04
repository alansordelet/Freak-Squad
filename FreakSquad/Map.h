#pragma once
#include "CoffeeCore.hpp"
class Map
{
private : 


protected : 


public : 
	Map();
	~Map();

	void initMap(std::shared_ptr<GameObject> _object, float _volumeMusic, float _volumeSound);
	void initPremierPlan(std::shared_ptr<GameObject> _object);
};


class MapFactory
{
public:
	static std::shared_ptr<GameObject> createMap(std::string _nameObject, std::string _fileName, sf::Vector2f _pos);
	static std::shared_ptr<GameObject> createFrontMap(std::string _nameObject, std::string _fileName, sf::Vector2f _pos);
};