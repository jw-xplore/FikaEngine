#pragma once
#include <vector>
#include <memory>

class GameObject;
class Component;

struct GameObjectId;

namespace GameObjectManager
{
	/**
	 * @brief Call at start to setup game objects storage.
	 */
	void init();

	/**
	 * @brief Updates all game objects in list, including their components. Takes care of removing game objects.
	 * @param dt 
	 */
	void update(float dt);

	/**
	 * @brief Creates new empty GameObject.
	 * @return Pointer to created GameObject.
	 */
	GameObject* addGameObject();

	/**
	 * @brief Reserves GameObject for removal from list. Reserved GameObject is deleted after update of all objects.
	 * @param gameObject Pointer to game object.
	 */
	void removeGameObject(GameObject* gameObject);

	/**
	 * @brief
	 * @param id 
	 * @return GameObject pointer of matching id. 
	 */
	GameObject* findById(GameObjectId id);
};