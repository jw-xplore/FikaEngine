#include "fika_engine.h"

namespace FikaEngine
{
    /**
     * @brief Load in all default resources like cube meshes, basic shaders, engine data, etc. 
     */
    void Game::setup()
	{
        // Systems
        FikaServers* systemsHolder = FikaServers::getInstance();
        systemsHolder->init();

        // Setup and load basic resources
        FikaServers::getGResourceManager().init();

        FikaServers::getMainRenderer().init();
        FikaServers::getDebugRenderer().init();

        // Meshes
        MeshResource* cubeMesh = FikaServers::getGResourceManager().reserveMesh("cube");
        MeshBuilder().createCube(1).build(*cubeMesh);

        MeshResource* sphereMesh = FikaServers::getGResourceManager().reserveMesh("sphere");
        MeshBuilder().loadMesh("assets/common/models/sphere.obj").build(*sphereMesh);

        MeshResource* cylinderMesh = FikaServers::getGResourceManager().reserveMesh("cylinder");
        MeshBuilder().loadMesh("assets/common/models/cylinder.obj").build(*cylinderMesh);

        // Shaders
        ShaderResource basicShader = ShaderResource("assets/common/shaders/basic.vert", "assets/common/shaders/basic.frag");
        FikaServers::getGResourceManager().storeShader("basic", basicShader);

        // Keyboard
        m_Keyboard = Input::getDefaultKeyboard();
	}

    void Game::debugUI(GLFWwindow* window)
    {
        // TODO: Cleanup and make into general purpose
        ImGuiIO& io = ImGui::GetIO();
        int fb_w = 0, fb_h = 0;
        glfwGetFramebufferSize(window, &fb_w, &fb_h);
        if (fb_w > 0 && fb_h > 0) {
            io.DisplaySize = ImVec2(static_cast<float>(fb_w), static_cast<float>(fb_h));

            int win_w = 0, win_h = 0;
            glfwGetWindowSize(window, &win_w, &win_h);
            io.DisplayFramebufferScale = ImVec2(
                win_w > 0 ? static_cast<float>(fb_w) / static_cast<float>(win_w) : 1.0f,
                win_h > 0 ? static_cast<float>(fb_h) / static_cast<float>(win_h) : 1.0f
            );
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        
        ImGui::Begin("Debug");
        int fps = 1.0f / m_DeltaTime;
        std::string strFps = "FPS: " + std::to_string(fps);
        ImGui::Text(strFps.c_str());
        ImGui::Checkbox("V-Sync", &m_EnableVSync);
        ImGui::End();
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Game::run(void (*startFnc)(), void (*updateFnc)(float))
    {
        Window window;
        float lastTime = 0;

        if (!window.create(1280, 720, "Fika Engine"))
            return;

        setup();
        glEnable(GL_DEPTH_TEST);

        // Setup cameras
        FikaServers::getCameraManager().init(window);
        Camera* mainCamera = FikaServers::getCameraManager().getMainCamera();

        // Custom user start and setup
        startFnc();

        // ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window.getHandle(), true);
        ImGui_ImplOpenGL3_Init("#version 330");

        // Game loop
        while (!window.shouldClose())
        {
            Input::InputHandler::beginFrame();

            // TODO: Create proper debug UI
            // Display current FPS in window title
            float now = glfwGetTime();
            float dt = now - lastTime;
            if (dt > 1.0)
                dt = m_DeltaTime;

            m_DeltaTime = dt;
            lastTime = now;

            // V-Sync
            glfwSwapInterval(m_EnableVSync);

            // Poll and clear
            window.poll();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Custom user update
            updateFnc(dt);

            // Free cam update
            if (m_Keyboard->pressed[Input::Key::P])
            {
                FikaServers::getCameraManager().useFreeCamera(!FikaServers::getCameraManager().isUsingFreeCamera());
                mainCamera = FikaServers::getCameraManager().getActiveCamera();
            }

            if (FikaServers::getCameraManager().isUsingFreeCamera())
                FikaServers::getCameraManager().getFreeCamera()->flycamUpdate(dt);

            // Base game update
            FikaServers::getECSManager().update(dt);
            FikaServers::getPhysicsSolver().update(dt);
            FikaServers::getMainRenderer().render(mainCamera->getProjection());

            // Debug
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            FikaServers::getDebugRenderer().render(mainCamera->getProjection());
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            debugUI(window.getHandle());

            window.swap();
        }

        window.destroy();
    }

    float Game::getDeltaTime() { return m_DeltaTime; }
}