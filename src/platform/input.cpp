#include "input.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h> 

InputManager::InputManager()
{
	//GLFWwindow* window = glfwGetCurrentContext();
	//lastMouseX = window.
}

glm::vec2 InputManager::mouseMovement()
{
	double x, y;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);

	float dx = x - lastMouseX;
	float dy = y - lastMouseX;

	lastMouseX = x;
	lastMouseX = y;

	return { dx, dy };
}