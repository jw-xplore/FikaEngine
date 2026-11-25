#pragma once
#include <vector>
#include <glm/glm.hpp>

namespace FikaEngine
{
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
		{}
	};

	class MeshBuilder
	{
	public:
		std::vector<VertexAttributes> vertexBuffer;
		std::vector<unsigned int> indices;
		//const char* texturePath;

		MeshBuilder();

		void build(MeshResource& resource);

		MeshBuilder& addVertices(glm::vec3 position, glm::vec4 color, glm::vec2 uv, glm::vec3 normal);
		MeshBuilder& addVertices(VertexAttributes& vertex);
		MeshBuilder& addTriangles(unsigned int v0, unsigned int v1, unsigned int v2);

		MeshBuilder& loadMesh(const char* path);
		MeshBuilder& createQuad(float width, float height);
		MeshBuilder& createCube(float size);
	};

	//------------------------------------------------------------------------------
	// 2D Mesh builder
	//------------------------------------------------------------------------------

	struct VertexAttributes2D
	{
		glm::vec2 position;
		glm::vec2 uv;

		VertexAttributes2D() {}
		VertexAttributes2D(glm::vec2 position, glm::vec2 uv) : position(position), uv(uv) {}
	};

	class MeshBuilder2D
	{
	private:
		std::vector<VertexAttributes2D> vertexBuffer;
		std::vector<unsigned int> indices;

	public:
		void build(MeshResource& resource);

		MeshBuilder2D& addVertices(glm::vec2 position, glm::vec2 uv);
		MeshBuilder2D& addTriangles(unsigned int v0, unsigned int v1, unsigned int v2);

		MeshBuilder2D& createRectangle(float width, float height);
	};

} // namespace FikaEngine
