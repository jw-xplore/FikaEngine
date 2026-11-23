#include "debug_console.h"
#include <iostream>
#include "../core/fika_servers.h"

namespace FikaEngine
{
	DebugConsole::DebugConsole()
	{

	}

	DebugConsole::~DebugConsole()
	{

	}

	void DebugConsole::drawConsole()
	{
		ImGui::SetNextWindowPos(ImVec2(20, 400));
		ImGui::SetNextWindowSize(ImVec2(400, 300));

		// Text
		ImGui::Begin("Output");

		ImGui::Text(consoleText.c_str());

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

		//entries.push_back(mergedString);
		consoleText += mergedString + "\n";
		std::cout << mergedString << "\n";
	}

	void DebugConsole::addListener(std::function<void(std::string)> fnc)
	{
		onCommandExecuted.addListener(fnc);
	}
}