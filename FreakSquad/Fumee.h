#pragma once
#include "CoffeeCore.hpp"

class Fumee : public GameComponent
{
private:
	std::vector<Fumee*> SMOKE;
	sf::Sprite m_spriteSmoke;
	sf::Vector2f m_positionSmoke = { 0.0f,0.0f };
	sf::Vector2f m_tmppositionSmoke = { 200.0f, 550.0f };
	sf::Vector2f m_tmppositionSmokeMOUSE;
	sf::Vector2f m_vitesseSmoke;
	sf::Vector2f m_tmpvitesseSmoke;
	sf::Vector2f m_scaleSmoke = { 1.0, 1.0f };
	float m_transSmoke = 50.0f;
	float m_targetAngle;
	float m_tmptAngle = 0.0f;
	float m_tmpAngle2 = 0.0f;
	float m_tmpAngle3 = 0.0f;
	int m_nbFumer = 0;
	float m_timerRDM = 0.0f;
	int m_choixPushFumer = 1;
	
	float m_red = 255.0f;
	float m_green = 255.0f;
	float m_blue = 255.0f;

	float m_keytimer = 0.0f;
public:

	Fumee();
	Fumee(sf::Sprite _spriteSmoke, sf::Vector2f _positionSmoke, sf::Vector2f _vitesseSmoke, sf::Vector2f _tmpvitesseSmoke, sf::Vector2f _scaleSmoke, float _targetAngle, float _tmpAngle2, float _tmpAngle3, float _red, float _green, float _blue);
	~Fumee();

	void initFumee(std::shared_ptr<GameObject> _object);

	void update();
	void draw();
};