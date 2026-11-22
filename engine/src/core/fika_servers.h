#pragma once
#include <memory>

#include "renderer/renderer.h"
#include "physics/physics.h"
#include "renderer/camera/camera_manager.h"
#include "renderer/resources/gpu_resource_manager.h"
#include "core/game_resource_manager.h"
#include "core/ecs/ecs_manager.h"
#include "platform/inputs/input_manager.h"
#include "audio/audio_manager.h"
#include "dev/debug_console.h"

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
		AudioManager audioManager;
		DebugConsole debugConsole;

	public:
		FikaServers();
		~FikaServers();

		static FikaServers* getInstance();
		void init();
		void setWindow(Window* window);
		static void consolePrint(std::string text, std::initializer_list<std::string> additionalText = {});

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
		static AudioManager& getAudioManager()					{ return FikaServers::getInstance()->audioManager; }
		static DebugConsole& getDebugConsole()					{ return FikaServers::getInstance()->debugConsole; }
	};
} // namespace FikaEngine