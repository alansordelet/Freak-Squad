#pragma once
#include "CoffeeCore.hpp"
class Hit: public GameComponent
{
private:
	std::vector<Hit*> m_vecteur;
	sf::Vector2f m_position, m_scale;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	float animTime;
	int FrameX;
	int random;
	sf::Uint8 m_opacite;
	sf::IntRect m_rect;
public:
	Hit();
	Hit(sf::Sprite _sprite, sf::Vector2f _position, sf::Vector2f _scale);
	~Hit();

	void update();
	void draw();
	void add(sf::Vector2f _position, sf::Vector2f _scale);
};

class BigHit : public GameComponent
{
private:
	std::vector<BigHit*> m_Bigvecteur;
	sf::Vector2f m_Bigposition, m_Bigscale;
	sf::Texture m_Bigtexture;
	sf::Sprite m_Bigsprite;
	float BiganimTime;
	int BigFrameX;
	int random;
	sf::Uint8 m_Bigopacite;
	sf::IntRect m_Bigrect;
public:
	BigHit();
	BigHit(sf::Sprite _sprite, sf::Vector2f _position, sf::Vector2f _scale);
	~BigHit();

	void update();
	void draw();
	void add(sf::Vector2f _position, sf::Vector2f _scale);
};