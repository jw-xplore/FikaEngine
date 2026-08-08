#include "fikaEngine.h"

namespace FikaEngine
{
    float deltaTime = 1;
    Input::Keyboard* keyboard;

    Renderer* renderer;
    Renderer* debugRenderer;
    PhysicsSolver* physicsSolver;
    GameObjectManager* gameObjectManager;
    CameraManager* cameraManager;
    GResourceManager* gResourceManager;

    /**
     * @brief Load in all default resources like cube meshes, basic shaders, engine data, etc. 
     */
    void setup()
	{
        // Systems
        SystemsHolder* systemsHolder = SystemsHolder::getInstance();
        renderer = systemsHolder->getMainRenderer();
        debugRenderer = systemsHolder->getDebugRenderer();
        physicsSolver = systemsHolder->getMainPhysicsSolver();
        gameObjectManager = systemsHolder->getGameObjectManager();
        cameraManager = systemsHolder->getCameraManager();
        gResourceManager = systemsHolder->getGResourceManager();

        // Setup and load basic resources
        gResourceManager->init();

        // Meshes
        MeshResource* cubeMesh = gResourceManager->reserveMesh("cube");
        MeshBuilder().createCube(1).build(*cubeMesh);

        MeshResource* sphereMesh = gResourceManager->reserveMesh("sphere");
        MeshBuilder().loadMesh("assets/common/models/sphere.obj").build(*sphereMesh);

        MeshResource* cylinderMesh = gResourceManager->reserveMesh("cylinder");
        MeshBuilder().loadMesh("assets/common/models/cylinder.obj").build(*cylinderMesh);

        // Shaders
        ShaderResource basicShader = ShaderResource("assets/common/shaders/basic.vert", "assets/common/shaders/basic.frag");
		gResourceManager->storeShader("basic", basicShader);

        // Keyboard
        keyboard = Input::getDefaultKeyboard();
	}

    void debugUI(GLFWwindow* window)
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
        int fps = 1.0f / deltaTime;
        std::string strFps = "FPS: " + std::to_string(fps);
        ImGui::Text(strFps.c_str());
        ImGui::End();
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void run(void (*startFnc)(), void (*updateFnc)(float))
    {
        Window window;
        float lastTime = 0;

        if (!window.create(1280, 720, "Fika Engine"))
            return;

        setup();
        glEnable(GL_DEPTH_TEST);
        //glfwSwapInterval(0); // Disable v-sync for testing

        // Setup cameras
        cameraManager->init(window);
        Camera* mainCamera = cameraManager->getMainCamera();

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
            deltaTime = dt;
            lastTime = now;

            // Poll and clear
            window.poll();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Custom user update
            updateFnc(dt);

            // Free cam update
            if (keyboard->pressed[Input::Key::P])
            {
                cameraManager->useFreeCamera(!cameraManager->isUsingFreeCamera());
                mainCamera = cameraManager->getActiveCamera();
            }

            if (cameraManager->isUsingFreeCamera())
                cameraManager->getFreeCamera()->flycamUpdate(dt);

            // Base game update
            gameObjectManager->update(dt);
            physicsSolver->update(dt);
            renderer->render(mainCamera->getProjection());

            // Debug
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            debugRenderer->render(mainCamera->getProjection());
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            debugUI(window.getHandle());

            window.swap();
        }

        window.destroy();
    }

    float getDeltaTime() { return deltaTime; }

    GameObject* addGameObject() { return gameObjectManager->addGameObject(); }
}