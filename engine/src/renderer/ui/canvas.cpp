#include "canvas.h"

namespace FikaEngine
{
	bool Canvas::removeNode(const UINode& node)
	{
		auto it = std::find_if(nodes.begin(), nodes.end(),
			[&](const auto& ptr) { return ptr.get() == &node; }
		);

		if (it == nodes.end())
			return false;

		nodes.erase(it);
		return true;
	}

	void Canvas::render()
	{
		for (const auto& node : nodes)
		{
			node->drawWindow();
		}
	}
}