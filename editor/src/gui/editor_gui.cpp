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
        ImGui::SetNextWindowSize(ImVec2(400, 200));

        std::string title = entityDisplayName(*entity);
        ImGui::Begin(title.c_str());

        // Content

        // Transform
        Transform* transform = FikaServers::getECSManager().findEntityTransform(*entity);
        
        // Position
        ImGui::Text("Position");

        glm::vec3 position = transform->getLocalPosition();
        ImGui::PushItemWidth(100);
        ImGui::InputFloat("pX", &position.x, 0.1f);
        ImGui::SameLine();
        ImGui::InputFloat("pY", &position.y, 0.1f);
        ImGui::SameLine();
        ImGui::InputFloat("pZ", &position.z, 0.1f);

        transform->setPosition(position);

        // Rotation
        ImGui::Text("Rotation");

        glm::vec3 rotation = transform->getLocalRotation();
        ImGui::InputFloat("rX", &rotation.x, 1.0f);
        ImGui::SameLine();
        ImGui::InputFloat("rY", &rotation.y, 1.0f);
        ImGui::SameLine();
        ImGui::InputFloat("rZ", &rotation.z, 1.0f);

        transform->setRotation(rotation);

        // Scale
        ImGui::Text("Scale");

        std::string scaleLockText = "SLock";
        if (consistentScaling)
        {
            scaleLockText = "SUnlock";
        }

        ImGui::SameLine();
 
        if (ImGui::Button(scaleLockText.c_str()))
        {
            consistentScaling = !consistentScaling;
        }

        glm::vec3 scale = transform->getLocalScale();
        if (ImGui::InputFloat("sX", &scale.x, 0.1f))
        {
            if (consistentScaling)
            {
                scale.y = scale.x;
                scale.z = scale.x;
            }
        }

        ImGui::SameLine();
        if (ImGui::InputFloat("sY", &scale.y, 0.1f))
        {
            if (consistentScaling)
            {
                scale.x = scale.y;
                scale.z = scale.y;
            }
        }

        ImGui::SameLine();
        if (ImGui::InputFloat("sZ", &scale.z, 0.1f))
        {
            if (consistentScaling)
            {
                scale.x = scale.z;
                scale.y = scale.z;
            }
        }

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