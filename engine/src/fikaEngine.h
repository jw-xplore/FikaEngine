#pragma once
#include <functional>

/** FikaEngine
* This header gives access to full functionality of the engine.
*/

/*
Includes
*/

// Core
#include "core/gameobject.h"
#include "core/component.h"
#include "core/gameobjectmanager.h"

// Render
#include "renderer/renderer.h"
#include "renderer/resources/gResourceManager.h"
#include "renderer/resources/meshInstance.h"
#include "renderer/resources/meshBuilder.h"
#include "renderer/camera/cameraManager.h"
#include "renderer/camera/camera.h"

// Plaftorm
#include "platform/window.h"
#include "platform/inputs/inputdevices.h"
#include "platform/inputs/inputhandler.h"
#include "platform/inputs/inputmapping.h"

// External
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Components
#include "components/meshInstanceComponent.h"

/*
Engine
*/

/**
 * @brief Main engine namespace - Call run to initiate engine and game loop in your project.
 */
namespace FikaEngine
{
	/**
	 * @brief Create window, initialize engine and run game loop.
	 * @param startFnc Function for setting up custom project. Is called right before first game loop update.
	 * @param updateFnc Function for custom update. Is called every frame before render.
	 */
	void run(void (*startFnc)(), void (*updateFnc)(float));
}