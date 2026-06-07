#include "meshInstance.h"
#include "gResourceManager.h"
#include <iostream>

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
	shader->use();
	shader->setUniform("transform", *transform);
	shader->setUniform("MVP", mvp);

	if (texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture->texture);
	}

	glBindVertexArray(mesh->VOA);
	glDrawElements(GL_TRIANGLES, mesh->indicesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}