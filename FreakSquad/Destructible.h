#pragma once
#include "CoffeeCore.hpp"

enum EnumAsset
{
	FRIGO,
	MACHINELAVER,
	DISTRIBUTEUR,
};


class Destructible : public GameComponent
{
private:
	EnumAsset type;
	bool m_activeSet;
	bool m_hasDestroyed;
	bool m_isHit;
	bool m_textureDestroyedSet;
	float m_timerHit;
	float m_mass;
	int m_pv;
	sf::IntRect m_intRect;
	static int s_idDestructible;
	float m_timerBlinking;
	float m_timerDepop;
public:

	Destructible();
	Destructible(sf::IntRect _intRect, EnumAsset _type);
	~Destructible();

	float m_yBoing;

	static std::shared_ptr<GameObject> createDestructible(EnumAsset _type, float _posX, float _posY);

	int getPVDestructible();
	void setPVDestructible(int _pv);

	void setHit(const bool _hit);
	bool getIsHit();

	void setDestroyed();

	void update();
	void draw();

	sf::IntRect& getRectDestruct();
	bool getHasDestroyed();
};

