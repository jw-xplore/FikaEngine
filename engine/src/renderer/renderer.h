#pragma once
#include <vector>
#include <glm/glm.hpp>

class MeshResource;
class ShaderResource;
class MeshInstance;

namespace Renderer
{
	const int MAX_MESHES = 256;

	/**
	 * @brief Render all mesh instances in list withing given projection. 
	 * @param mvp Model view projection. Camera view matrix.
	 */
	void render(glm::mat4 mvp);

	/**
	 * @brief Create new mesh instance into render pool. Mesh instance will be automatically rendered each frame.
	 * @param meshRes Model mesh used for the instance.
	 * @param shader Shader used for the instance
	 * @return New created mesh instanced
	 */
	MeshInstance* addMeshInstance(MeshResource& meshRes, ShaderResource& shader);
}