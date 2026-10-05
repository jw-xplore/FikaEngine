#pragma once
#include <fika_engine.h>

using namespace FikaEngine;

class ContentManager
{
public:
	ContentManager();
	~ContentManager();

	void init();
	static Entity& createPlayer();
	static Entity& createBox(glm::vec3 position);
	static Entity& createBullet(glm::vec3 position, glm::vec3 velocity);
};