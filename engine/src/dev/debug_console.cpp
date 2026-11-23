#include "debug_console.h"
#include <iostream>
#include "../core/fika_servers.h"

namespace FikaEngine
{
	DebugConsole::DebugConsole()
	{
		entries.reserve(ENTRIES_LIMIT);
	}

	DebugConsole::~DebugConsole()
	{

	}

	void DebugConsole::drawConsole()
	{
		ImGui::SetNextWindowPos(ImVec2(20, 400));
		ImGui::SetNextWindowSize(ImVec2(400, 300));

		// Output
		ImGui::Begin("Output");

		// Texte
		std::string consoleText = "";

		for (std::string entry : entries)
		{
			consoleText += entry + "\n";
		}

		ImGui::Text(consoleText.c_str());

		// Scroll
		if (prevScroll <= ImGui::GetScrollMaxY())
		{
			ImGui::SetScrollHereY(1.0f);
		}

		prevScroll = ImGui::GetScrollY();

		ImGui::End();

		// Commands
		ImGui::SetNextWindowPos(ImVec2(20, 400 + 300));
		ImGui::SetNextWindowSize(ImVec2(400, 50));

		ImGui::Begin("Commands");
		ImGui::InputText("cmd", command, 256);

		if (ImGui::IsWindowFocused())
		{
			// Confirm
			if (FikaServers::getInputManager().isKeyPressed(Key::Return))
			{
				onCommandExecuted.broadcast(command);
			}
		}

		ImGui::End();
	}

	void DebugConsole::print(std::string text, std::initializer_list<std::string> additionalText)
	{
		std::string mergedString = text;

		for (auto txt : additionalText)
		{
			mergedString += txt;
		}

		if (entries.size() < ENTRIES_LIMIT)
		{
			entries.push_back(mergedString);
		}
		else
		{
			entries.erase(entries.begin());
			entries.push_back(mergedString);
		}

		std::cout << mergedString << "\n";
	}

	void DebugConsole::addListener(std::function<void(std::string)> fnc)
	{
		onCommandExecuted.addListener(fnc);
	}
}