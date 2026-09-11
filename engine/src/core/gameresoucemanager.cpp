#include "gameresoucemanager.h"
#include <fstream>
#include "ecs/ecsmanager.h"
#include "core/fika_servers.h"
#include <iostream>

GameResourceManager::GameResourceManager()
{
	
}

GameResourceManager::~GameResourceManager()
{

}

void GameResourceManager::init()
{
	ecsManager = &FikaServers::getECSManager();
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

	file << std::setw(2) << js;
	file.close();
}

void GameResourceManager::loadPrefab(const char* path, Prefab& out)
{
	// Read json
	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cout << "Failed to load prefab: " << path << "\n";
		return;
	}

	// Parse data
	nlohmann::json js = nlohmann::ordered_json::parse(file);
	file.close();

	nlohmann::json jsEntity = js["entity"];
	out.name = jsEntity["name"];
	out.path = path;
	out.data = js;
}

Prefab* GameResourceManager::getLoadedPrefab(std::string path)
{
	if (loadedPrefabs.find(path) == loadedPrefabs.end())
		return nullptr;

	return &loadedPrefabs[path];
}

std::vector<Prefab*> GameResourceManager::getLoadedPrefabsList()
{
	std::vector<Prefab*> prefabs;
	std::map<std::string, Prefab>::iterator it;

	for (it = loadedPrefabs.begin(); it != loadedPrefabs.end(); it++)
	{
		prefabs.push_back(&it->second);
	}

	return prefabs;
}

void GameResourceManager::loadFolderPrefabs(const char* path)
{
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		Prefab pref;
		std::string prefPath = entry.path().string();
		loadPrefab(prefPath.c_str(), pref);

		loadedPrefabs[prefPath] = pref;
	}
}