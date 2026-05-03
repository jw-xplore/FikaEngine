#pragma once
#include <vector>
#include <glm/glm.hpp>

class MeshResource;

struct VertexAttributes
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
	glm::vec3 normal;

	VertexAttributes() {}
	VertexAttributes(glm::vec3 position, glm::vec4 color, glm::vec2 uv, glm::vec3 normal) :
		position(position),
		color(color),
		uv(uv),
		normal(normal)
	{
	}
};

class MeshBuilder
{
public:
	std::vector<VertexAttributes> vertexBuffer;
	std::vector<unsigned int> indices;
	const char* texturePath;

	MeshBuilder();

	MeshResource& build();

	MeshBuilder& addVertices(glm::vec3 position, glm::vec4 color, glm::vec2 uv, glm::vec3 normal);
	MeshBuilder& addVertices(VertexAttributes& vertex);
	MeshBuilder& addTriangles(unsigned int v0, unsigned int v1, unsigned int v2);
	MeshBuilder& setTexturePath(const char* path);

	//MeshBuilder& loadMesh(const char* path);
	MeshBuilder& createQuad(float width, float height);
	MeshBuilder& createCube(float size);
};