#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "core/filemanagement/json.h"

struct Prefab;

namespace FikaEditor
{
	class Editor
	{
	private:
		char workingDirectory[256] = "C:/Projects/Prog/FikaEngine/build/projects/testgame/Debug/";
		char executable[256] = "testgame.exe";
		char levelPath[256] = "C:/Projects/Prog/FikaEngine/build/projects/testgame/Debug/assets/levels/testLevel.json";
		//char activePrefabPath[256] = "C:/Projects/Prog/FikaEngine/build/projects/testgame/Debug/assets/prefabs/wall.json";

		Prefab* activePrefab;
		char projectPrefabPath[256] = "C:/Projects/Prog/FikaEngine/build/projects/testgame/Debug/assets/prefabs/";
		std::vector<Prefab*> projectPrefabs;

		void debugUI(GLFWwindow* window);
	public:
		void update();

		bool loadProject();
		void loadActivePrefab();
		void saveLevel(const char* path);
		void runGame();

		glm::vec3 positionFromScreenSpace(glm::vec2 position);
		void placeObject(glm::vec3 position);
		nlohmann::json meshJsonFromPrefab(Prefab& prefab);

		void selectPrefab();
	};
}