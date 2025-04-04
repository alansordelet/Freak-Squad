#include "Boss_Smoke.h"

Boss_Smoke::Boss_Smoke()
{

}

Boss_Smoke::Boss_Smoke(sf::Sprite _sprite, sf::Vector2f _position, float _speed, float _angle, sf::Vector2f _scale)
{
	//m_sprite1 = _sprite;
	m_position = _position;
	m_scale = _scale;
	m_angle = _angle;
	m_speed = _speed;
	m_opacite = 255;
	//m_sprite.setTexture(RessourceManager::get()->getSceneTexture("126.199..504.199.png"));
	//m_rect = { 0,0,126,199 };// 1er hit léger
	m_sprite1.setTexture(RessourceManager::get()->getSceneTexture("smokeg2Lineless.png"));
	m_sprite2.setTexture(RessourceManager::get()->getSceneTexture("smokeg3Lineless.png"));
	m_sprite3.setTexture(RessourceManager::get()->getSceneTexture("smokeg4Lineless.png"));
	m_sprite4.setTexture(RessourceManager::get()->getSceneTexture("smokegLineless.png"));
	m_rect = { 0,0,207,384 }; // 2ème hit léger
	m_sprite1.setPosition(m_position);
	m_sprite1.setScale(m_scale);
	m_sprite1.setOrigin(m_sprite1.getTextureRect().height / 2, m_sprite1.getTextureRect().width / 2);
}

Boss_Smoke::~Boss_Smoke() {}

void Boss_Smoke::update()
{
	for (Boss_Smoke* i : m_vecteur) {
		i->m_position.x += Boss_Smoke::Norm(i->m_speed, i->m_angle).x * tools::GetTimeDelta();
		i->m_position.y += Boss_Smoke::Norm(i->m_speed, i->m_angle).y * tools::GetTimeDelta();

		i->m_sprite1.setScale(i->m_scale);
		i->m_sprite1.setColor(sf::Color(255, 255, 255, i->m_opacite));
		i->m_sprite1.setPosition(i->m_position);

		//i->m_sprite2.setScale(i->m_scale);
		//i->m_sprite2.setColor(sf::Color(255, 255, 255, i->m_opacite));
		//i->m_sprite2.setPosition(i->m_position);

		//i->m_sprite3.setScale(i->m_scale);
		//i->m_sprite3.setColor(sf::Color(255, 255, 255, i->m_opacite));
		//i->m_sprite3.setPosition(i->m_position);

		/*i->m_sprite4.setScale(i->m_scale);
		i->m_sprite4.setColor(sf::Color(255, 255, 255, i->m_opacite));
		i->m_sprite4.setPosition(i->m_position);*/

		i->m_opacite -= 100.f * tools::GetTimeDelta();
	}


	for (int n = 0; n < m_vecteur.size(); n++) {
		if (m_vecteur[n]->m_opacite <= 5.f) {
			m_vecteur.erase(m_vecteur.begin() + n);
		}
	}
}

void Boss_Smoke::draw()
{
	for (Boss_Smoke* i : m_vecteur) {
		window.draw(i->m_sprite1);
		//window.draw(i->m_sprite2);
		//window.draw(i->m_sprite3);
		//window.draw(i->m_sprite4);
	}
}

void Boss_Smoke::add(sf::Vector2f _position, float _speed, float _angle, sf::Vector2f _scale)
{

	m_vecteur.push_back(new Boss_Smoke(m_sprite1, _position, _speed, _angle, _scale));
	//m_vecteur.push_back(new Boss_Smoke(m_sprite2, _position, _speed, _angle,  _scale));
	//m_vecteur.push_back(new Boss_Smoke(m_sprite3, _position, _speed, _angle, _scale));
	//m_vecteur.push_back(new Boss_Smoke(m_sprite4, _position, _speed, _angle, _scale));

}
