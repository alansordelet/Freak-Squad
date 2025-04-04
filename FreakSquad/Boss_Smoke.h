#pragma once
#include "CoffeeCore.hpp"

class Boss_Smoke : public GameComponent
{
private:
	std::vector<Boss_Smoke*> m_vecteur;
	sf::Vector2f m_position, m_scale;
	sf::Sprite m_sprite1;
	sf::Sprite m_sprite2;
	sf::Sprite m_sprite3;
	sf::Sprite m_sprite4;
	float animTime;
	float m_speed;
	float m_angle;
	int FrameX;
	int random;
	sf::Uint8 m_opacite;
	sf::IntRect m_rect;
public:
	inline static sf::Vector2f Norm(float _Speed, float _Angle) {
		return sf::Vector2f(_Speed * sin(_Angle * 3.1415 / 180.0f), _Speed * cos(_Angle * 3.1415 / 180.0f));
	}
	Boss_Smoke();
	Boss_Smoke(sf::Sprite _sprite, sf::Vector2f _position, float _speed,float _angle, sf::Vector2f _scale);
	~Boss_Smoke();

	void update();
	void draw();
	void add(sf::Vector2f _position, float _speed, float _angle, sf::Vector2f _scale);
};

