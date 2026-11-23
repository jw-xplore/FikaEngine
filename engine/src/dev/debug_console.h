#pragma once
#include <string>
#include <vector>
#include <initializer_list>
#include "imgui.h"
#include "../core/event.h"

namespace FikaEngine
{
	class DebugConsole
	{
	private:
		const unsigned int ENTRIES_LIMIT = 50;
		std::vector<std::string> entries;
		float prevScroll = 1.0f;
		char command[256] = "";
		Event<void(std::string)> onCommandExecuted;

	public:
		DebugConsole();
		~DebugConsole();
		void drawConsole();
		void print(std::string text, std::initializer_list<std::string> additionalText = {});

		void addListener(std::function<void(std::string)> fnc);
	};
}