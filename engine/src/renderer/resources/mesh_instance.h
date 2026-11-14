#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace FikaEngine
{
	class MeshResource;
	class TextureResource;
	class ShaderResource;

	//------------------------------------------------------------------------------
	// Mesh instance
	//------------------------------------------------------------------------------

	class MeshInstance
	{
	private:
		MeshResource* mesh = nullptr;
		TextureResource* texture = nullptr;
		ShaderResource* shader = nullptr;
		bool visible = true;

		glm::vec2 textureScale = glm::vec2(1.0f);
		glm::vec2 textureOffset = glm::vec2(0.0f);

	public:
		glm::mat4* transform;
		glm::vec3 customScale = glm::vec3(1.0);

		MeshInstance();
		MeshInstance(MeshResource& meshRes, ShaderResource& shader, TextureResource* texture, glm::mat4* transform);

		void setMesh(MeshResource* mesh) { this->mesh = mesh; }
		void setTexture(TextureResource* texture) { this->texture = texture; }
		void setShader(ShaderResource* shader) { this->shader = shader; }
		void setTransform(glm::mat4* transform) { this->transform = transform; }
		void setTextureScale(glm::vec2 scale) { this->textureScale = scale; }
		void setTextureOffset(glm::vec2 offset) { this->textureOffset = offset; }

		MeshResource* getMesh() { return mesh; }
		TextureResource* getTexture() { return texture; }
		ShaderResource* gettShader() { return shader; }

		void setVisible(bool visible) { this->visible = visible; }
		bool getVisible() { return visible; }

		void draw(glm::mat4 mvp);
	};
} // namespace FikaEngine
