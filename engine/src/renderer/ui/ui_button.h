#pragma once
#include "ui_node.h"
#include "core/event.h"

namespace FikaEngine
{
	class UIButton : public UINode
	{
	public:
		Event<void(UIButton& button)> onButtonClick;

		UIButton() {}
		~UIButton() {}

		void draw() override;
	};
}