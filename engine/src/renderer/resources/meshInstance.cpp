#include "meshInstance.h"
#include "gResourceManager.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

MeshInstance::MeshInstance()
{

}

MeshInstance::MeshInstance(MeshResource& meshRes, ShaderResource& shader, TextureResource* texture, glm::mat4* transform)
{
	this->mesh = &meshRes;
	this->shader = &shader;
	this->texture = texture;
	this->transform = transform;
}

// Draw - Render
void MeshInstance::draw(glm::mat4 mvp)
{
	glm::mat4 tr = glm::mat4(*transform);
	tr = glm::scale(tr, customScale);

	shader->use();
	shader->setUniform("transform", tr);
	shader->setUniform("MVP", mvp);

	// VOA
	glBindVertexArray(mesh->VOA);

	// Texture
	float useTexture = 0;
	if (texture)
	{
		useTexture = 1;

		if (texture->texture)
		{
			glBindTexture(GL_TEXTURE_2D, texture->texture);
		}

		shader->setUniform("textureSampler", GL_TEXTURE_2D);
	}

	shader->setUniform("useTexture", useTexture);

	glDrawElements(GL_TRIANGLES, mesh->indicesCount, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}