#pragma once
#include "CoffeeCore.hpp"

enum TYPE_COLIS {
	BLEU, JAUNE, ROUGE, VERT
};
enum STATE_COLIS {
	IN_AIR,MID_AIR,ON_GROUND,PICKED_UP
};


class Colis {
private:

public:
	Colis();
	~Colis();
	/*Pour créer un Drop, veuillez indiqué le nom de l'objet, la couleur du colis, la position de spawn du colis, et la position d'arrivé du colis*/
	static std::shared_ptr<GameObject> createDrop(TYPE_COLIS _type, sf::Vector2f _spawnPos, sf::Vector2f _targetPos);

};

class Package : public GameComponent
{
private:
	TYPE_COLIS m_type;
	STATE_COLIS m_state;
	std::weak_ptr<ObjectTransform> m_position;
	sf::Sprite m_sprite;
	sf::Sprite m_Button;
	sf::Sprite m_Ombre;
	sf::Uint8 m_opacite;
	int m_life;
	sf::Vector2f m_targetPosition;
	sf::Vector2f m_spawnPos;
	float m_speed;
	float timer;
	bool is_onGround;
	bool is_Hit;
	bool is_pickedUp;
	bool m_playLandingAnim;
	sf::IntRect m_Rect;
public:
	Package();
	Package(TYPE_COLIS _type, sf::Vector2f _spawnPos, sf::Vector2f _targetPos, sf::IntRect _rect);
	~Package();
	void update();
	void draw();
	void destroyPackage();
	//pour la pos target en y utiliser le z du player
	void setTargetPos(sf::Vector2f _targetPos);
	void setPos(std::weak_ptr<ObjectTransform> _posView);
	void setIsHit(bool _is_pickedUp);
	void setLife(int _life);
	bool getIsHit();
	bool getIs_PickedUp();
	void Set_Is_PickedUp();
	sf::Vector2f getPackage_Position();
	int getLife();
	sf::IntRect& getRect();

	TYPE_COLIS getType();
	void setType(TYPE_COLIS _value);
};

