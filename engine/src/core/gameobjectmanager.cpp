#include "gameobjectmanager.h"
#include "gameobject.h"
#include "component.h"

GameObjectManager::GameObjectManager()
{
	gameObjects.reserve(256);
	removeGOs.reserve(16);
}

void GameObjectManager::Update(float dt)
{
	// Update
	for (auto& go : gameObjects)
	{
		for (auto& comp : go->getComponents())
		{
			comp->Update(dt);
		}
	}

	// Remove
	if (removeGOsCount > 0)
	{
		for (auto& gameObject : removeGOs)
		{
			gameObjects.erase(
				std::remove_if(gameObjects.begin(), gameObjects.end(),
					[&](const std::unique_ptr<GameObject>& go)
					{
						return go.get() == gameObject;
					}),
				gameObjects.end()
			);
		}

		removeGOs.clear();
		removeGOsCount = 0;
	}
}

GameObject* GameObjectManager::AddGameObject()
{
	return nullptr;
}

void GameObjectManager::RemoveGameObject(GameObject* gameObject)
{
	removeGOs.push_back(gameObject);
	removeGOsCount++;
}

GameObject* GameObjectManager::FindById(GameObjectId id)
{
	for (auto& go : gameObjects)
	{
		if (go.get()->getId() == id)
			return go.get();
	}

	return nullptr;
}