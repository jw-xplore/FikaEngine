#include "camera.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "../platform/window.h";
#include "../platform/inputs/inputdevices.h"
#include "../platform/inputs/inputhandler.h"

Camera::Camera(Window& window)
{
    this->window = &window;
    glfwSetCursorPos(window.getHandle(), window.getWidth() * 0.5f, window.getHeight() * 0.5f);

    keyboard = Input::getDefaultKeyboard();
    mouse = Input::getDefaultMouse();
}

void Camera::lookAt(glm::vec3 target)
{
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    projection = glm::lookAt(position, target, up);

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    float ratio = (float)viewport[2] / (float)viewport[3];

    projection = glm::perspective(glm::radians(fov), ratio, nearPlane, farPlane) * projection;
}

void Camera::update(float dt)
{
    // Free cam controls
    processMouse(dt);
    processKeyboard(dt);
    updateVectors();

    lookAt(position + direction);
}

void Camera::updateVectors()
{
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(direction);
    rightVec = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));
    upVec = glm::normalize(glm::cross(rightVec, front));
}

void Camera::processMouse(float dt)
{
    double centerX = window->getWidth() * 0.5f, centerY = window->getHeight() * 0.5f;
    double xpos, ypos;
    glfwGetCursorPos(window->getHandle(), &xpos, &ypos);

    double changeX = xpos - centerX;
    double changeY = ypos - centerY;

    //std::cout << "change: " << changeX << ", " << changeY << "\n";

    yaw += changeX * sensitivity * dt;
    pitch -= changeY * sensitivity * dt;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glfwSetCursorPos(window->getHandle(), centerX, centerY);
}

void Camera::processKeyboard(float dt)
{
    // Adjust speed
    if (mouse->currentYScroll > 0 && speed < maxSpeed)
        speed += speedChange;
    else if (mouse->currentYScroll < 0 && speed > minSpeed)
        speed -= speedChange;

    // Forwards - backwards
    float forward = 0;
    if (keyboard->held[Input::Key::W])
        forward = 1;
    if (keyboard->held[Input::Key::S])
        forward = -1;

    // Sides
    float right = 0;
    if (keyboard->held[Input::Key::D])
        right = 1;
    if (keyboard->held[Input::Key::A])
        right = -1;

    // Up - Down
    float up = 0;
    if (keyboard->held[Input::Key::E])
        up = 1;
    if (keyboard->held[Input::Key::Q])
        up = -1;

    // Boost
    float boost = 1;
    if (keyboard->held[Input::Key::LeftShift])
        boost = 3;

    float velocity = speed * dt * boost;
    position += front * forward * velocity;
    position += rightVec * right * velocity;
    position.y += up * velocity;
}