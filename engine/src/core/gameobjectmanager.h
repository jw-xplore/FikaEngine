#pragma once
#include <vector>
#include <memory>

class GameObject;
class Component;

struct GameObjectId;

namespace GameObjectManager
{
	void init();

	void update(float dt);
	GameObject* addGameObject();
	void removeGameObject(GameObject* gameObject);
	GameObject* findById(GameObjectId id);
};