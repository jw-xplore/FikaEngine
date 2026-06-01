#pragma once
#include <vector>
#include <memory>

class GameObject;
class Component;

struct GameObjectId;

class GameObjectManager
{
private:
	std::vector<std::unique_ptr<GameObject>> gameObjects;

	int removeGOsCount = 0;
	std::vector<GameObject*> removeGOs;

public:
	GameObjectManager();
	~GameObjectManager() {}

	void update(float dt);
	GameObject* addGameObject();
	void removeGameObject(GameObject* gameObject);
	GameObject* findById(GameObjectId id);
};