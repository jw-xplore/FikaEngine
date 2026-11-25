#include "ui_node.h"
#include "../../core/fika_servers.h"

namespace FikaEngine
{
	UINode::UINode()
	{
		//createMesh();
	}

	UINode::UINode(glm::vec2 position, glm::vec2 size, float rotation):
		position(position),
		size(size),
		rotation(rotation)
	{
		//createMesh();
	}

	UINode::~UINode()
	{

	}

	glm::mat3 UINode::transformMatrix()
	{
		glm::mat3 transform = glm::mat3(1.0f);

		// Size
		transform[0][0] *= size.x;
		transform[1][1] *= size.y;

		// Position
		transform[0][2] += position.x;
		transform[1][2] += position.x;

		return transform;
	}

	void UINode::draw()
	{
		MeshResource* meshRes = mesh.getMesh();
		ShaderResource* shader = mesh.gettShader();

		shader->use();

		int width, height;
		glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
		shader->setUniform("screenSize", glm::vec2(width, height));

		shader->setUniform("size", size);
		shader->setUniform("position", position);

		// VOA
		glBindVertexArray(meshRes->VOA);

		// Texture
		float useTexture = 0;
		/*
		if (texture)
		{
			useTexture = 1;

			if (texture->texture)
			{
				glBindTexture(GL_TEXTURE_2D, texture->texture);
			}
		}
		*/

		//shader->setUniform("useTexture", useTexture);

		glDrawElements(GL_TRIANGLES, meshRes->indicesCount, GL_UNSIGNED_INT, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);

		glUseProgram(0);
	}

	void UINode::initMesh()
	{
		mesh.setMesh(&FikaServers::getGPUResourceManager().getMesh(GPUResourceManager::MESH_RECTANGLE));
		mesh.setShader(&FikaServers::getGPUResourceManager().getShader(GPUResourceManager::SHADER_BASIC_UI));
	}
}