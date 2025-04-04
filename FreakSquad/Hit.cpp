#include "Hit.h"

Hit::Hit()
{

}

Hit::Hit(sf::Sprite _sprite, sf::Vector2f _position, sf::Vector2f _scale)
{
	m_sprite = _sprite;
	m_position = _position;
	m_scale = _scale;
	m_opacite = 255;
	m_sprite.setTexture(RessourceManager::get()->getSceneTexture("126.199..504.199.png"));
	m_rect = { 0,0,126,199 };// 1er hit léger
	//m_sprite.setTexture(RessourceManager::get()->getSceneTexture("207.384..812.384.png"));
	//m_rect = { 0,0,207,384 }; // 2ème hit léger
	m_sprite.setTextureRect(m_rect);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(m_scale);
	m_sprite.setOrigin(m_sprite.getTextureRect().height / 2, m_sprite.getTextureRect().width / 2);
}

Hit::~Hit() {}

void Hit::update()
{
	for (Hit* i : m_vecteur) {
		i->animTime += tools::GetTimeDelta();
		if (i->animTime > 0.08f) {
			if (i->FrameX < 3)
				i->FrameX++;
			else i->FrameX = 3;
			i->animTime = 0.0f;
		}
		i->m_rect.left = i->FrameX * i->m_rect.width;
		i->m_sprite.setTextureRect(i->m_rect);
		i->m_sprite.setScale(i->m_scale);
		i->m_sprite.setColor(sf::Color(255, 255, 255, i->m_opacite));
		i->m_sprite.setPosition(i->m_position);
		i->m_opacite -= 290.f * tools::GetTimeDelta();
	}


	for (int n = 0; n < m_vecteur.size(); n++) {
		if (m_vecteur[n]->m_opacite <= 5.f) {
			m_vecteur.erase(m_vecteur.begin() + n);
		}
	}
}

void Hit::draw()
{
	for (Hit* i : m_vecteur) {
		window.draw(i->m_sprite);
	}
}

void Hit::add(sf::Vector2f _position, sf::Vector2f _scale)
{
	for (int i = 0; i < 1; i++) {
		m_vecteur.push_back(new Hit(m_sprite, _position, _scale));
	}
}

/*____________BIG_HIT______________*/
BigHit::BigHit()
{
}

BigHit::BigHit(sf::Sprite _sprite, sf::Vector2f _position, sf::Vector2f _scale)
{
	m_Bigsprite = _sprite;
	m_Bigposition = _position;
	m_Bigscale = _scale;
	m_Bigopacite = 255;
	m_Bigsprite.setTexture(RessourceManager::get()->getSceneTexture("207.384..812.384.png"));
	m_Bigrect = { 0,0,207,384 }; // Hit lourd
	m_Bigsprite.setTextureRect(m_Bigrect);
	m_Bigsprite.setPosition(m_Bigposition);
	m_Bigsprite.setScale(m_Bigscale);
	m_Bigsprite.setOrigin(m_Bigsprite.getTextureRect().height / 2,
		m_Bigsprite.getTextureRect().width / 2);
}

BigHit::~BigHit() {}

void BigHit::update()
{
	for (BigHit* i : m_Bigvecteur) {
		i->BiganimTime += tools::GetTimeDelta();
		if (i->BiganimTime > 0.08f) {
			if (i->BigFrameX < 3)
				i->BigFrameX++;
			else i->BigFrameX = 3;
			i->BiganimTime = 0.0f;
		}
		i->m_Bigrect.left = i->BigFrameX * i->m_Bigrect.width;
		i->m_Bigsprite.setTextureRect(i->m_Bigrect);
		i->m_Bigsprite.setScale(i->m_Bigscale);
		i->m_Bigsprite.setColor(sf::Color(255, 255, 255, i->m_Bigopacite));
		i->m_Bigsprite.setPosition(i->m_Bigposition);
		i->m_Bigopacite -= 330.f * tools::GetTimeDelta();
	}
	for (int n = 0; n < m_Bigvecteur.size(); n++) {
		if (m_Bigvecteur[n]->m_Bigopacite <= 10.f) {
			m_Bigvecteur.erase(m_Bigvecteur.begin() + n);
		}
	}
}

void BigHit::draw()
{
	for (BigHit* i : m_Bigvecteur) {
		window.draw(i->m_Bigsprite);
	}
}

void BigHit::add(sf::Vector2f _position, sf::Vector2f _scale)
{
	for (int i = 0; i < 5; i++) {
		m_Bigvecteur.push_back(new BigHit(m_Bigsprite, _position, _scale));
	}
}
