#pragma once
#include "GameComponent.h"
#include "ObjectTransform.h"
#include "GameObject.h"
#include "Identity.h"
#include "Animation.h"
#include "RigidBody.h"

struct COFFEECORE_API InfoRect
{
	sf::IntRect rect;
	std::string name;
};
typedef std::map<std::string, std::map<int, std::vector<InfoRect>>> listColliderAttack; //"Nom de L'anim"/Frame/hitbox	
typedef std::map<std::string, std::map<int, std::vector<InfoRect>>> listColliderBody; //"Nom de L'anim"/Frame/hitbox	

class COFFEECORE_API Collider : public GameComponent
{
protected:
	std::weak_ptr<ObjectTransform> wp_objTranform;
	std::weak_ptr<Animation> wp_animation;
	std::weak_ptr<RigidBody> wp_rigidBody;
	listColliderAttack l_hitBoxAttack;
	listColliderBody l_hitBoxBody;
	bool m_isHit;
	float m_timer;
public:
	Collider();

	Collider(std::shared_ptr<ObjectTransform> _objectTransform, std::shared_ptr<Animation> _animation, std::shared_ptr<RigidBody> _rigidBody, std::string _name);

	~Collider();

	void update();
	void draw();

	bool getIsHit();
	void setIsHit(bool _isHit);
	void isHit();

	std::vector<InfoRect> getRectAttack();
	std::vector<InfoRect> getRectBody();
};