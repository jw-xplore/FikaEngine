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

MeshInstance* testPlane;

void Application::run()
{
	Window window;
    //InputManager inputManager;

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

    //testPlane = new MeshInstance();
    //testPlane->setMesh("plane", &planeMesh);
    //testPlane->setShader("basic", &basicShader);

    Renderer::addMeshInstance(planeMesh, basicShader);
    MeshInstance* mi1 = Renderer::addMeshInstance(planeMesh, basicShader);
    mi1->transform = glm::translate(mi1->transform, glm::vec3(0,1,0));

    char title[64];

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

        mainCamera.update(dt);
        Renderer::render(mainCamera.getProjection());
        //testPlane->draw(mainCamera.getProjection());

        window.swap();
    }

    window.destroy();
}