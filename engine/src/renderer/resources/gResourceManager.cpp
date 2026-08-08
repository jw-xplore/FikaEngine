#include "gResourceManager.h"
#include <iostream>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

MeshResource* GResourceManager::reserveMesh(std::string name)
{
	meshes.push_back(MeshResource());
	int id = meshes.size() - 1;
	meshHandles[name] = id;

	return &meshes[id];
}

TextureResource& GResourceManager::reseveTexture(std::string name)
{
	textures.push_back(TextureResource());
	int id = textures.size() - 1;
	textureHandles[name] = id;

	return textures[id];
}

int GResourceManager::storeMesh(std::string name, MeshResource& mesh)
{
	meshes.push_back(mesh);
	int id = meshes.size() - 1;
	meshHandles[name] = id;

	return id;
}

int GResourceManager::storeTexture(std::string name, TextureResource& texture)
{
	textures.push_back(texture);
	int id = textures.size() - 1;
	textureHandles[name] = id;

	return id;
}

int GResourceManager::storeShader(std::string name, ShaderResource& shader)
{
	shaders.push_back(shader);
	int id = shaders.size() - 1;
	shaderHandles[name] = id;

	return id;
}

int GResourceManager::meshHandle(std::string name)
{
	if (!meshHandles.contains(name))
		return -1;

	return meshHandles[name];
}

int GResourceManager::textureHandle(std::string name)
{
	if (!textureHandles.contains(name))
		return -1;

	return textureHandles[name];
}

int GResourceManager::shaderHandle(std::string name)
{
	if (!shaderHandles.contains(name))
		return -1;

	return shaderHandles[name];
}

MeshResource& GResourceManager::getMesh(int handle)
{
	return meshes[handle];
}

MeshResource& GResourceManager::getMesh(std::string handle)
{
	int id = meshHandle(handle);
	return meshes[id];
}

TextureResource& GResourceManager::getTexture(int handle)
{
	return textures[handle];
}

TextureResource& GResourceManager::getTexture(std::string handle)
{
	int id = textureHandle(handle);
	return textures[id];
}

ShaderResource& GResourceManager::getShader(int handle)
{
	return shaders[handle];
}

ShaderResource& GResourceManager::getShader(std::string handle)
{
	int id = shaderHandle(handle);
	return shaders[id];
}

void GResourceManager::init()
{
	// TODO: Add safety for resources changing address due to pushing over reserved count
	meshes.reserve(128);
	textures.reserve(128);
	shaders.reserve(128);
}

void GResourceManager::reloadShaders()
{
	for (auto shader : shaders)
	{
		shader.reload();
	}
}

void GResourceManager::debugPrint()
{
	std::cout << "Meshes: " << &meshes[0] << "\n";
}