#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <windows.h>

#include <fika_engine.h>

using namespace FikaEngine;

namespace FikaEditor
{
	class EditorGUI
	{
	private:
		bool cursorHover = false;

		void projectPanel();
		void entitiesList();

	public:
		bool getCursorHover() { return cursorHover; }
		void entityInspector(Entity* entity);
		static std::string entityDisplayName(Entity& entity);
	};
}