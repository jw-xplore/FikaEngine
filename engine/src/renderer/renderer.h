#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <memory>
#include "core/memorymanagement.h"

class MeshResource;
class ShaderResource;
class MeshInstance;
class TextureResource;

class Renderer
{
private:
	PoolAllocator<MeshInstance>* meshes;

public:
	const int MAX_MESHES = 256;

	Renderer();
	~Renderer();

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
	MeshInstance* addMeshInstance(glm::mat4* transform, MeshResource& meshRes, ShaderResource& shader, TextureResource* texture = nullptr);
};