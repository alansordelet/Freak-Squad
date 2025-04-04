#pragma once
#include "CoffeeCore.hpp"
#include "Camera.h"

class Light {/*Classe qui gère les propriétés de chaque light séparément*/
private:
	sf::Vector3f position;
	sf::Vector3f color;
	float radius;
	float falloff;
	bool is_sparkling;
	bool is_Flickering;
public:
	Light();/*Constructeur par défaut*/
	Light(sf::Vector3f _position, sf::Vector3f _color,
		float _falloff, float _radius, bool _sparkling, bool _flickering);/*Constructeur spécialisé*/
	~Light();/*Destrtucteur*/

	/*mutateurs et accesseurs*/
	sf::Vector3f GetPosition();
	sf::Vector3f GetColor();
	float GetRadius();
	float GetFalloff();
	bool GetIsSparkling();
	bool GetIsFlickering();

	void SetPosition(sf::Vector3f _position);
	void SetColor(sf::Vector3f _color);
	void SetRadius(float _radius);
	void SetFalloff(float _falloff);
	void SetSparkling(bool _sparkling);
	void SetFlickering(bool _flickering);
};

class Light_Manager : public GameComponent
{/*Classe qui gère le groupe de light*/
private:
	std::vector<std::unique_ptr<Light>> lights;

	
	sf::RenderStates render_State;
	sf::Texture temporary;
	sf::Texture temporary_pass;
	sf::Sprite final_Sprite;
	sf::Vector3f m_position;
	sf::Vector3f m_AmbientColor;
	sf::Vector3f m_shaderColor;
	float m_shaderFalloff;
	float m_shaderRadius;
	int Pass_Number;
	int stockage;
	int m_nbLights;
	size_t vector_size;
	std::weak_ptr<Camera> wp_camera;
public:
	Light_Manager();/*Constructeur par défaut*/
	~Light_Manager();/*Destrtucteur*/
	sf::Shader shader;
	void addLight(sf::Vector3f _position,
		sf::Vector3f _color, sf::Vector3f _AmbientColor,
		float _falloff, float _radius, bool _sparkling, bool _flickering);/*Fonction qui permet l'ajout visuel de light
	la seule a utiliser pour instancier une light*/

	void setCamera(std::shared_ptr<Camera> _camera);

	void update();
	void draw();
};

