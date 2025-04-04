#pragma once
#include "CoffeeCore.hpp"

enum TypeCollectible
{
	PUCE = 1,
	SOIN,
	ULTI
};

class Collectible : public GameComponent
{
private:
	TypeCollectible m_type;
	sf::IntRect m_intRect;
	bool m_isCollected;
	bool m_isTouchable;
	float m_timerWaving;
	float m_startPosY;
	static int s_idCollectible;
	sf::Sprite m_spriteButton;
public:
	Collectible();
	Collectible(TypeCollectible _type);
	~Collectible();

	static std::shared_ptr<GameObject> createCollectible(TypeCollectible _type, sf::Vector2f _position);

	void update();
	void draw();

	TypeCollectible& getTypeCollectible();
	void setIsLootable(bool _set);
	void setPosButton(sf::Vector2f _vect2);
	sf::IntRect& getRectCollectible();
	void setRect(sf::IntRect _intrect);
	void setStartPosY(float _pos);
};

