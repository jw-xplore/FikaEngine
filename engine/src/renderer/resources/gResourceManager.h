#pragma once
#define GLFW_INCLUDE_NONE

#include <map>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class MeshResource;
class TextureResource;
class ShaderResource;

//------------------------------------------------------------------------------
// Mesh resource
//------------------------------------------------------------------------------

class MeshResource
{
public:
	GLuint VOA; // Vertex object array
	GLuint VBO; // Vertex Buffer Object
	GLuint EBO; // Element Buffer Object
	int indicesCount;
	TextureResource* textureRes;

	MeshResource();
	MeshResource(const MeshResource& meshRes);
	~MeshResource();

	void cleanup();
};

//------------------------------------------------------------------------------
// Shader resource
//------------------------------------------------------------------------------

class ShaderResource
{
public:
	GLchar* vertexBuffer;
	GLchar* fragmentBuffer;

	const char* lastVpath;
	const char* lastFpath;

	GLuint program = 0;
	GLuint vertexShader = 0;
	GLuint pixelShader = 0;

	std::string compilerLog;

	ShaderResource();
	ShaderResource(const ShaderResource& shaderRes);
	ShaderResource(const char* vpath, const char* fpath);

	void loadShader(const char* path, GLchar*& buffer);
	void loadShaders(const char* vpath, const char* fpath);
	ShaderResource& compile();
	void reload();
	void use();

	void setUniform(const GLchar* name, glm::mat4 value)
	{
		unsigned int location = glGetUniformLocation(program, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)&value);
	}

	void setUniform(const GLchar* name, glm::vec4 value)
	{
		unsigned int location = glGetUniformLocation(program, name);
		glUniform4fv(location, 1, (GLfloat*)&value);
	}

	void setUniform(const GLchar* name, glm::vec3 value)
	{
		unsigned int location = glGetUniformLocation(program, name);
		glUniform3fv(location, 1, (GLfloat*)&value);
	}

	void setUniform(const GLchar* name, float value)
	{
		unsigned int location = glGetUniformLocation(program, name);
		glUniform1fv(location, 1, (GLfloat*)&value);
	}

	void setUniform(const GLchar* name, void* value, int size)
	{
		unsigned int location = glGetUniformLocation(program, name);
		glUniform3fv(location, size, (GLfloat*)&value);
	}
};

//------------------------------------------------------------------------------
// Texture resource
//------------------------------------------------------------------------------

class TextureResource
{
public:
	unsigned int texture;

	TextureResource();
	~TextureResource();

	void loadTexture(const char* path);
	void activateTexture(unsigned int* texture);
};

//------------------------------------------------------------------------------
// Resource manager
//------------------------------------------------------------------------------

namespace GResourceManager
{
	MeshResource* reserveMesh(std::string name);
	int storeMesh(std::string name, MeshResource& mesh);
	int storeTexture(std::string name, TextureResource& texture);
	int storeShader(std::string name, ShaderResource& shader);

	int meshHandle(std::string name);
	int textureHandle(std::string name);
	int shaderHandle(std::string name);

	MeshResource& getMesh(int handle);
	TextureResource& getTexture(int handle);
	ShaderResource& getShader(int handle);

	void init();
	void reloadShaders();
	void debugPrint();
};