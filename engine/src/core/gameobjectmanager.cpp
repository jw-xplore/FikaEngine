#include "gameobjectmanager.h"
#include "gameobject.h"
#include "component.h"

GameObjectManager::GameObjectManager()
{
	gameObjects.reserve(256);
}

void GameObjectManager::Update(float dt)
{
	for (auto& go : gameObjects)
	{
		for (auto& comp : go->getComponents())
		{
			comp->Update(dt);
		}
	}
}

GameObject* GameObjectManager::AddGameObject()
{
	return nullptr;
}

void GameObjectManager::RemoveGameObject(GameObject* gameObject)
{

}

GameObject* GameObjectManager::FindById(GameObjectId id)
{
	return nullptr;
}