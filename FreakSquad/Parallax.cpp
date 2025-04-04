#include "Parallax.h"
#include "Camera.h"

Parallax::Parallax()
{
	loadLayerTexture(screen1, "parallaxScreen1.png", sf::Vector2f{ 0.f, 1080.f }, false);
	loadLayerTexture(dial, "dia1.png", sf::Vector2f{ 2300.f, 1080.f }, true);
	loadLayerTexture(apresdial, "apresdia1.png", sf::Vector2f{ 7180.f, 3240.f }, true);
	loadLayerTexture(seconddia, "2emedia.png", sf::Vector2f{ 14795.f, 2150.f }, true);
	loadLayerTexture(dernierscreen, "dernierscreen.png", sf::Vector2f{ 24075.f, 4320.f }, true);
}

Parallax::~Parallax()
{
}

void Parallax::initParallax(std::shared_ptr<GameObject> _object)
{
	std::shared_ptr<GameObject> sptr_parallax = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Identity> id_parallax = std::shared_ptr<Identity>(new Identity("Parallax", OBJECT));
	std::shared_ptr<ObjectTransform> pos1 = std::shared_ptr<ObjectTransform>(new ObjectTransform(sf::Vector2f(0.f, 0.0f), -INFINITY, STATIC));

	std::shared_ptr<Parallax> background_parallax = std::shared_ptr<Parallax>(new Parallax());
	sptr_parallax->addComponents<Identity>(id_parallax);
	sptr_parallax->addComponents<Parallax>(background_parallax);
	sptr_parallax->addComponents<ObjectTransform>(pos1);
	_object->addGameObject(sptr_parallax);
}

void Parallax::setPositionToObjectTransform(std::shared_ptr<GameObject>& _object)
{
}

void Parallax::update()
{
	if (auto parent = getParents().lock())
		m_posPlayer = parent->getParent()->getObjects("Camera")->getComponents<Camera>()->getViewPos();

	for (auto& layer : v_layers)
		layer.sprite.setPosition(layer.position.x + (-m_posPlayer).x * layer.speed, layer.position.y);
}

void Parallax::draw()
{
	for (const auto& layer : v_layers)
		window.draw(layer.sprite);
}

void Parallax::loadLayerTexture(LayerParallax& _layer, const std::string& _texturePath, const sf::Vector2f& _position, bool _transparent)
{
	_layer.position = _position;
	_layer.sprite.setTexture(RessourceManager::get()->getSceneTexture(_texturePath));
	_layer.sprite.setPosition(_layer.position);
	_layer.speed = 0.02f;
	if (_transparent)
	{
		sf::Color layerColor = _layer.sprite.getColor();
		layerColor.a = 128;
		_layer.sprite.setColor(layerColor);
	}
	v_layers.push_back(_layer);
}

//						   %%%%%%%%
//			     %%%%%%%%%%%%%%
//		   %%%%%%%  y        %%%%%%%
//		%%%%%%%    r)          %%%%%%%
//		  %%%%%%     (  v         %%%%%%
//			   %%%%%     ]        %%%%%