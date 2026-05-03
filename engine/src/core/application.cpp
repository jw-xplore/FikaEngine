#include "application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../platform/window.h";
#include "../platform/input.h"
#include "../renderer/camera.h"
#include "../renderer/resources/gResourceManager.h"
#include "../renderer/resources/meshBuilder.h"
#include "../renderer/resources/meshInstance.h"
#include "../renderer/camera.h"

MeshInstance* testPlane;

void Application::run()
{
	Window window;
    InputManager inputManager;

    if (!window.create(1280, 720, "Fika Engine"))
        return;

    glEnable(GL_DEPTH_TEST);

    // Temporary cam setup
    Camera mainCamera = Camera(window);
    //mainCamera.setPerspective(90, window.getAspect(), 0.1f, 100);
    //mainCamera.updateVectors();

    float lastTime = 0;

    // Test mesh
    MeshResource planeMesh = MeshBuilder().createCube(0.5).build();
    ShaderResource basicShader;
    basicShader.loadShaders("assets/shaders/basic.vert", "assets/shaders/basic.frag");
    basicShader.compile();

    testPlane = new MeshInstance();
    testPlane->setMesh("plane", &planeMesh);
    testPlane->setShader("basic", &basicShader);

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
        mainCamera.update(dt);

        // temporary clear color
        //glClearColor(0.2f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainCamera.update(dt);
        testPlane->draw(mainCamera.getProjection());

        window.swap();
    }

    window.destroy();
}