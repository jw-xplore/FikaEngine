#include "ui_progress.h"

namespace FikaEngine
{
	void UIProgress::draw()
	{
		float fraction = currentProgress / maxProgress;
		ImGui::ProgressBar(fraction, ImVec2(size.x, size.y));
	}
}