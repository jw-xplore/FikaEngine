#pragma once
#include <string>
#include "core/filemanagement/json.h"
#include <filesystem>
#include <map>

class Entity;
class ECSManager;

struct Prefab
{
	std::string name;
	std::string path;
	nlohmann::json data;
};

class GameResourceManager
{
private:
	ECSManager* ecsManager;
	std::map<std::string, Prefab> loadedPrefabs;

public:
	GameResourceManager();
	~GameResourceManager();

	void init();
	void makePrefab(Entity& entity, const char* path);
	void loadPrefab(const char* path, Prefab& out);
	Prefab* getLoadedPrefab(std::string path);
	std::vector<Prefab*> getLoadedPrefabsList();
	void loadFolderPrefabs(const char* path);
};