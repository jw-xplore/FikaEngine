#pragma once
#include <glm/glm.hpp>
#include <fikaEngine.h>

class ContentManager
{
private:
	GResourceManager* gResourceManager;
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
	void loadWalls(const char* filePath);
};