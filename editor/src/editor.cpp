#include "editor.h"
#include <fstream>
#include <iostream>
#include <windows.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "core/fika_servers.h"
#include "core/game_resource_manager.h"
#include "platform/inputs/input_devices.h"
#include "platform/inputs/input_handler.h"

#include "fika_engine.h"

namespace FikaEditor
{
    Editor::Editor()
    {

    }

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
        ImGui::InputText("Prefabs", projectPrefabPath, 256);

        // Run game
        if (ImGui::Button("Run"))
        {
            runGame();
        }

        // Save level
        ImGui::InputText("Level path", levelPath, 256);

        if (ImGui::Button("Save"))
        {
            saveLevel(levelPath);
            //FikaServers::getGameObjectManager()->serialize(levelPath);
            //nlohmann::json level = FikaServers::getECSManager().serializeEditorEntities();
        }

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Editor::update()
    {
        // UI
        selectPrefab();
        debugUI(glfwGetCurrentContext());

        glm::vec3 pos = positionFromScreenSpace(glm::vec2(0, 0));
        placingTransform[3] = glm::vec4(pos.x, pos.y, pos.z, 1);
        //glm::translate(placingTransform, pos);

        // Placing
        Input::Mouse* mouse = Input::getDefaultMouse();

        if (mouse->pressed[Input::Mouse::RightButton])
        {
            if (pos == glm::vec3(-1))
                return;

            placeObject(pos);
        }
    }

    bool Editor::loadProject()
    {
        GResourceManager& gResMgnr = FikaServers::getGResourceManager();
        FikaServers::getMainRenderer().addMeshInstance(&placingTransform, gResMgnr.getMesh("cube"), gResMgnr.getShader("basic"));

        loadActivePrefab();

        return true;
    }

    void Editor::loadActivePrefab()
    {
        if (!activePrefab)
            activePrefab = new Prefab();

        //FikaServers::getGameResourceManager()->loadPrefab(activePrefabPath, *activePrefab);

        // Load prefabs
        FikaServers::getGameResourceManager().loadFolderPrefabs(projectPrefabPath);
        projectPrefabs = FikaServers::getGameResourceManager().getLoadedPrefabsList();

        activePrefab = projectPrefabs[0];
    }

    void Editor::saveLevel(const char* path)
    {
        nlohmann::json level = FikaServers::getECSManager().serializeEditorEntities();

        std::ofstream file(path);

        if (!file.is_open())
        {
            std::cout << "Can't serialize game objects as levels folder/file is not found \n";
            return;
        }

        file << std::setw(4) << level;
        file.close();
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
        CameraManager& cameraManager = FikaServers::getCameraManager();
        Camera* cam = cameraManager.getActiveCamera();

        glm::vec3 pos = cam->getPosition();
        glm::vec3 dir = cam->getDirection();

        float t = -pos.y / dir.y;
        if (t < 0)
            return glm::vec3(-1);

        // Target rounding
        glm::vec3 target = pos + t * dir;
        target.x = roundf(target.x * 2) / 2;
        target.y = roundf(target.y * 2) / 2;
        target.z = roundf(target.z * 2) / 2;

        return target;
    }

    void Editor::placeObject(glm::vec3 position)
    {
        GResourceManager& gResourceManager = FikaServers::getGResourceManager();
        ShaderResource& basicShader = gResourceManager.getShader("basic");
        //MeshResource& customMesh = gResourceManager->getMesh("cube");

        Entity* entity = FikaServers::getECSManager().addEntity();
        entity->setSourcePrefab(activePrefab);

        TransformComponent* transform = dynamic_cast<TransformComponent*>(FikaServers::getECSManager().addComponent(entity, TransformComponent::componentId));
        transform->getTransform()->setPosition(position);

        // Translate mesh instance 
        nlohmann::json meshCmpJson = meshJsonFromPrefab(*activePrefab);

        std::string meshPath = meshCmpJson["meshPath"];
        assert(meshPath != "");
        meshPath = workingDirectory + meshPath;
        MeshResource* meshRes = gResourceManager.reserveMesh(activePrefab->name.c_str());
        MeshBuilder().loadMesh(meshPath.c_str()).build(*meshRes);
        //MeshResource* meshRes = gResourceManager->loadMesh(meshPath.c_str(), activePrefab->name.c_str());

        std::string texturePath = meshCmpJson["texturePath"];
        assert(texturePath != "");
        texturePath = workingDirectory + texturePath;
        TextureResource* textureRes = gResourceManager.loadTexture(texturePath.c_str(), activePrefab->name.c_str());

        MeshComponent* meshCmp = dynamic_cast<MeshComponent*>(FikaServers::getECSManager().addComponent(entity, MeshComponent::componentId));
        meshCmp->setup(*meshRes, basicShader, nullptr);
        meshCmp->setTexture(*textureRes);
    }

    nlohmann::json Editor::meshJsonFromPrefab(Prefab& prefab)
    {
        nlohmann::json entityJson = activePrefab->data["entity"];
        nlohmann::json componentJson = entityJson["components"];

        for (auto& jsComp : componentJson.items())
        {
            unsigned int id = jsComp.value()["id"];
            if (id == MeshComponent::componentId)
                return jsComp.value();
        }

        return "";
    }

    void Editor::selectPrefab()
    {
        Input::Keyboard* keyboard = Input::getDefaultKeyboard();

        if (keyboard->held[Input::Key::Key1])
            activePrefab = projectPrefabs[0];
        if (keyboard->held[Input::Key::Key2])
            activePrefab = projectPrefabs[1];
    }
}