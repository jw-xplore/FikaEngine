#pragma once
#include "ui_node.h"
#include <vector>
#include <memory>

namespace FikaEngine
{
	class Canvas
	{
	private:
		std::vector<std::unique_ptr<UINode>> nodes;

	public:
		template <typename T>
		T& addNode()
		{
			auto node = std::make_unique<T>();
			T& result = *node;
			nodes.push_back(std::move(node));
			return result;
		}

		bool removeNode(const UINode& node);

		void render();
	};
}