#include "editor.h"
#include <fstream>
#include <iostream>
#include <windows.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "fikaEngine.h"

namespace FikaEditor
{
    void Editor::debugUI(GLFWwindow* window)
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

        ImGui::Begin("Fika Editor");
        ImGui::InputText("Directory", workingDirectory, 256);
        ImGui::InputText("Executable", executable, 256);

        // Run game
        if (ImGui::Button("Run"))
        {
            runGame();
        }

        // Save level
        ImGui::InputText("Level path", levelPath, 256);

        if (ImGui::Button("Save"))
        {
            //SystemsHolder::getGameObjectManager()->serialize(levelPath);
        }

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Editor::update()
    {
        // UI
        debugUI(glfwGetCurrentContext());

        // Placing
        Input::Mouse* mouse = Input::getDefaultMouse();

        if (mouse->pressed[Input::Mouse::RightButton])
        {
            glm::vec3 pos = positionFromScreenSpace(glm::vec2(0,0));
            if (pos == glm::vec3(-1))
                return;

            placeObject(pos);
        }
    }

    bool Editor::loadProject()
    {
        std::string path = workingDirectory;
        path += "assets/textures/pawn.jpg";

        // Read file
        try
        {
            std::cout << "File found: " << path << "\n";
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "Failed to load: " << path << "\n";
            return false;
        }

        return true;
    }

	void Editor::runGame()
	{
        STARTUPINFOA startupInfo{};
        PROCESS_INFORMATION processInfo{};

        startupInfo.cb = sizeof(startupInfo);

        // The command line buffer must be writable.
        char commandLine[128];
        std::string project = workingDirectory;
        project += executable;

        strcpy(commandLine, project.c_str());

        BOOL success = CreateProcessA(
            nullptr,          // Application name
            commandLine,      // Command line
            nullptr,          // Process security attributes
            nullptr,          // Thread security attributes
            FALSE,            // Inherit handles
            0,                // Creation flags
            nullptr,          // Environment
            workingDirectory,      // Working directory
            &startupInfo,
            &processInfo
        );

        if (!success) {
            std::cerr << "Failed to start program. Error: " << GetLastError() << '\n';
            return;
        }

        std::cout << "Program started.\n";

        // Optional: wait until the program exits
        // WaitForSingleObject(processInfo.hProcess, INFINITE);

        CloseHandle(processInfo.hThread);
        CloseHandle(processInfo.hProcess);
	}

    glm::vec3 Editor::positionFromScreenSpace(glm::vec2 position)
    {
        CameraManager* cameraManager = SystemsHolder::getCameraManager();
        Camera* cam = cameraManager->getActiveCamera();

        glm::vec3 pos = cam->getPosition();
        glm::vec3 dir = cam->getDirection();

        float t = -pos.y / dir.y;
        if (t < 0)
            return glm::vec3(-1);

        return pos + t * dir;
    }

    void Editor::placeObject(glm::vec3 position)
    {
        GResourceManager* gResourceManager = SystemsHolder::getGResourceManager();
        ShaderResource& basicShader = gResourceManager->getShader("basic");
        MeshResource& customMesh = gResourceManager->getMesh("cube");

        FikaECS::Entity* entity = SystemsHolder::getECSManager()->addEntity();

        TransformComponent* transform = dynamic_cast<TransformComponent*>(SystemsHolder::getECSManager()->addComponent(entity, TransformComponent::componentId));
        transform->getTransform()->setPosition(position);

        MeshComponent* meshCmp = dynamic_cast<MeshComponent*>(SystemsHolder::getECSManager()->addComponent(entity, MeshComponent::componentId));
        meshCmp->setup(customMesh, basicShader, nullptr);
    }
}