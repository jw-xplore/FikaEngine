#pragma once
#include <glm/glm.hpp>
#include <fika_engine.h>

class ContentManager
{
private:
	GResourceManager* gResourceManager;
	ECSManager* ecsManager;
	MeshResource* cubeMesh;
	ShaderResource* basicShader;
	MeshResource* customMesh;
	TextureResource* customTexture;

public:
	ContentManager();
	~ContentManager();

	Entity& createPlayer(glm::vec3 position);
	Entity& createWall(glm::vec3 position, bool solid = true);

	void loadWalls(const char* filePath);
};