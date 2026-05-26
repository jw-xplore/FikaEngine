#include "renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "resources/gResourceManager.h"
#include "resources/meshBuilder.h"
#include "resources/meshInstance.h"
#include "../core/memory.h"
#include <iostream>

namespace Renderer
{
	static int width, height;
	static PoolAllocator<MeshInstance> meshes(MAX_MESHES);

	void render(glm::mat4 mvp)
	{
		for (size_t i = 0; i < meshes.used; i++)
		{
			MeshInstance mesh = meshes.at(i);
			mesh.draw(mvp);
		}
	}

	MeshInstance* addMeshInstance(MeshResource& meshRes, ShaderResource& shader)
	{
		MeshInstance* mesh = meshes.allocate();
		//std::cout << "meshRes" << meshRes->VOA << "&meshRes" << &meshRes.VOA << "\n";
		mesh->setMesh(&meshRes);
		mesh->setShader(&shader);

		return mesh;
	}
}