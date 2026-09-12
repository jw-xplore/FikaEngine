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

	Renderer m_Renderer;
	Renderer m_DebugRenderer; // Renders helper meshes
	ECSManager m_EcsManager;
	PhysicsSolver m_PhysicsSolver;
	CameraManager m_CameraManager;
	GResourceManager m_GResourceManager;
	GameResourceManager m_GameResourceManager;

public:
	FikaServers();
	~FikaServers();

	static FikaServers* getInstance();
	void init();

	// Servers getters
	static Renderer& getMainRenderer()						{ return FikaServers::getInstance()->m_Renderer; }
	static Renderer& getDebugRenderer()						{ return FikaServers::getInstance()->m_DebugRenderer; }
	static CameraManager& getCameraManager()				{ return FikaServers::getInstance()->m_CameraManager; }
	static GResourceManager& getGResourceManager()			{ return FikaServers::getInstance()->m_GResourceManager; }
	static PhysicsSolver& getPhysicsSolver()				{ return FikaServers::getInstance()->m_PhysicsSolver; }
	static ECSManager& getECSManager()				{ return FikaServers::getInstance()->m_EcsManager; }
	static GameResourceManager& getGameResourceManager()	{ return FikaServers::getInstance()->m_GameResourceManager; }
};