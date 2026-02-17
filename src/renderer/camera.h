#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	void setPerspective(float fov, float aspect, float nearPlane, float farPlane);
	void updateVectors();

	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;

	void processMouse(float dx, float dy);
	void processKeyboard(float forward, float right, float deltaTime);

	glm::vec3 position{ 0.0f, 1.6f, 3.0f };

private:
    float yaw = -90.0f;
    float pitch = 0.0f;

    float speed = 5.0f;
    float sensitivity = 0.1f;

    glm::vec3 front{ 0,0,-1 };
    glm::vec3 rightVec{ 1,0,0 };
    glm::vec3 upVec{ 0,1,0 };

    glm::mat4 projection;
    bool freeControls = true;
};