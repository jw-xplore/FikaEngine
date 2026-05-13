#pragma once
#include <vector>
#include <glm/glm.hpp>

class MeshResource;
class ShaderResource;
class MeshInstance;

namespace Renderer
{
	const int MAX_MESHES = 256;

	void init(int w, int h);
	void render(glm::mat4 mvp);
	void clear();

	MeshInstance* addMeshInstance(MeshResource& meshRes, ShaderResource& shader);
}