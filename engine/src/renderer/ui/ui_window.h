#pragma once
#include "ui_node.h"
#include "core/event.h"

namespace FikaEngine
{
	class UIWindow : public UINode
	{
	private:
		std::vector<UINode> nodes;

	public:
		UIWindow() {}
		~UIWindow() {}

		void draw() override;
	};
}