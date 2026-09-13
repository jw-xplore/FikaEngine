#pragma once
#include <memory>

#include "renderer/renderer.h"
#include "physics/physics.h"
#include "renderer/camera/camera_manager.h"
#include "renderer/resources/gpu_resource_manager.h"
#include "core/game_resource_manager.h"
#include "core/ecs/ecs_manager.h"

class FikaServers
{
private:
	static FikaServers* instance;

	Renderer renderer;
	Renderer debugRenderer; // Renders helper meshes
	ECSManager ecsManager;
	PhysicsSolver physicsSolver;
	CameraManager cameraManager;
	GPUResourceManager gpuResourceManager;
	GameResourceManager gameResourceManager;

public:
	FikaServers();
	~FikaServers();

	static FikaServers* getInstance();
	void init();

	// Servers getters
	static Renderer& getMainRenderer()						{ return FikaServers::getInstance()->renderer; }
	static Renderer& getDebugRenderer()						{ return FikaServers::getInstance()->debugRenderer; }
	static CameraManager& getCameraManager()				{ return FikaServers::getInstance()->cameraManager; }
	static GPUResourceManager& getGResourceManager()			{ return FikaServers::getInstance()->gpuResourceManager; }
	static PhysicsSolver& getPhysicsSolver()				{ return FikaServers::getInstance()->physicsSolver; }
	static ECSManager& getECSManager()				{ return FikaServers::getInstance()->ecsManager; }
	static GameResourceManager& getGameResourceManager()	{ return FikaServers::getInstance()->gameResourceManager; }
};