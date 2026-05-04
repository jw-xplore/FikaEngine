#pragma once
#include <vector>
#include <memory>

class GameObject;
class Component;

struct GameObjectId;

class GameObjectManager
{
public:
	std::vector<std::unique_ptr<GameObject>> gameObjects;

	GameObjectManager();
	~GameObjectManager() {}

	void Update(float dt);
	GameObject* AddGameObject();
	void RemoveGameObject(GameObject* gameObject);
	GameObject* FindById(GameObjectId id);
};