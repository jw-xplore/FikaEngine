#include "fikaEngine.h"

namespace FikaEngine
{
    float deltaTime = 1;
    Input::Keyboard* keyboard;

    /**
     * @brief Load in all default resources like cube meshes, basic shaders, engine data, etc. 
     */
    void setup()
	{
        // Setup and load basic resources
        GResourceManager::init();

        MeshResource* cubeMesh = GResourceManager::reserveMesh("cube");
        MeshBuilder().createCube(0.5).build(*cubeMesh);

        ShaderResource basicShader = ShaderResource("assets/common/shaders/basic.vert", "assets/common/shaders/basic.frag");
		GResourceManager::storeShader("basic", basicShader);

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

        // Setup cameras
        CameraManager::init(window);
        Camera* mainCamera = CameraManager::getActiveCamera();
        mainCamera->move(glm::vec3(0), glm::vec3(0, 0, 1));

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
                CameraManager::useFreeCamera(!CameraManager::isUsingFreeCamera());
                mainCamera = CameraManager::getActiveCamera();
            }

            if (CameraManager::isUsingFreeCamera())
                CameraManager::getFreeCamera()->flycamUpdate(dt);

            // Base game update
            GameObjectManager::update(dt);
            Renderer::render(mainCamera->getProjection());
            debugUI(window.getHandle());

            window.swap();
        }

        window.destroy();
    }
}