#include "gameresoucemanager.h"
#include <fstream>
#include "ecs/ecsmanager.h"
#include "core/systemsHolder.h"
#include <iostream>

GameResourceManager::GameResourceManager()
{
	
}

GameResourceManager::~GameResourceManager()
{

}

void GameResourceManager::init()
{
	ecsManager = SystemsHolder::getECSManager();
}

void GameResourceManager::makePrefab(FikaECS::Entity& entity, const char* path)
{
	nlohmann::json js = ecsManager->serializeEntity(entity);

	std::ofstream file(path);

	if (!file.is_open())
	{
		std::cout << "Can't serialize game objects as levels folder/file is not found \n";
		return;
	}

	file << std::setw(4) << js;
	file.close();
}

void GameResourceManager::loadPrefab(const char* path, Prefab& out)
{
	// Read json
	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cout << "Failed to load level \n";
		return;
	}

	// Parse data
	nlohmann::json js = nlohmann::ordered_json::parse(file);
	file.close();

	nlohmann::json jsEntity = js["entity"];
	out.name = jsEntity["name"];
	out.data = js;
}