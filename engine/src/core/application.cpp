#include "application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../platform/window.h";
#include "../renderer/camera.h"
#include "../renderer/renderer.h"
#include "../renderer/resources/gResourceManager.h"
#include "../renderer/resources/meshBuilder.h"
#include "../renderer/resources/meshInstance.h"
#include "../platform/inputs/inputhandler.h"
#include <glm/ext/matrix_transform.hpp>

MeshResource cubeMesh;
ShaderResource basicShader;

Application::Application(void (*startFnc)(), void (*updateFnc)(float))
{
    this->startFnc = startFnc;
    this->updateFnc = updateFnc;
}

Application::~Application()
{

}

void Application::setup()
{
    cubeMesh = MeshBuilder().createCube(0.5).build();
    GResourceManager::storeMesh("cube", cubeMesh);

    basicShader = ShaderResource("assets/shaders/basic.vert", "assets/shaders/basic.frag");
    GResourceManager::storeShader("basic", basicShader);
}

void Application::run()
{
	Window window;
    float lastTime = 0;
    char title[64];

    if (!window.create(1280, 720, "Fika Engine"))
        return;

    setup();
    glEnable(GL_DEPTH_TEST);

    Camera mainCamera = Camera(window);

    startFnc();

    // Game loop
    while (!window.shouldClose())
    {
        Input::InputHandler::beginFrame();

        float now = glfwGetTime();
        float dt = now - lastTime;
           lastTime = now;

        snprintf(title, 64, "Fika Engine - %.0f", (1.0f / dt));
        glfwSetWindowTitle(glfwGetCurrentContext(), title);

        window.poll();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Base game update
        mainCamera.update(dt);
        Renderer::render(mainCamera.getProjection());
        updateFnc(dt);

        window.swap();
    }

    window.destroy();
}