#pragma once
#include <memory>

#include "renderer/renderer.h"
#include "physics/physics.h"
#include "renderer/camera/cameraManager.h"
#include "renderer/resources/gResourceManager.h"
#include "core/gameresoucemanager.h"
#include "core/ecs/ecsmanager.h"

namespace FikaECS
{
	class ECSManager;
}

class FikaServers
{
private:
	static FikaServers* instance;

	Renderer renderer;
	Renderer debugRenderer; // Renders helper meshes
	FikaECS::ECSManager ecsManager;
	PhysicsSolver physicsSolver;
	CameraManager cameraManager;
	GResourceManager gResourceManager;
	GameResourceManager gameResourceManager;

public:
	FikaServers();
	~FikaServers();

	static FikaServers* getInstance()
	{
		if (!instance)
			instance = new FikaServers();

		return instance;
	}

	void init();

	static Renderer& getMainRenderer() { return FikaServers::getInstance()->renderer; }
	static Renderer& getDebugRenderer() { return FikaServers::getInstance()->debugRenderer; }
	static CameraManager& getCameraManager() { return FikaServers::getInstance()->cameraManager; }
	static GResourceManager& getGResourceManager() { return FikaServers::getInstance()->gResourceManager; }
	static PhysicsSolver& getPhysicsSolver() { return FikaServers::getInstance()->physicsSolver; }
	static FikaECS::ECSManager& getECSManager() { return FikaServers::getInstance()->ecsManager; }
	static GameResourceManager& getGameResourceManager() { return FikaServers::getInstance()->gameResourceManager; }
};