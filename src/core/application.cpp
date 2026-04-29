#include "application.h"
#include <GLFW/glfw3.h>
#include "../platform/window.h";
#include "../platform/input.h"
#include "../renderer/camera.h"

void Application::run()
{
	Window window;
    InputManager inputManager;

    if (!window.create(1280, 720, "Fika Engine"))
        return;

    glEnable(GL_DEPTH_TEST);

    // Temporary cam setup
    Camera mainCamera;
    mainCamera.setPerspective(90, window.getAspect(), 0.1f, 100);
    mainCamera.updateVectors();

    float lastTime = 0;

    // Game loop
    while (!window.shouldClose())
    {
        float now = glfwGetTime();
        float dt = now - lastTime;
           lastTime = now;

        char title[64];
        snprintf(title, 64, "Fika Engine - %.0f", (1.0f / dt));
        glfwSetWindowTitle(glfwGetCurrentContext(), title);

        window.poll();

        // Temporary cam controls
        glm::vec2 mouseMove = inputManager.mouseMovement();
        mainCamera.processMouse(mouseMove.x, mouseMove.y);

        // temporary clear color
        glClearColor(0.2f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window.swap();
    }

    window.destroy();
}