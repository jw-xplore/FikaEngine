#include "gResourceManager.h"
#include <iostream>
#include <fstream>

//------------------------------------------------------------------------------
// Mesh resource
//------------------------------------------------------------------------------

MeshResource::MeshResource()
{
}

MeshResource::MeshResource(const MeshResource& meshRes)
{
	VOA = meshRes.VOA;
	VBO = meshRes.VBO;
	EBO = meshRes.EBO;
	indicesCount = meshRes.indicesCount;
	textureRes = meshRes.textureRes;
}

MeshResource::~MeshResource()
{
	cleanup();
}

void MeshResource::cleanup()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VOA);
	//delete textureRes;
}

//------------------------------------------------------------------------------
// Shader resource
//------------------------------------------------------------------------------

#define STRING_BUFFER_SIZE 8192

ShaderResource::ShaderResource()
{
}

ShaderResource::ShaderResource(const ShaderResource& shaderRes)
{
	vertexBuffer = shaderRes.vertexBuffer;
	fragmentBuffer = shaderRes.fragmentBuffer;

	lastVpath = shaderRes.lastVpath;
	lastFpath = shaderRes.lastFpath;

	program = shaderRes.program;
	vertexShader = shaderRes.vertexShader;
	pixelShader = shaderRes.pixelShader;

	compilerLog = shaderRes.compilerLog;
}

ShaderResource::ShaderResource(const char* vpath, const char* fpath)
{
	loadShaders(vpath, fpath);
	compile();
}

void ShaderResource::loadShader(const char* path, GLchar*& buffer)
{
	std::string fileData;

	// Read file
	try
	{
		std::fstream file(path);

		// Not found
		if (file.fail())
		{
			std::cout << "Shader file: '" << path << "' not found! \n";
			return;
		}

		// Read
		std::string line;
		while (std::getline(file, line))
		{
			fileData += line + "\n";
		}
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Failed to load shader: " << path << "\n";
	}

	// Setup buffer
	buffer = new GLchar[STRING_BUFFER_SIZE];
	std::strncpy(buffer, fileData.c_str(), STRING_BUFFER_SIZE);
}

void ShaderResource::loadShaders(const char* vpath, const char* fpath)
{
	lastVpath = vpath;
	lastFpath = fpath;

	loadShader(vpath, vertexBuffer);
	loadShader(fpath, fragmentBuffer);
}

ShaderResource& ShaderResource::compile()
{
	// check if shader already exists
	if (this->program)
	{
		glDeleteProgram(this->program);
		this->program = 0;
	}
	if (this->vertexShader)
	{
		glDeleteShader(this->vertexShader);
		this->vertexShader = 0;
	}
	if (this->pixelShader)
	{
		glDeleteShader(this->pixelShader);
		this->pixelShader = 0;
	}

	this->compilerLog.clear();

	// setup vertex shader
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLint length = static_cast<GLint>(std::strlen(this->vertexBuffer));
	glShaderSource(this->vertexShader, 1, &this->vertexBuffer, &length);
	glCompileShader(this->vertexShader);

	// get error log
	GLint shaderLogSize;
	glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
		this->compilerLog.append(buf);
		printf("[VERTEX SHADER COMPILE ERROR]: %s", buf);
		delete[] buf;
	}

	// setup pixel shader
	this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
	length = static_cast<GLint>(std::strlen(this->fragmentBuffer));
	glShaderSource(this->pixelShader, 1, &this->fragmentBuffer, &length);
	glCompileShader(this->pixelShader);

	// get error log
	shaderLogSize;
	glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
		this->compilerLog.append(buf);
		printf("[PIXEL SHADER COMPILE ERROR]: %s", buf);
		delete[] buf;
	}

	// create a program object
	this->program = glCreateProgram();
	glAttachShader(this->program, this->vertexShader);
	glAttachShader(this->program, this->pixelShader);
	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
		this->compilerLog.append(buf);
		printf("[PROGRAM LINK ERROR]: %s", buf);
		delete[] buf;
	}

	return *this;
}

void ShaderResource::reload()
{
	loadShaders(lastVpath, lastFpath);
	compile();
}

void ShaderResource::use()
{
	glUseProgram(program);
}

//------------------------------------------------------------------------------
// Texture resource
//------------------------------------------------------------------------------

TextureResource::TextureResource()
{

}

TextureResource::~TextureResource()
{
	glDeleteTextures(1, &texture);
}

void TextureResource::loadTexture(const char* path)
{

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Bind
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load
	int width, height, channels;

	/*
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load(path, &width, &height, &channels, 0);
	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Texuture not found: " << path << "\n";
	}
	*/

	// Cleanup
	//stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureResource::activateTexture(unsigned int* texture)
{
	glBindTexture(GL_TEXTURE_2D, *texture);
}

//------------------------------------------------------------------------------
// Resource manager
//------------------------------------------------------------------------------

namespace GResourceManager
{
	std::vector<MeshResource> meshes;
	std::vector<TextureResource> textures;
	std::vector<ShaderResource> shaders;

	std::map<std::string, int> meshHandles;
	std::map<std::string, int> textureHandles;
	std::map<std::string, int> shaderHandles;

	int storeMesh(std::string name, MeshResource& mesh)
	{
		meshes.push_back(mesh);
		return meshes.size() - 1;
	}

	int storeTexture(std::string name, TextureResource& texture)
	{
		textures.push_back(texture);
		return textures.size() - 1;
	}

	int storeShader(std::string name, ShaderResource& shader)
	{
		shaders.push_back(shader);
		return shaders.size() - 1;
	}

	int meshHandle(std::string name)
	{
		if (meshHandles.find(name) != meshHandles.end())
			return -1;

		return meshHandles[name];
	}

	int textureHandle(std::string name)
	{
		if (textureHandles.find(name) != textureHandles.end())
			return -1;

		return textureHandles[name];
	}

	int shaderHandle(std::string name)
	{
		if (shaderHandles.find(name) != shaderHandles.end())
			return -1;

		return shaderHandles[name];
	}

	MeshResource& getMesh(int handle)
	{
		return meshes[handle];
	}

	TextureResource& getTexture(int handle)
	{
		return textures[handle];
	}

	ShaderResource& getShader(int handle)
	{
		return shaders[handle];
	}

	void reloadShaders()
	{
		for (auto shader : shaders)
		{
			shader.reload();
		}
	}
}