#include "meshInstance.h"
#include "gResourceManager.h"
#include <iostream>

MeshInstance::MeshInstance()
{
	transform = glm::mat4(1.0f);
}

// Mesh settings
MeshResource* MeshInstance::setMesh(std::string name)
{
	auto meshes = &GResourceManager::getInstance()->meshes;

	if (meshes->find(name) == meshes->end())
	{
		std::cout << "No mesh '" << name << "' found!\n";
		return nullptr;
	}

	this->mesh = meshes->at(name);

	return this->mesh;
}

MeshResource* MeshInstance::setMesh(std::string name, MeshResource* mesh)
{
	auto meshes = &GResourceManager::getInstance()->meshes;

	if (meshes->find(name) != meshes->end())
	{
		std::cout << "Mesh '" << name << "' is alread used!\n";
		return nullptr;
	}

	meshes->insert({ name, mesh });
	this->mesh = mesh;

	return this->mesh;
}

// Texture settings
TextureResource* MeshInstance::setTexture(std::string name)
{
	auto textures = &GResourceManager::getInstance()->textures;

	if (textures->find(name) == textures->end())
	{
		std::cout << "No texture '" << name << "' found!\n";
		return nullptr;
	}

	this->texture = textures->at(name);

	return this->texture;
}

TextureResource* MeshInstance::setTexture(std::string name, TextureResource* texture)
{
	auto textures = &GResourceManager::getInstance()->textures;

	if (textures->find(name) != textures->end())
	{
		std::cout << "Texture '" << name << "' is alread used!\n";
		return nullptr;
	}

	this->texture = texture;
	textures->insert({ name, texture });

	return this->texture;
}

// Shader settings
ShaderResource* MeshInstance::setShader(std::string name)
{
	auto shaders = &GResourceManager::getInstance()->shaders;

	if (shaders->find(name) == shaders->end())
	{
		std::cout << "No shader '" << name << "' found!\n";
		return nullptr;
	}

	this->shader = shaders->at(name);

	return this->shader;
}

ShaderResource* MeshInstance::setShader(std::string name, ShaderResource* shader)
{
	auto shaders = &GResourceManager::getInstance()->shaders;

	if (shaders->find(name) != shaders->end())
	{
		std::cout << "Shader '" << name << "' is alread used!\n";
		return nullptr;
	}

	shaders->insert({ name, shader });
	this->shader = shader;

	return this->shader;
}

// Draw - Render
void MeshInstance::draw()
{
	shader->use();
	shader->setUniform("transform", transform);

	if (mesh->textureRes->texture)
		glBindTexture(GL_TEXTURE_2D, mesh->textureRes->texture);

	glBindVertexArray(mesh->VOA);
	glDrawElements(GL_TRIANGLES, mesh->indicesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}