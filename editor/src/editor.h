#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace FikaEditor
{
	class Editor
	{
	private:
		char workingDirectory[256] = "C:/Projects/Prog/FikaEngine/build/projects/testgame/Debug/";
		char executable[256] = "testgame.exe";
		char levelPath[256] = "C:/Projects/Prog/FikaEngine/build/projects/testgame/Debug/assets/levels/testLevel.json";

		void debugUI(GLFWwindow* window);
	public:
		void update();

		bool loadProject();
		void runGame();

		glm::vec3 positionFromScreenSpace(glm::vec2 position);
		void placeObject(glm::vec3 position);
	};
}