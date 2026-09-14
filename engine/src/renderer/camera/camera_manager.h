#pragma once
#include "camera.h"

namespace FikaEngine
{
	class Window;

	class CameraManager
	{
	private:
		Camera mainCamera;
		Camera freeCamera;

		Camera* activeCamera;
		bool usingFreeCamera = false;

	public:
		CameraManager();
		~CameraManager();

		void init(Window& window);
		Camera* getActiveCamera();
		void useFreeCamera(bool use);
		bool isUsingFreeCamera();

		Camera* getMainCamera();
		Camera* getFreeCamera();
	};
} // namespace FikaEngine
