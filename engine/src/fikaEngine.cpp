#include "fikaEngine.h"

namespace FikaEngine
{
	// TODO: Make possible to remove these
	MeshResource cubeMesh;
	ShaderResource basicShader;

	/// <summary>
	/// Load in all default resources like cube meshes, basic shaders, engine data, etc. 
	/// </summary>
	void setup()
	{
		cubeMesh = MeshBuilder().createCube(0.5).build();
		GResourceManager::storeMesh("cube", cubeMesh);

		basicShader = ShaderResource("assets/shaders/basic.vert", "assets/shaders/basic.frag");
		GResourceManager::storeShader("basic", basicShader);
	}

    void run(void (*startFnc)(), void (*updateFnc)(float))
    {
        Window window;
        float lastTime = 0;
        char title[64];

        if (!window.create(1280, 720, "Fika Engine"))
            return;

        setup();
        glEnable(GL_DEPTH_TEST);

        Camera mainCamera = Camera(window);

        // Custom user start and setup
        startFnc();

        // Game loop
        while (!window.shouldClose())
        {
            Input::InputHandler::beginFrame();

            // TODO: Create proper debug UI
            // Display current FPS in window title
            float now = glfwGetTime();
            float dt = now - lastTime;
            lastTime = now;

            snprintf(title, 64, "Fika Engine - %.0f", (1.0f / dt));
            glfwSetWindowTitle(glfwGetCurrentContext(), title);

            // Poll and clear
            window.poll();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Custom user update
            updateFnc(dt);

            // Base game update
            mainCamera.update(dt);
            Renderer::render(mainCamera.getProjection());

            window.swap();
        }

        window.destroy();
    }
}