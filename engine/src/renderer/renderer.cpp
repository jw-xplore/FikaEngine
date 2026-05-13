#include "renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "resources/gResourceManager.h"
#include "resources/meshBuilder.h"
#include "resources/meshInstance.h"
#include "../core/memory.h"

namespace Renderer
{
	static int width, height;
	static PoolAllocator<MeshInstance> meshes(MAX_MESHES);

	void init(int w, int h)
	{
		width = w;
		height = h;
	}

	void render(glm::mat4 mvp)
	{
		for (size_t i = 0; i < meshes.used; i++)
		{
			meshes.at(i).draw(mvp);
		}
	}

	void clear() { glClear(GL_COLOR_BUFFER_BIT); }

	MeshInstance* addMeshInstance(MeshResource& meshRes, ShaderResource& shader)
	{
		MeshInstance* mesh = meshes.allocate();
		mesh->setMesh(&meshRes);
		mesh->setShader(&shader);

		return mesh;
	}
}