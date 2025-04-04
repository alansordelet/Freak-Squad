#include "Package.h"
Package::Package() {}
Package::Package(TYPE_COLIS _type, sf::Vector2f _spawnPos, sf::Vector2f _targetPos, sf::IntRect _rect) {
	m_state = IN_AIR;
	m_speed = 80.f;
	m_opacite = 255;
	m_spawnPos = _spawnPos;
	m_targetPosition = _targetPos;
	m_Rect = _rect;
	is_onGround = false;
	m_playLandingAnim = true;
	is_Hit = false;
	is_pickedUp = false;
	m_life = 2;
	m_Rect.height = 151;
	m_Rect.width = 184;
	m_Rect.top = m_targetPosition.y;
	m_Rect.left = m_targetPosition.x;
	timer = 0.f;
	m_Button.setTexture(RessourceManager::get()->getSceneTexture("touche_b.png"));
	m_Ombre.setTexture(RessourceManager::get()->getSceneTexture("Ombre.png"));
	m_Ombre.setColor(sf::Color(255, 255, 255, 100));
	if (auto parent = getParents().lock()) {
		switch (_type) {
		case BLEU:
			parent->getComponents<Sprite>()->setTexture(RessourceManager::get()->getSceneTexture("ColisBleu_idle.png"));
			break;
		case ROUGE:
			parent->getComponents<Sprite>()->setTexture(RessourceManager::get()->getSceneTexture("ColisRouge_idle.png"));
			break;
		case VERT:
			parent->getComponents<Sprite>()->setTexture(RessourceManager::get()->getSceneTexture("ColisVert_idle.png"));
			break;
		case JAUNE:
			parent->getComponents<Sprite>()->setTexture(RessourceManager::get()->getSceneTexture("ColisJaune_idle.png"));
			break;
		}
	}
}
Package::~Package() {}

void Package::update()
{
	if (auto parent = getParents().lock()) {
		parent->getComponents<ObjectTransform>()->setZBuffer(parent->getComponents<ObjectTransform>()->getPosition().y + 300.f);
		if (parent->getComponents<ObjectTransform>()->getPosition().y < m_targetPosition.y) {
			m_state = IN_AIR;
			m_speed = 100.f;
		}
		if (parent->getComponents<ObjectTransform>()->getPosition().y >= m_targetPosition.y - 400.f) {
			m_state = MID_AIR;
			m_speed = 500.f;
		}
		if (parent->getComponents<Animation>()->getCurrentFrame() >= 10) {
			m_state = ON_GROUND;

		}
		if (parent->getComponents<ObjectTransform>()->getPosition().y >= m_targetPosition.y) {
			//parent->getComponents<ObjectTransform>()->setState(STATIC);
			m_state = ON_GROUND;
			m_speed = 0.f;
		}
		parent->getComponents<RigidBody>()->setSpeed(sf::Vector2f{ parent->getComponents<RigidBody>()->getSpeed().x, m_speed });
	}
	if (!is_pickedUp)
	{
		if (auto anim = getParents().lock()->getComponents<Animation>()) {
			if (m_state == IN_AIR) {
				anim->playAnim("LIVRAISON", true);
			}
			if (m_state == MID_AIR) {
				if (m_playLandingAnim) {
					anim->playAnim("LANDING", false);
					m_playLandingAnim = false;
				}
				if (anim->getCurrentFrame() >= 10) {
					anim->pause();

					m_state = ON_GROUND;
				}
			}
			if (m_state == ON_GROUND) {
				anim->playAnim("IDLE", true);
			}
		}
	}
}

void Package::draw()
{
	timer += tools::GetTimeDelta();
	if (!is_pickedUp) {
		m_Ombre.setPosition({ m_targetPosition.x - m_Ombre.getTextureRect().width / 2, m_targetPosition.y - m_Ombre.getTextureRect().height / 2 });
		if (auto parent = getParents().lock()) {
			m_Button.setPosition({ parent->getComponents<ObjectTransform>()->getPosition().x - 60 ,parent->getComponents<ObjectTransform>()->getPosition().y - 280 });
			if (m_state == ON_GROUND) {
				if (timer <= 0.6f) {
					window.draw(m_Button);
				}
				if (timer >= 0.9f) {
					timer = 0.f;
				}
			}
		}
		window.draw(m_Ombre);
	}
}


void Package::setTargetPos(sf::Vector2f _targetPos) { m_targetPosition = _targetPos; }
void Package::setPos(std::weak_ptr<ObjectTransform> _pos) { m_position = _pos; }
void Package::setIsHit(bool _is_Hit) { is_Hit = _is_Hit; }
bool Package::getIsHit() { return is_Hit; }
void Package::setLife(int _life) { m_life = _life; }
sf::Vector2f Package::getPackage_Position() {
	if (auto objectTransform = m_position.lock()) {
		return sf::Vector2f(objectTransform->getPosition().x, objectTransform->getPosition().y);
	}
}
int Package::getLife() { return m_life; }
sf::IntRect& Package::getRect() { return m_Rect; }
TYPE_COLIS Package::getType() { return m_type; }
void Package::setType(TYPE_COLIS _value) { m_type = _value; }
bool Package::getIs_PickedUp() { return is_pickedUp; }
void Package::Set_Is_PickedUp() { is_pickedUp = true; }

/*____________GAME_OBJECT____________*/
Colis::Colis() {}
Colis::~Colis() {}
int integer = 0;
std::shared_ptr<GameObject> Colis::createDrop(TYPE_COLIS _type, sf::Vector2f _spawnPos, sf::Vector2f _targetPos)
{
	std::string nameObj = "Drop" + std::to_string(integer);
	integer++;
	std::shared_ptr<GameObject> drop = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> idDrop = std::shared_ptr<Identity>(new Identity(nameObj, COLLECTIBLE));
	std::shared_ptr<Sprite> spritePakage = std::shared_ptr<Sprite>(new Sprite());
	std::shared_ptr<ObjectTransform> transformLivraison = std::shared_ptr<ObjectTransform>(new ObjectTransform(_spawnPos, _spawnPos.y + spritePakage->getSprite().getGlobalBounds().height, NON_STATIC));
	std::shared_ptr<RigidBody> bodyPackage = std::shared_ptr<RigidBody>(new RigidBody());
	std::shared_ptr<Mouvement> mvtPackage = std::shared_ptr<Mouvement>(new Mouvement());
	std::shared_ptr<Animation> animLivraison = std::shared_ptr<Animation>(new Animation());
	std::shared_ptr<Package> PackageComponent = std::shared_ptr<Package>(new Package(_type, _spawnPos, _targetPos,
		{ static_cast<int>(_spawnPos.x), static_cast<int>(_spawnPos.y), 151,
		183 }));
	transformLivraison->setZBuffer(_targetPos.y);
	//spritePakage->getSprite().setScale(sf::Vector2f(0.5f, 0.5f));
	switch (_type)
	{
	case BLEU:
		animLivraison->addAnimation("LIVRAISON", "ColisBleu_chute.png", 8, 0.1, true);
		animLivraison->addAnimation("LANDING", "ColisBleu_Landing.png", 10, 0.08, false);
		animLivraison->addAnimation("IDLE", "ColisBleu_idle.png", 3, 0.1, true);
		PackageComponent->setType(BLEU);
		break;
	case JAUNE:
		animLivraison->addAnimation("LIVRAISON", "ColisJaune_chute.png", 8, 0.1, true);
		animLivraison->addAnimation("LANDING", "ColisJaune_Landing.png", 10, 0.08, false);
		animLivraison->addAnimation("IDLE", "ColisJaune_idle.png", 3, 0.1, true);
		PackageComponent->setType(JAUNE);
		break;
	case ROUGE:
		animLivraison->addAnimation("LIVRAISON", "ColisRouge_chute.png", 8, 0.1, true);
		animLivraison->addAnimation("LANDING", "ColisRouge_Landing.png", 10, 0.08, false);
		animLivraison->addAnimation("IDLE", "ColisRouge_idle.png", 3, 0.1, true);
		PackageComponent->setType(ROUGE);
		break;
	case VERT:
		animLivraison->addAnimation("LIVRAISON", "ColisVert_chute.png", 8, 0.1, true);
		animLivraison->addAnimation("LANDING", "ColisVert_Landing.png", 10, 0.08, false);
		animLivraison->addAnimation("IDLE", "ColisVert_idle.png", 3, 0.1, true);
		PackageComponent->setType(VERT);
		break;
	}
	drop->addComponents<Identity>(idDrop);
	drop->addComponents<Sprite>(spritePakage);
	drop->addComponents<ObjectTransform>(transformLivraison);
	drop->addComponents<RigidBody>(bodyPackage);
	drop->addComponents<Mouvement>(mvtPackage);
	drop->addComponents<Animation>(animLivraison);
	drop->addComponents<Package>(PackageComponent);
	return drop;

}