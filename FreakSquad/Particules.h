#pragma once
#include "CoffeeCore.hpp"

enum Shape {
	CERCLE,
	RECTANGLE,
};

enum DirectionParticules {
	BAS,
	HAUT,
	GAUCHE,
	DROITE,
	STATIQUE
};
class Particules : public GameComponent
{
private:
	
	std::vector <Particules*> m_vector;
	Shape m_shape;
	sf::RectangleShape Rectangle;
	sf::Color m_color;
	sf::CircleShape Circle;
	sf::Vector2f m_position;
	float m_speed;
	sf::Uint8 m_opacite, r, g, b;
	int height,width;
	float angle;
	float timerSpawn;
	DirectionParticules direction;
	std::string m_name;
	sf::Sprite m_sprite;
	float m_erasespeed;
public:
	Particules();
	Particules(sf::Vector2f _position, std::string _nameTexture, DirectionParticules _dir,
		sf::Uint8 _opacite, float _speed, float _eraseSpeed);
	~Particules();

	void update();
	void draw();

	void addParticules(sf::Vector2f _position, std::string _nameTexture, DirectionParticules _dir,
		sf::Uint8 _opacite, float _speed, float _eraseSpeed);

};

