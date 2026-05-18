#include "meshInstance.h"
#include "gResourceManager.h"
#include <iostream>

MeshInstance::MeshInstance()
{
	transform = glm::mat4(1.0f);
}

// Draw - Render
void MeshInstance::draw(glm::mat4 mvp)
{
	shader->use();
	shader->setUniform("transform", transform);
	shader->setUniform("MVP", mvp);

	/*
	if (mesh->textureRes->texture)
		glBindTexture(GL_TEXTURE_2D, mesh->textureRes->texture);
	*/

	glBindVertexArray(mesh->VOA);
	glDrawElements(GL_TRIANGLES, mesh->indicesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}