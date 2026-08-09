#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <memory>
#include "core/memorymanagement.h"

class MeshResource;
class ShaderResource;
class MeshInstance;
class TextureResource;

struct LineVertex
{
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 color = glm::vec3(1.0f);
};

struct Line
{
	LineVertex a;
	LineVertex b;

	Line() {}

	Line(glm::vec3 posA, glm::vec3 posB, glm::vec3 color)
	{
		a.position = posA;
		b.position = posB;
		a.color = color;
		b.color = color;
	}
};

struct LinesRenderData
{
	PoolAllocator<Line>* lines;
	std::vector<LineVertex> vertices;

	ShaderResource* shader;
	GLuint vao = 0;
	GLuint vbo = 0;
};

class Renderer
{
private:
	PoolAllocator<MeshInstance>* meshes;
	LinesRenderData linesData;

public:
	const int MAX_MESHES = 256;

	Renderer();
	~Renderer();

	void init();

	/**
	 * @brief Render all mesh instances in list withing given projection.
	 * @param mvp Model view projection. Camera view matrix.
	 */
	void render(glm::mat4 mvp);
	void renderLines(glm::mat4 mvp);

	/**
	 * @brief Create new mesh instance into render pool. Mesh instance will be automatically rendered each frame.
	 * @param meshRes Model mesh used for the instance.
	 * @param shader Shader used for the instance
	 * @return New created mesh instanced
	 */
	MeshInstance* addMeshInstance(glm::mat4* transform, MeshResource& meshRes, ShaderResource& shader, TextureResource* texture = nullptr);

	Line* addLine(Line line);
};