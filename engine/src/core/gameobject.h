#pragma once
#include <vector>
#include <memory>
#include "component.h"
#include <glm/glm.hpp>
#include "components/transform.h"

class Component;

static unsigned int lastGameObjectId = 0;

struct GameObjectId
{
	unsigned int id = 0;

	inline bool operator==(const GameObjectId& rhs) { return this->id == rhs.id; }
	inline bool operator!=(const GameObjectId& rhs) { return this->id != rhs.id; }
};

/**
 * @brief Main object for engine entity. Holds list of functional components and it is updated by GameObjectManager.
 */
class GameObject
{
private:
	GameObjectId id;
	std::vector<std::unique_ptr<Component>> components;
	TransformComponent transformComponent;

public:
	GameObject();
	~GameObject() {}

	/**
	 * @brief Find first component of selected type from components list.
	 * @tparam T Must be of class Component.
	 */
	template<typename T>
	inline T* getComponent()
	{
		for (auto& comp : components)
		{
			T* casted = dynamic_cast<T*>(comp.get());
			if (casted)
				return casted;
		}

		return nullptr;
	}

	/**
	 * @brief Add new component into components list.
	 * @tparam T Must be of class Component.
	 * @return Pointer to new created component object.
	 */
	template<typename T>
	inline T* addComponent()
	{
		auto component = std::make_unique<T>();
		T* rawPtr = component.get();
		components.push_back(std::move(component));

		Component* cmp = dynamic_cast<Component*>(rawPtr);
		cmp->owner = this;
		cmp->start();

		return rawPtr;
	}

	/**
	 * @brief Remove selected component from components list if found.
	 * @param component 
	 */
	void removeComponent(Component* component);

	/**
	 * @brief Get unique id of gameobject
	 * @return 
	 */
	inline GameObjectId getId() { return id; }

	/**
	 * @brief List of all components
	 * @return 
	 */
	inline std::vector<std::unique_ptr<Component>>& getComponents() { return components; }

	inline TransformComponent& getTransformComponent() { return transformComponent; }
	inline glm::mat4& getTransform() { return transformComponent.getTransformMatrix(); }
	inline glm::vec3 getPosition()
	{ 
		glm::vec3 pos = transformComponent.getTransformMatrix()[3];
		return glm::vec3(pos.x, pos.y, pos.z);
	}
};