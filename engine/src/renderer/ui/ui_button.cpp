#include "ui_button.h"

namespace FikaEngine
{
	void UIButton::draw()
	{
		//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0, 0.0, 0.0, 0.5));

		if (ImGui::Button(".", ImVec2(size.x, size.y)))
		{
			onButtonClick.broadcast(*this);
		}
		
		//ImGui::PopStyleColor();
	}
}