#include "Light_Manager.h"

Light_Manager::Light_Manager()
{
	shader.loadFromFile("../Ressources/Game/SHADER/Lightmulti.frag", sf::Shader::Type::Fragment);
	render_State.shader = &shader;
	render_State.blendMode = sf::BlendAlpha;
	render_State.transform = sf::Transform::Identity;
	render_State.texture = NULL;
	Pass_Number = 0;
	m_shaderColor = sf::Vector3f(0.f, 0.f, 0.f);
	m_position = sf::Vector3f(0.f, 0.f, 0.f);
	m_AmbientColor = sf::Vector3f(0.f, 0.f, 0.f);
	m_shaderFalloff = 0.f;
	m_shaderRadius = 0.f;
	stockage = 0.f;
	m_nbLights = 0.f;
}

Light_Manager::~Light_Manager()
{
}

void Light_Manager::addLight(sf::Vector3f _position,
	sf::Vector3f _color, sf::Vector3f _AmbientColor, float _falloff, float _radius, bool _sparkling , bool _flickering)
{
	m_AmbientColor = _AmbientColor;
	lights.emplace_back(std::make_unique<Light>(_position, _color, _falloff, _radius, _sparkling, _flickering));
}

void Light_Manager::setCamera(std::shared_ptr<Camera> _camera)
{
	wp_camera = _camera;
}

void Light_Manager::update()
{
	/*sf::Mouse mouse;
	sf::Vector2i mousePos;
	mousePos = mouse.getPosition(window.getWindow());
	sf::Vector2f Pos;
	Pos = window.getWindow().mapPixelToCoords(mousePos, window.getWindow().getView());
	//std::cout << "mousePos.x : " << Pos.x << " mousePos.y : " << Pos.y << std::endl;*/
}

void Light_Manager::draw()
{
	for (size_t i = 0; i < lights.size(); i++) {
		if(lights[i]->GetIsSparkling()) {
			lights[i]->SetPosition(sf::Vector3f(lights[i]->GetPosition().x + tools::frand(-2.8f, 2.8f),
				lights[i]->GetPosition().y + tools::frand(-2.f, 2.f), 1.0f));
		}
		if(!lights[i]->GetIsSparkling()) {
			lights[i]->SetPosition(sf::Vector3f(lights[i]->GetPosition().x,
				lights[i]->GetPosition().y, 1.0f));
		}
		if (lights[i]->GetIsFlickering()) {
			lights[i]->SetFalloff(tools::frand(0.1f, 0.2f));
			//lights[i]->SetRadius(tools::frand(0, lights[i]->GetRadius()));
		}
		if (!lights[i]->GetIsFlickering()) {
			lights[i]->SetFalloff(lights[i]->GetFalloff());
			//lights[i]->SetRadius(lights[i]->GetRadius());
		}
	}
	Pass_Number = ceil(lights.size() / 3.f);
	temporary.create(static_cast<int>(window.getWindow().getSize().x),
		static_cast<int>(window.getWindow().getSize().y));
	temporary.update(window.getWindow());
	temporary_pass.create(static_cast<int>(window.getWindow().getSize().x),
		static_cast<int>(window.getWindow().getSize().y));
	shader.setUniform("DiffuseMap", temporary);
	shader.setUniform("AmbientLight", m_AmbientColor);
	stockage = 3 - (lights.size() % 3);

	for (int y = 0; y < Pass_Number; y++) {
		temporary_pass.update(window.getWindow());
		shader.setUniform("LastPass", temporary_pass);
		final_Sprite.setTexture(temporary_pass);

		shader.setUniform("PassNumber", y + 1);
		m_nbLights = (y + 1) * 3 > lights.size() ? 3 - stockage : 3;
		shader.setUniform("LightCount", m_nbLights);
		sf::Vector2f tmp = { 0.0f, 0.0f };
		for (int i = 0; i < m_nbLights; i++) {
			int index = y * 3 + i;

			sf::Vector2i tmpPos = window.getWindow().mapCoordsToPixel(sf::Vector2f(lights[index]->GetPosition().x,
				lights[index]->GetPosition().y), window.getWindow().getView());
			if (auto parent = m_Parents.lock()) {
				if (auto camera = wp_camera.lock()) {
					tmp = camera->getView().getCenter();
						float y = camera->getView().getViewport().height - tmpPos.y;
						/*lights[index]->GetPosition()*/
						shader.setUniform("Lights[" + std::to_string(i) + "].position", sf::Vector3f(tmpPos.x, y, lights[index]->GetPosition().z));
						shader.setUniform("Lights[" + std::to_string(i) + "].color", lights[index]->GetColor());
						shader.setUniform("Lights[" + std::to_string(i) + "].radius", lights[index]->GetRadius());
						shader.setUniform("Lights[" + std::to_string(i) + "].falloff", lights[index]->GetFalloff());
				}
			}
		}
		final_Sprite.setPosition({ tmp.x - 960.0f, tmp.y - 540.0f});
		window.getWindow().draw(final_Sprite, &shader);
	}
}

/*___________Class Light___________*/
Light::Light()
{
	position = { 0.f,0.f,0.f };
	color = { 0.f,0.f,0.f };
	radius = 0.f;
	falloff = 0.f;
	is_sparkling = false;
}
Light::~Light() {}
Light::Light(sf::Vector3f _position,
	sf::Vector3f _color, float _falloff, float _radius, bool _sparkling, bool _flickering){
	position = _position;
	color = _color;
	falloff = _falloff;
	radius = _radius;
	is_sparkling = _sparkling;
	is_Flickering = _flickering;
}
sf::Vector3f Light::GetPosition() { return position; }
sf::Vector3f Light::GetColor() { return color; }
float Light::GetRadius() { return radius; }
float Light::GetFalloff() { return falloff; }

bool Light::GetIsSparkling(){return is_sparkling;}
bool Light::GetIsFlickering(){return is_Flickering;}

void Light::SetPosition(sf::Vector3f _position) { position = _position; }
void Light::SetColor(sf::Vector3f _color) { color = _color; }
void Light::SetRadius(float _radius) { radius = _radius; }
void Light::SetFalloff(float _falloff) { falloff = _falloff; }
void Light::SetSparkling(bool _sparkling){is_sparkling = _sparkling;}
void Light::SetFlickering(bool _flickering){is_Flickering = _flickering;}
