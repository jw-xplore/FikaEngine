#pragma once
#include <vector>
#include <memory>

class GameObject;
class Component;

struct GameObjectId;

class GameObjectManager
{
private:
	// TODO: Use pool allocator
	std::vector<std::unique_ptr<GameObject>> gameObjects;

	std::vector<GameObject*> removeGOs;
	int removeGOsCount = 0;

public:
	GameObjectManager();
	~GameObjectManager();

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

	void serialize(const char* filePath);
};