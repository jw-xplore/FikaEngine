#include "renderer.h"
#include "core/systemsHolder.h"
#include "resources/gResourceManager.h"
#include "resources/meshBuilder.h"
#include "resources/meshInstance.h"
#include <iostream>

Renderer::Renderer()
{
	meshes = new PoolAllocator<MeshInstance>("Meshes", MAX_MESHES);
}

Renderer::~Renderer()
{

}

void Renderer::init()
{
	// Lines shader
	SystemsHolder* systems = SystemsHolder::getInstance();
	GResourceManager* gResMngr = systems->getGResourceManager();
	ShaderResource shader = ShaderResource("assets/common/shaders/line.vert", "assets/common/shaders/line.frag");
	int shaderID = gResMngr->storeShader("Line", shader);

	linesData.shader = &gResMngr->getShader(shaderID);

	// Setup lines buffer
	linesData.lines = new PoolAllocator<Line>("Lines", MAX_MESHES);
	linesData.vertices.reserve(linesData.lines->getSize() * 2);

	glGenVertexArrays(1, &linesData.vao);
	glGenBuffers(1, &linesData.vbo);

	glBindVertexArray(linesData.vao);
	glBindBuffer(GL_ARRAY_BUFFER, linesData.vbo);
	glBufferData(GL_ARRAY_BUFFER, linesData.lines->getSize() * sizeof(LineVertex), nullptr, GL_DYNAMIC_DRAW);

	// pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (void*)offsetof(LineVertex, position));
	// color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (void*)offsetof(LineVertex, color));

	glBindVertexArray(0);
}

void Renderer::render(glm::mat4 mvp)
{
	// Meshes
	for (size_t i = 0; i < meshes->getUsedAmount(); i++)
	{
		MeshInstance mesh = (*meshes)[i];
		mesh.draw(mvp);
	}

	renderLines(mvp);
}

void Renderer::renderLines(glm::mat4 mvp)
{
	linesData.vertices.clear();

	for (size_t i = 0; i < linesData.lines->getUsedAmount(); i++)
	{
		Line& line = (*linesData.lines)[i];
		linesData.vertices.push_back({ line.a.position, line.a.color });
		linesData.vertices.push_back({ line.b.position, line.a.color });
	}

	// upload only used vertices
	glBindBuffer(GL_ARRAY_BUFFER, linesData.vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, linesData.vertices.size() * sizeof(LineVertex), linesData.vertices.data());

	linesData.shader->use();
	linesData.shader->setUniform("MVP", mvp);

	glBindVertexArray(linesData.vao);
	glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(linesData.vertices.size()));
	glBindVertexArray(0);
	glLineWidth(2);

	linesData.lines->deallocate();
}

MeshInstance* Renderer::addMeshInstance(glm::mat4* transform, MeshResource& meshRes, ShaderResource& shader, TextureResource* texture)
{
	MeshInstance* mesh = meshes->allocate();
	//std::cout << "meshRes" << meshRes->VOA << "&meshRes" << &meshRes.VOA << "\n";
	mesh->setMesh(&meshRes);
	//mesh->setTexture(texture);
	mesh->setShader(&shader);
	mesh->setTransform(transform);

	return mesh;
}

Line* Renderer::addLine(Line line)
{
	Line* l = linesData.lines->allocate();
	l->a = line.a;
	l->b = line.b;

	return l;
}