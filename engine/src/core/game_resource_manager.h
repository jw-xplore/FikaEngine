#pragma once
#include <string>
#include "core/filemanagement/json.h"
#include <filesystem>
#include <map>

namespace FikaEngine
{
	class Entity;
	class ECSManager;

	struct ProjectMetaData
	{
		std::string name;
		std::string sourcePath;
	};

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
		ProjectMetaData projectMetaData;

	public:
		GameResourceManager();
		~GameResourceManager();

		void init();
		bool loadProject(ProjectMetaData& metaData);
		void makePrefab(Entity& entity, const char* path);
		void loadPrefab(const char* path, Prefab& out);
		Prefab* getLoadedPrefab(std::string path);
		std::vector<Prefab*> getLoadedPrefabsList();
		void loadFolderPrefabs(const char* path);

		ProjectMetaData getProjectMetaData() { return projectMetaData; }
	};
} // namespace FikaEngine