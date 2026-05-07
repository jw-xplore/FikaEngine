#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window;

namespace Input
{
    struct Keyboard;
    struct Mouse;
}

class Camera
{
public:
    Camera() {}
    Camera(Window& window);

	void updateVectors();

    void lookAt(glm::vec3 target);
    void update(float dt);
	void processMouse(float dt);
	void processKeyboard(float dt);

    glm::mat4 getProjection() { return projection; }

	glm::vec3 position{ 0, 0, -5 };

private:
    Window* window;
    Input::Keyboard* keyboard;
    Input::Mouse* mouse;

    float yaw = 90;
    float pitch = 0;

    float speed = 5.0f;
    float minSpeed = 1.0f, maxSpeed = 20.0f, speedChange = 1.0f;
    float sensitivity = 10.1f;

    glm::vec3 rotation;

    float fov = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    glm::vec3 direction = { 0, 0, 1};
    glm::vec3 front{ 0,0,-1 };
    glm::vec3 rightVec{ 1,0,0 };
    glm::vec3 upVec{ 0,1,0 };

    glm::mat4 projection;
    bool freeControls = true;
};