#include "editor_gui.h"

namespace FikaEditor
{
    void EditorGUI::projectPanel()
    {
        // TODO
    }

    void EditorGUI::entitiesList()
    {
        // TODO
    }

    void EditorGUI::entityInspector(Entity* entity)
    {
        cursorHover = false;

        // No entity selected
        if (entity == nullptr)
        {
            return;
        }

        ImGui::SetNextWindowPos(ImVec2(400, 20), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(200, 200));

        std::string title = entityDisplayName(*entity);
        ImGui::Begin(title.c_str());

        // Content

        // Transform
        Transform* transform = FikaServers::getECSManager().findEntityTransform(*entity);
        
        // Position
        ImGui::Text("Position");

        glm::vec3 position = transform->getLocalPosition();
        ImGui::InputFloat("pX", &position.x);
        ImGui::InputFloat("pY", &position.y);
        ImGui::InputFloat("pZ", &position.z);

        transform->setPosition(position);

        // Rotation
        ImGui::Text("Rotation");

        glm::vec3 rotation = transform->getLocalRotation();
        ImGui::InputFloat("rX", &rotation.x);
        ImGui::InputFloat("rY", &rotation.y);
        ImGui::InputFloat("rZ", &rotation.z);

        transform->setRotation(rotation);

        // Scale
        ImGui::Text("Scale");

        glm::vec3 scale = transform->getLocalScale();
        ImGui::InputFloat("sX", &scale.x);
        ImGui::InputFloat("sY", &scale.y);
        ImGui::InputFloat("sZ", &scale.z);

        transform->setScale(scale);

        // Content end

        // Hover check 
        if (ImGui::IsWindowHovered() || ImGui::IsWindowFocused())
        {
            cursorHover = true;
        }

        ImGui::End();
    }

    std::string EditorGUI::entityDisplayName(Entity& entity)
    {
        std::string name = entity.getName();
        if (name == "")
        {
            name = "Entity";
        }

        return name + "(" + std::to_string(entity.getId()) + ")";
    }
}