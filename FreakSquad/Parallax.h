#pragma once
#include "CoffeeCore.hpp"

struct LayerParallax
{
	sf::Sprite sprite;
	sf::Vector2f position;
	float speed;
};

class Parallax : public GameComponent
{
public:
	Parallax();
	~Parallax();

	void initParallax(std::shared_ptr<GameObject> _object);
	/// \brief récupère la position de l'object transform du joueur
	void setPositionToObjectTransform(std::shared_ptr<GameObject>& _object);

	void update();
	void draw();

private:
	std::vector<LayerParallax> v_layers;
	sf::Vector2f m_posPlayer;
	LayerParallax screen1;
	LayerParallax dial;
	LayerParallax apresdial;
	LayerParallax seconddia;
	LayerParallax dernierscreen;
	/// \brief charge la texture en récupérant le nom de la texture, sa position et si l'on souhaite la rendre transparente ou non
	/// \brief et la met dans la structure LayerParallax
	void loadLayerTexture(LayerParallax& _layer, const std::string& _texturePath, const sf::Vector2f& _position, bool _transparent);
};

//						   %%%%%%%%
//			     %%%%%%%%%%%%%%
//		   %%%%%%%  y        %%%%%%%
//		%%%%%%%    r)          %%%%%%%
//		  %%%%%%     (  v         %%%%%%
//			   %%%%%     ]        %%%%%