#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

void Camera::setPerspective(float fov, float aspect, float nearPlane, float farPlane)
{
    projection = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return projection;
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + front, upVec);
}

void Camera::updateVectors()
{
    glm::vec3 f;

    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(f);
    rightVec = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));
    upVec = glm::normalize(glm::cross(rightVec, front));
}

void Camera::processMouse(float dx, float dy)
{
    yaw += dx * sensitivity;
    pitch -= dy * sensitivity;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateVectors();
}

void Camera::processKeyboard(float forward, float right, float dt)
{
    float velocity = speed * dt;
    position += front * forward * velocity;
    position += rightVec * right * velocity;
}