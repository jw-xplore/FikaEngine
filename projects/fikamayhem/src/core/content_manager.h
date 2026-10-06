#pragma once
#include <fika_engine.h>

using namespace FikaEngine;

class ContentManager
{
private:
	static Entity* playerEntity;

public:
	ContentManager();
	~ContentManager();

	static Entity* getPlayerEntity() { return playerEntity; }

	void init();
	static Entity& createPlayer();
	static Entity& createBox(glm::vec3 position);
	static Entity& createBullet(glm::vec3 position, glm::vec3 velocity, float lifetime = 3);
	static Entity& createEnemy(glm::vec3 position);
};