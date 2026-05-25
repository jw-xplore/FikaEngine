#pragma once
#include <vector>
#include <glm/glm.hpp>

class MeshResource;
class ShaderResource;
class MeshInstance;

namespace Renderer
{
	const int MAX_MESHES = 256;

	void render(glm::mat4 mvp);

	/// <summary>
	/// Create new mesh instance into render pool. Mesh instance will be automatically rendered each frame.
	/// </summary>
	/// <param name="meshRes">Model mesh used for the instance.</param>
	/// <param name="shader">Shader used for the instance/</param>
	/// <returns>New created mesh instanced</returns>
	MeshInstance* addMeshInstance(MeshResource& meshRes, ShaderResource& shader);
}