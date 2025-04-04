#include "tools2.h"

float tools2::distance(sf::Vector2f _point1, sf::Vector2f _point2)
{
	return sqrt((_point1.x - _point2.x) * (_point1.x - _point2.x) + (_point1.y - _point2.y) * (_point1.y - _point2.y));
}

sf::Vector2f tools2::direction(sf::Vector2f _sujet, sf::Vector2f _cible)
{
	sf::Vector2f cosSin = { 0,0 };
	if (tools2::distance(_cible, _sujet) != 0) {
		cosSin.x = (_cible.x - _sujet.x) / tools2::distance(_cible, _sujet);
		cosSin.y = (_cible.y - _sujet.y) / tools2::distance(_cible, _sujet);
	}
	return cosSin;
}

void tools2::moveInCircle(sf::Vector2f& _pos, sf::Vector2f _center, float _radius, float _angle)
{
	//Mouvement circulaire, il a a juste a changer l'angle
	float x = _center.x + _radius * std::cos(_angle * 3.14f / 180.f);
	float y = _center.y + _radius * std::sin(_angle * 3.14f / 180.f);
	_pos = sf::Vector2f(x,y);
}

float tools2::CalculAngle(float p1x, float p1y, float p2x, float p2y) 
{
	float tmpX = p2x - p1x;
	float tmpY = p2y - p1y;

	float AngleDegre = atan2(tmpY, tmpX) * 180 / 3.1415;
	AngleDegre *= -1;
	return AngleDegre;
}