#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../resources/mesh_instance.h"
#include "../../external/imgui/imgui.h"
#include "../../external/imgui/imgui_impl_glfw.h"
#include "../../external/imgui/imgui_impl_opengl3.h"

namespace FikaEngine
{
	class UINode
	{
	protected:
		MeshInstance mesh;

		glm::vec2 position = glm::vec2(0.0f);
		glm::vec2 size = glm::vec2(100.0f, 50.0f);
		float rotation = 0.0f;

	public:
		UINode();
		UINode(glm::vec2 position, glm::vec2 size, float rotation);
		~UINode();

		void setPosition(const glm::vec2& position) { this->position = position; }
		void setSize(const glm::vec2& size) { this->size = size; }
		void setRotation(const float& rotation) { this->rotation = rotation; }

		MeshInstance& getMeshInstance() { return mesh; }

		glm::mat3 transformMatrix();
		virtual void draw() {}
		void drawWindow();
	};
}