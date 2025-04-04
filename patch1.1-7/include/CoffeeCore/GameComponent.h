#pragma once
#include "CoffeeUser.h"

enum COFFEECORE_API Type {
	PLAYER,
	ENNEMY,
	COLLECTIBLE,
	OBJECT,
	BIGBOY,
	CLEAVER,
	ROOT,
	UI
};

class GameObject;
class COFFEECORE_API GameComponent : public std::enable_shared_from_this<GameComponent> {
protected:
	bool m_active;
	std::weak_ptr<GameObject> m_Parents;
	CoffeeWindow window;
public:
	GameComponent() : m_active(true) {};
	virtual ~GameComponent() {};

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void destructor();

	std::weak_ptr<GameObject> getParents();
	bool isActive();
	void setActive(bool _v);

	void setParents(GameObject* _c);
};