#pragma once
#include "GameComponent.h"

class COFFEECORE_API GameObject : public std::enable_shared_from_this<GameObject> {
private:
	std::unordered_map<std::type_index, std::shared_ptr<GameComponent>> m_components;
	std::list<std::shared_ptr<GameObject>> m_objects;
	std::weak_ptr<GameObject> m_parent;
	bool m_isActive;
public:
	static std::list<std::shared_ptr<GameObject>> l_Player;
	static std::list<std::shared_ptr<GameObject>> l_Ennemy;
	static std::list<std::shared_ptr<GameObject>> l_Ui;
	static std::list<std::shared_ptr<GameObject>> l_Collectible;
	static std::list<std::shared_ptr<GameObject>> l_Object;

	GameObject(bool _isActive = true);
	~GameObject();

	template<typename T>
	std::shared_ptr<T> getComponents() {
		for (auto _o : m_components) {
			if (_o.first == typeid(T)) {
				return std::reinterpret_pointer_cast<T>(_o.second);
			}
		}
		return nullptr;
	}

	std::shared_ptr<GameObject> getParent();
	void deleteAllObjects();
	void deleleteSameName(std::string _name);
	void deleteId(int _id);
	void deleteName(std::string _name);
	void addGameObject(std::shared_ptr<GameObject> _go);
	void destructComponent(std::shared_ptr<GameObject> _o);
	bool isActive();
	void setActive(bool _isActive);

	template<typename T>
	void addComponents(std::shared_ptr<T> _c) {
		m_components.emplace(std::pair(std::type_index(typeid(T)), _c));
		_c->setParents(this);
	}

	std::shared_ptr<GameObject> getObjects(Type _type);
	std::shared_ptr<GameObject> getObjects(std::string _name);
	std::vector<std::shared_ptr<GameObject>>getAllTypeObjects(Type _type);
	std::list<std::shared_ptr<GameObject>> getAllObjects() { return m_objects; }

	void updateAllObject();
	void updateAllComponents();

	void drawAllObject();
	void drawComponents();
};