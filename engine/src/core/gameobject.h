#pragma once
#include <vector>
#include <memory>
#include "component.h"
#include <glm/glm.hpp>

class Component;

static unsigned int lastGameObjectId = 0;

struct GameObjectId
{
	unsigned int id = 0;

	inline bool operator==(const GameObjectId& rhs) { return this->id == rhs.id; }
	inline bool operator!=(const GameObjectId& rhs) { return this->id != rhs.id; }
};

class GameObject
{
private:
	GameObjectId id;
	std::vector<std::unique_ptr<Component>> components;
	glm::mat4 transform;

public:
	GameObject();
	~GameObject() {}

	template<typename T>
	inline void getComponent()
	{
		for (auto& comp : components)
		{
			if (auto& casted = dynamic_cast<T*>(comp))
				return casted;
		}
	}

	template<typename T>
	inline T* addComponent()
	{
		auto component = std::make_unique<T>();
		T* rawPtr = component.get();
		components.push_back(std::move(component));

		Component* cmp = dynamic_cast<Component*>(rawPtr);
		cmp->owner = this;
		cmp->start();
		//rawPtr.start();

		return rawPtr;
	}

	void removeComponent(Component* component);

	inline GameObjectId getId() { return id; }
	inline std::vector<std::unique_ptr<Component>>& getComponents() { return components; }

	inline glm::mat4 getTransform() { return transform; }
	void setPosition(glm::vec3 position);
	void setRotation(glm::vec4 rotation);
	void setScale(glm::vec3 scale);
	void translate(glm::vec3 translation);
	void rotate(glm::vec4 rotation);
};