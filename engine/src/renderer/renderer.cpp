#include "renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "resources/gResourceManager.h"
#include "resources/meshBuilder.h"
#include "resources/meshInstance.h"
#include <iostream>

Renderer::Renderer()
{
	meshes = new PoolAllocator<MeshInstance>(MAX_MESHES);
}

Renderer::~Renderer()
{

}

void Renderer::render(glm::mat4 mvp)
{
	for (size_t i = 0; i < meshes->used; i++)
	{
		MeshInstance mesh = meshes->at(i);
		mesh.draw(mvp);
	}
}

MeshInstance* Renderer::addMeshInstance(glm::mat4* transform, MeshResource& meshRes, ShaderResource& shader, TextureResource* texture)
{
	MeshInstance* mesh = meshes->allocate();
	//std::cout << "meshRes" << meshRes->VOA << "&meshRes" << &meshRes.VOA << "\n";
	mesh->setMesh(&meshRes);
	//mesh->setTexture(texture);
	mesh->setShader(&shader);
	mesh->setTransform(transform);

	return mesh;
}