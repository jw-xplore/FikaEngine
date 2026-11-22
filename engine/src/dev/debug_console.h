#pragma once
#include <string>
#include <vector>
#include <initializer_list>
#include "imgui.h"

class DebugConsole
{
private:
	const unsigned int ENTRIES_LIMIT = 50;
	//std::vector<std::string> entries;
	std::string consoleText = "";
	float prevScroll = 1.0f;

public:
	DebugConsole();
	~DebugConsole();
	void drawConsole();
	void print(std::string text, std::initializer_list<std::string> additionalText = {});
};