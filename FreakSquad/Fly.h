#pragma once
#include "CoffeeCore.hpp"

class Fly : public GameComponent
{
private:

	std::vector<Fly*> FLY;
	sf::Sprite m_spriteFly;
	sf::CircleShape recFly;
	sf::Vector2f m_positionFly = { 0.0f, 0.0f };
	sf::Vector2f m_vitesseFly = { 0.0f,0.0f };
	sf::Vector2f m_scaleFly = { 0.03f, 0.03f };
	sf::Vector2f m_originFly = { 379.0f / 2.0f, 385.0f / 2.0f };
	float m_angleFly = 0.0f;
	sf::Vector2f m_positionSAVE;
	bool m_fuite = false;
	float m_transFly = 0.0f;
	float m_timerChangeAngle = 0.0f;
	float m_TMPtimerChangeAngle = 0.0f;
	float m_vitesseAngle = 0.0f;
	float m_TMPvitesseAngle = 0.0f;
	int m_choixMouvement = 1;
	int m_choixMouvement2 = 1;
	float m_timerTrans = 0.0f;
	float m_TMPtimerTrans = 0.0f;
	bool m_InverseTrans = false;

public:

	Fly();
	Fly(std::shared_ptr<ObjectTransform>);
	Fly(sf::Sprite _spriteFly, sf::Vector2f _positionFly, sf::Vector2f _positionSuive);
	Fly(sf::CircleShape _spriteFly, sf::Vector2f _positionFly, sf::Vector2f _positionSuive);
	~Fly();

	void initFly(std::shared_ptr<GameObject> _object);

	float length(sf::Vector2f _vec);
	sf::Vector2f limit(sf::Vector2f _vec, float _limit);
	sf::Vector2f seek(sf::Vector2f _target, sf::Sprite _sprite, float _maxspeed, sf::Vector2f _velocity);
	sf::Vector2f seek2(sf::Vector2f _target, sf::CircleShape _sprite, float _maxspeed, sf::Vector2f _velocity);

	void update();
	void draw();
};