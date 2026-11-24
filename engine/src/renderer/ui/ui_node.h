#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../resources/mesh_instance.h"

namespace FikaEngine
{
	class UINode
	{
	private:
		MeshInstance mesh;

		glm::vec2 position = glm::vec2(0.0f);
		glm::vec2 size = glm::vec2(0.0f);
		float rotation = 0.0f;

		void createMesh();

	public:
		UINode();
		UINode(glm::vec2 position, glm::vec2 size, float rotation);
		~UINode();
	};
}