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
	glm::mat4 transform;

	MeshInstance();

	MeshResource* setMesh(std::string name);
	MeshResource* setMesh(std::string name, MeshResource* mesh);
	TextureResource* setTexture(std::string name);
	TextureResource* setTexture(std::string name, TextureResource* texture);
	ShaderResource* setShader(std::string name);
	ShaderResource* setShader(std::string name, ShaderResource* shader);

	MeshResource* getMesh() { return mesh; }
	TextureResource* getTexture() { return texture; }
	ShaderResource* gettShader() { return shader; }

	void draw(glm::mat4 mvp);
};