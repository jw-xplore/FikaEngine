#pragma once
#include <glm/glm.hpp>
#include <fika_engine.h>

using namespace FikaEngine;

class ContentManager
{
private:

public:
	ContentManager();
	~ContentManager();

	Entity* planeEnt = nullptr;

	void init();
	static Entity& createPlayer(glm::vec3 position);
	static Entity& createWall(glm::vec3 position, bool solid = true);
	static Entity& createEnemy(glm::vec3 position);

	void makePrefabs();
};