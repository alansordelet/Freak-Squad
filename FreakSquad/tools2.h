#pragma once
#include"CoffeeCore.hpp"
namespace tools2
{
	float distance(sf::Vector2f _point1, sf::Vector2f _point2);

	sf::Vector2f direction(sf::Vector2f _sujet, sf::Vector2f _cible);  //return le sin et cosinus

	void moveInCircle(sf::Vector2f& _pos, sf::Vector2f _center, float _radius, float _angle);

	float CalculAngle(float p1x, float p1y, float p2x, float p2y);
}