#pragma once
#include <glm/glm.hpp>
#include <fikaEngine.h>

class ContentManager
{
private:
	GResourceManager* gResourceManager;
	FikaECS::ECSManager* ecsManager;
	MeshResource* cubeMesh;
	ShaderResource* basicShader;
	MeshResource* customMesh;
	TextureResource* customTexture;

public:
	ContentManager();
	~ContentManager();

	FikaECS::Entity& createPlayer(glm::vec3 position);
	FikaECS::Entity& createWall(glm::vec3 position, bool solid = true);

	void loadWalls(const char* filePath);
};