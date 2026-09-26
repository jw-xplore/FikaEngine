#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "core/filemanagement/json.h"
#include "core/game_resource_manager.h"
#include "editor_camera.h"
#include "renderer/resources/mesh_instance.h"

using namespace FikaEngine;

namespace FikaEditor
{
	struct ProjectMetaData
	{
		std::string name;
		std::string sourcePath;
	};

	class Editor
	{
	private:
		char workingDirectory[256] = "C:/Projects/Prog/FikaEngine/build/projects/testgame/Debug/";
		char executable[256] = "testgame.exe";
		char levelName[256] = "testLevel.json";
		//char activePrefabPath[256] = "C:/Projects/Prog/FikaEngine/build/projects/testgame/Debug/assets/prefabs/wall.json";

		Prefab* activePrefab = nullptr;
		char projectPrefabPath[256] = "C:/Projects/Prog/FikaEngine/build/projects/testgame/Debug/assets/prefabs/";
		std::vector<Prefab*> projectPrefabs;
		bool projectLoaded = false;
		ProjectMetaData metaData;

		MeshInstance* placingCube = nullptr;
		glm::mat4 placingTransform = glm::mat4(1.95);
		EditorCamera editorCamera;

		bool cursorInsideGui = false;

		void debugUI(GLFWwindow* window);

	public:
		Editor();

		void init();
		void update(float dt);

		bool loadProject();
		void loadActivePrefab();
		void saveLevel(const char* path);
		void runGame();

		glm::vec3 positionFromScreenSpace();
		glm::vec3 screenToWorldGround(const glm::vec2 mouse, const glm::vec2 screenSize, const glm::mat4& view, const glm::mat4& projection);
		void placeObject(glm::vec3 position);
		nlohmann::json meshJsonFromPrefab(Prefab& prefab);

		void selectPrefab();
	};
}