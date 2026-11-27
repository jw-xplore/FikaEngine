#pragma once
#include "ui_node.h"
#include "core/event.h"

namespace FikaEngine
{
	class UILabel : public UINode
	{
	public:
		UILabel() {}
		~UILabel() {}

		void draw() override;
	};
}