#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class MeshResource;
class TextureResource;
class ShaderResource;


//------------------------------------------------------------------------------
// Mesh instance
//------------------------------------------------------------------------------

class MeshInstance
{
private:
	MeshResource* mesh;
	TextureResource* texture;
	ShaderResource* shader;

public:
	glm::mat4* transform;

	MeshInstance();
	MeshInstance(MeshResource& meshRes, ShaderResource& shader, TextureResource* texture, glm::mat4* transform);

	void setMesh(MeshResource* mesh) { this->mesh = mesh; }
	void setTexture(TextureResource* texture) { this->texture = texture; }
	void setShader(ShaderResource* shader) { this->shader = shader; }
	void setTransform(glm::mat4* transform) { this->transform = transform; }

	MeshResource* getMesh() { return mesh; }
	TextureResource* getTexture() { return texture; }
	ShaderResource* gettShader() { return shader; }

	void draw(glm::mat4 mvp);
};