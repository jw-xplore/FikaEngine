#include "ui_window.h"

namespace FikaEngine
{
	void UIWindow::draw()
	{
		for (UINode& node : nodes)
		{
			node.draw();
		}
	}
}