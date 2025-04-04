#include "Particules.h"

Particules::Particules() {}

Particules::Particules(sf::Vector2f _position,std::string _nameTexture, DirectionParticules _dir,
	sf::Uint8 _opacite, float _speed, float _eraseSpeed)
{
	m_position = _position;
	m_speed = _speed;
	m_opacite = _opacite;
	m_name = _nameTexture;
	direction = _dir;
	m_erasespeed = _eraseSpeed;
	m_sprite.setTexture(RessourceManager::get()->getSceneTexture(m_name));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
}

Particules::~Particules() {}

void Particules::update()
{
	for (Particules* i : m_vector) {
		//i->m_sprite.setSize(sf::Vector2f(i->width, i->height));
		i->m_sprite.setColor(sf::Color(255,255,255, i->m_opacite));
		if (i->direction == HAUT) {
			i->m_position.y -= i->m_speed * tools::GetTimeDelta();
		}
		else if (i->direction == BAS) {
			i->m_position.y += i->m_speed * tools::GetTimeDelta();
		}
		else if (i->direction == GAUCHE) {
			i->m_position.x -= i->m_speed * tools::GetTimeDelta();
		}
		else if (i->direction == DROITE) {
			i->m_position.x += i->m_speed * tools::GetTimeDelta();
		}
		else if (i->direction == STATIQUE) {
			
		}
		i->m_sprite.setPosition(i->m_position);
	}
}

void Particules::draw()
{
	for (Particules* i : m_vector) {
		window.draw(i->m_sprite);
		i->m_opacite -= i->m_erasespeed * tools::GetTimeDelta();
	}
	for (int n = 0; n < m_vector.size(); n++) {
		if (m_vector[n]->m_opacite <= 5) {
			m_vector.erase(m_vector.begin() + n);
		}
	}
}

void Particules::addParticules(sf::Vector2f _position, std::string _nameTexture, DirectionParticules _dir,
	sf::Uint8 _opacite, float _speed, float _eraseSpeed)
{
	m_vector.push_back(new Particules(_position, _nameTexture, _dir,_opacite, _speed,_eraseSpeed));
}
