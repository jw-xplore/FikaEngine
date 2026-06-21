#pragma once
#include <glm/glm.hpp>
#include <fikaEngine.h>

class ContentManager
{
private:
	MeshResource* cubeMesh;
	ShaderResource* basicShader;
	MeshResource* customMesh;
	TextureResource* customTexture;

public:
	ContentManager();
	~ContentManager();

	void createPlayer(glm::vec3 position);
	void createWall(glm::vec3 position);
};