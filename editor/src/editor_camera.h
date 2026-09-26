#pragma once
#include "renderer/camera/camera.h"
#include "platform/window.h";
#include <glm/glm.hpp>

using namespace FikaEngine;

namespace FikaEditor
{
	class EditorCamera
	{
	public:
		EditorCamera();
		EditorCamera(Camera* camera, Window* window);

		void update(float dt);
		void keyboardControl(float dt);
		void mouseControl(float dt);

	private:
		Window* window;
		Camera* camera;

		float speed = 5.0f;
		float minSpeed = 1.0f, maxSpeed = 20.0f, speedChange = 1.0f;
		float pitchLimit = 60.0f;
		float sensitivity = 0.5f;
	};
}