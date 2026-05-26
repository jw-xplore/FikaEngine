#include "meshBuilder.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "gResourceManager.h"
#include "core/filemanagement/objparser.h"

MeshBuilder::MeshBuilder()
{
	texturePath = "";
}

void MeshBuilder::build(MeshResource& resource)
{
	glGenVertexArrays(1, &resource.VOA);
	glBindVertexArray(resource.VOA);

	// Vertices
	glGenBuffers(1, &resource.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, resource.VBO);
	int size = sizeof(VertexAttributes) * vertexBuffer.size();
	glBufferData(GL_ARRAY_BUFFER, size, vertexBuffer.data(), GL_STATIC_DRAW);

	// Elements
	glGenBuffers(1, &resource.EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resource.EBO);
	size = sizeof(int) * indices.size();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices.data(), GL_STATIC_DRAW);

	// Texture
	if (texturePath && texturePath != "" && strlen(texturePath) != 0)
	{
		resource.textureRes = new TextureResource();
		resource.textureRes->loadTexture(texturePath);
	}

	// Attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	// These attributes handle positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributes), NULL);
	// These attributes handle colors
	int offset = 3;
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexAttributes), (GLvoid*)(sizeof(GLfloat) * offset));
	// UV
	offset += 4;
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttributes), (GLvoid*)(sizeof(GLfloat) * offset));
	// Normals
	offset += 2;
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributes), (GLvoid*)(sizeof(GLfloat) * offset));

	resource.indicesCount = indices.size();

	vertexBuffer.clear();
	indices.clear();
	texturePath = "";
}

MeshBuilder& MeshBuilder::addVertices(glm::vec3 position, glm::vec4 color, glm::vec2 uv = glm::vec2(0, 0), glm::vec3 normal = glm::vec3(0, 0, 0))
{
	VertexAttributes attribute;
	attribute.position = position;
	attribute.color = color;
	attribute.uv = uv;
	attribute.normal = normal;

	vertexBuffer.push_back(attribute);

	return *this;
}

MeshBuilder& MeshBuilder::addVertices(VertexAttributes& vertex)
{
	vertexBuffer.push_back(vertex);
	return *this;
}

MeshBuilder& MeshBuilder::addTriangles(unsigned int v0, unsigned int v1, unsigned int v2)
{
	// Add position
	indices.push_back(v0);
	indices.push_back(v1);
	indices.push_back(v2);

	return *this;
}

MeshBuilder& MeshBuilder::setTexturePath(const char* path)
{
	texturePath = path;
	return *this;
}

MeshBuilder& MeshBuilder::loadMesh(const char* path)
{
	OBJParser::readFile(path, *this);
	return *this;
}

MeshBuilder& MeshBuilder::createQuad(float width, float height)
{
	addVertices({ -width, -height,-1 }, { 1,0,0,1 });			// 0 - TL
	addVertices({ width, -height,-1 }, { 0,1,0,1 });		// 1 - TR
	addVertices({ width, height,-1 }, { 0,0,1,1 });	// 2 - BR
	addVertices({ -width, height,-1 }, { 1,1,1,1 });		// 3 - BL

	//resource->indexBuffer = new GLint[3 * 2];

	addTriangles(0, 1, 2);
	addTriangles(2, 3, 0);

	return *this;
}

float cubeVertices[] = {
	// BACK (-Z)
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,

	// FRONT (+Z)
	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	// BOTTOM (-Y)
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	// TOP (+Y)
	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	// LEFT (-X)
	-0.5f, -0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	// RIGHT (+X)
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
};

unsigned int cubeIndices[] = {
	0, 1, 2, 2, 3, 0,       // back
	4, 5, 6, 6, 7, 4,       // front
	8, 9,10,10,11, 8,       // bottom
   12,13,14,14,15,12,       // top
   16,17,18,18,19,16,       // left
   20,21,22,22,23,20        // right
};

float cubeUVs[] = {
	// Back
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,

	// Front
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	// Bottom
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	// Top
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,

	// Left
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,

	// Right
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
};

// Normals
float cubeNormals[] = {
	// BACK (-Z)
	0.0f,  0.0f, -1.0f,
	0.0f,  0.0f, -1.0f,
	0.0f,  0.0f, -1.0f,
	0.0f,  0.0f, -1.0f,

	// FRONT (+Z)
	0.0f,  0.0f,  1.0f,
	0.0f,  0.0f,  1.0f,
	0.0f,  0.0f,  1.0f,
	0.0f,  0.0f,  1.0f,

	// BOTTOM (-Y)
	0.0f, -1.0f,  0.0f,
	0.0f, -1.0f,  0.0f,
	0.0f, -1.0f,  0.0f,
	0.0f, -1.0f,  0.0f,

	// TOP (+Y)
	0.0f,  1.0f,  0.0f,
	0.0f,  1.0f,  0.0f,
	0.0f,  1.0f,  0.0f,
	0.0f,  1.0f,  0.0f,

	// LEFT (-X)
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,

	// RIGHT (+X)
	1.0f,  0.0f,  0.0f,
	1.0f,  0.0f,  0.0f,
	1.0f,  0.0f,  0.0f,
	1.0f,  0.0f,  0.0f,
};

MeshBuilder& MeshBuilder::createCube(float size)
{
	// Vertices
	int u = 0;
	int vertData = 24 * 3;

	for (int i = 0; i < vertData; i += 3)
	{
		glm::vec3 pos = { cubeVertices[i], cubeVertices[i + 1], cubeVertices[i + 2] };
		glm::vec2 uv = { cubeUVs[u], cubeUVs[u + 1] };
		glm::vec3 norm = { cubeNormals[i], cubeNormals[i + 1], cubeNormals[i + 2] };
		u += 2;

		addVertices(pos * size, { pos,1 }, uv, norm);
	}

	// Indices
	for (int i = 0; i < 36; i += 3)
	{
		addTriangles(cubeIndices[i], cubeIndices[i + 1], cubeIndices[i + 2]);
	}

	return *this;
}