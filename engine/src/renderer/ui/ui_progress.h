#pragma once
#include "ui_node.h"
#include "core/event.h"

namespace FikaEngine
{
	class UIProgress : public UINode
	{
	private:
		float currentProgress = 1.0f;
		float maxProgress = 1.0f;

	public:
		UIProgress() {}
		~UIProgress() {}

		void draw() override;
	};
}