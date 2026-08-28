#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace FikaEditor
{
	class Editor
	{
	private:
		char workingDirectory[256] = "C:/Projects/Prog/FikaEngine/build/projects/testgame/Debug/";
		char executable[256] = "testgame.exe";

		//std::string projectPath = "C:/Projects/Prog/FikaEngine/build/projects/testgame/Debug/";
		//std::string gameName = "testgame.exe";
		void debugUI(GLFWwindow* window);
	public:
		void update();

		bool loadProject();
		void runGame();
	};
}