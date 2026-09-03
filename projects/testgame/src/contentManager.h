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

	/*
	GameObject& createPlayer(glm::vec3 position);
	GameObject& createWall(glm::vec3 position, bool solid = true);
	*/
	void createTestEntity();
	void createTestWall(glm::vec3 pos);

	void loadWalls(const char* filePath);
};