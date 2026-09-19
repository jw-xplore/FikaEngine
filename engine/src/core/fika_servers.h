#pragma once
#include <memory>

#include "renderer/renderer.h"
#include "physics/physics.h"
#include "renderer/camera/camera_manager.h"
#include "renderer/resources/gpu_resource_manager.h"
#include "core/game_resource_manager.h"
#include "core/ecs/ecs_manager.h"
#include "platform/inputs/input_manager.h"

namespace FikaEngine
{
	class FikaServers
	{
	private:
		static FikaServers* instance;

		Window* window;
		Renderer renderer;
		Renderer debugRenderer; // Renders helper meshes
		ECSManager ecsManager;
		PhysicsSolver physicsSolver;
		CameraManager cameraManager;
		GPUResourceManager gpuResourceManager;
		GameResourceManager gameResourceManager;
		InputManager inputManager;

	public:
		FikaServers();
		~FikaServers();

		static FikaServers* getInstance();
		void init();
		void setWindow(Window* window);

		// Servers getters
		static Window* getWindow()								{ return FikaServers::getInstance()->window; }
		static Renderer& getMainRenderer()						{ return FikaServers::getInstance()->renderer; }
		static Renderer& getDebugRenderer()						{ return FikaServers::getInstance()->debugRenderer; }
		static CameraManager& getCameraManager()				{ return FikaServers::getInstance()->cameraManager; }
		static GPUResourceManager& getGPUResourceManager()		{ return FikaServers::getInstance()->gpuResourceManager; }
		static PhysicsSolver& getPhysicsSolver()				{ return FikaServers::getInstance()->physicsSolver; }
		static ECSManager& getECSManager()						{ return FikaServers::getInstance()->ecsManager; }
		static GameResourceManager& getGameResourceManager()	{ return FikaServers::getInstance()->gameResourceManager; }
		static InputManager& getInputManager()					{ return FikaServers::getInstance()->inputManager; }
	};
} // namespace FikaEngine