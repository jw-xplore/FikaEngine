#pragma once
#include <functional>

/** FikaEngine
* This header gives access to full functionality of the engine.
*/

/*
Includes
*/

// Core
#include "core/fika_servers.h"
#include "core/filemanagement/json.h"
#include "core/game_resource_manager.h"

// ECS
#include "core/ecs/ecs_manager.h"
#include "core/ecs/component.h"
#include "core/ecs/entity.h"
#include "core/ecs/component_updater.h"

// Render
#include "renderer/renderer.h"
#include "renderer/resources/gpu_resource_manager.h"
#include "renderer/resources/mesh_instance.h"
#include "renderer/resources/mesh_builder.h"
#include "renderer/camera/camera_manager.h"
#include "renderer/camera/camera.h"

// Physics
#include "physics/physics.h"
#include "physics/collisions.h"

// Plaftorm
#include "platform/window.h"
#include "platform/inputs/input_devices.h"
#include "platform/inputs/input_handler.h"
#include "platform/inputs/input_mapping.h"

// External
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Components
#include "components/transform_component.h"
#include "components/mesh_component.h"
#include "components/rigidbody_component.h"

/*
Engine
*/

/**
 * @brief Main engine namespace - Call run to initiate engine and game loop in your project.
 */
namespace FikaEngine
{
	class Game
	{
	public:
		/**
		 * @brief Create window, initialize engine and run game loop.
		 * @param startFnc Function for setting up custom project. Is called right before first game loop update.
		 * @param updateFnc Function for custom update. Is called every frame before render.
		 */
		void run(void (*startFnc)(), void (*updateFnc)(float));
		float getDeltaTime();

	private:
		float m_DeltaTime = 1;
		Input::Keyboard* m_Keyboard = nullptr;

		// Settings
		bool m_EnableVSync = true;

		void setup();
		void debugUI(GLFWwindow* window);
	};
}