#include "ui_node.h"
#include "../../core/fika_servers.h"

namespace FikaEngine
{
	UINode::UINode()
	{
	}

	UINode::UINode(glm::vec2 position, glm::vec2 size, float rotation):
		position(position),
		size(size),
		rotation(rotation)
	{
	}

	UINode::~UINode()
	{

	}

	glm::mat3 UINode::transformMatrix()
	{
		glm::mat3 transform = glm::mat3(1.0f);

		// Size
		transform[0][0] *= size.x;
		transform[1][1] *= size.y;

		// Position
		transform[0][2] += position.x;
		transform[1][2] += position.x;

		return transform;
	}

	void UINode::draw()
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0, 0.0, 0.0, 0.5));
		ImGui::Button(".", ImVec2(size.x, size.y));
		ImGui::PopStyleColor();
	}

	void UINode::drawWindow()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f); // optional

		ImGui::SetNextWindowPos(ImVec2(position.x, position.y));
		ImGui::SetNextWindowSize(ImVec2(size.x, size.y));

		ImGui::Begin("Window", nullptr, 
			ImGuiWindowFlags_NoDecoration |
			ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoSavedSettings);

		draw();

		ImGui::End();

		ImGui::PopStyleVar(2);
	}
}