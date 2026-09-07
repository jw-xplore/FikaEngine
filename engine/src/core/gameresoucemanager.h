#pragma once
#include <string>
#include "core/filemanagement/json.h"
#include <filesystem>
#include <map>

namespace FikaECS
{
	class Entity;
	class ECSManager;
}

struct Prefab
{
	std::string name;
	std::string path;
	nlohmann::json data;
};

class GameResourceManager
{
private:
	FikaECS::ECSManager* ecsManager;
	std::map<std::string, Prefab> loadedPrefabs;

public:
	GameResourceManager();
	~GameResourceManager();

	void init();
	void makePrefab(FikaECS::Entity& entity, const char* path);
	void loadPrefab(const char* path, Prefab& out);
	void loadFolderPrefabs(const char* path);
};