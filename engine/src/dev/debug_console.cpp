#include "debug_console.h"
#include <iostream>

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

	ImGui::Begin("Console");

	// Text
	ImGui::Text(consoleText.c_str());

	if (prevScroll <= ImGui::GetScrollMaxY())
	{
		ImGui::SetScrollHereY(1.0f);
	}

	prevScroll = ImGui::GetScrollY();

	// TODO: Commands

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