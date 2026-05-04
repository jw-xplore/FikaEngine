#pragma once
#include <vector>
#include <memory>
#include "component.h"

class Component;

static unsigned int lastGameObjectId = 0;

struct GameObjectId
{
	unsigned int id = 0;
};

class GameObject
{
private:
	GameObjectId id;
	std::vector<std::unique_ptr<Component>> components;

public:
	GameObject();
	~GameObject();

	template<typename T>
	void getComponent()
	{
		for (auto& comp : components)
		{
			if (auto& casted = dynamic_cast<T*>(comp))
				return casted;
		}
	}

	template<typename T>
	void addComponent()
	{
		auto component = std::make_unique<T>();
		T* rawPtr = component.get();
		components.push_back(std::move(component));
		return rawPtr;
	}

	void removeComponent(Component* component);

	inline GameObjectId getId() { return id; }
	inline std::vector<std::unique_ptr<Component>>& getComponents() { return components; }
};