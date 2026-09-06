#pragma once
#include <string>
#include "core/filemanagement/json.h"

namespace FikaECS
{
	class Entity;
	class ECSManager;
}

struct Prefab
{
	std::string name;
	nlohmann::json data;
};

class GameResourceManager
{
private:
	FikaECS::ECSManager* ecsManager;

public:
	GameResourceManager();
	~GameResourceManager();

	void init();
	void makePrefab(FikaECS::Entity& entity, const char* path);
	void loadPrefab(const char* path, Prefab& out);
};