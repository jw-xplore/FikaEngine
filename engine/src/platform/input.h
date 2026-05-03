#pragma once
#include <glm/glm.hpp>

class InputManager
{
private:
	float lastMouseX, lastMouseY;

public:
	InputManager();
	glm::vec2 mouseMovement();
};