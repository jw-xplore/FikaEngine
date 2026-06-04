#include "cameraManager.h"
#include "camera.h"
#include "../../platform/window.h";

namespace CameraManager
{
	Camera mainCamera;
	Camera freeCamera;

	Camera* activeCamera;
	bool usingFreeCamera = false;

	void init(Window& window)
	{
		mainCamera = Camera(window);
		freeCamera = Camera(window);
		useFreeCamera(false);
	}

	Camera* getActiveCamera()
	{
		return activeCamera;
	}

	void useFreeCamera(bool use)
	{
		usingFreeCamera = use;

		if (use)
		{
			activeCamera = &freeCamera;
		}
		else
		{
			activeCamera = &mainCamera;
		}
	}

	bool isUsingFreeCamera()
	{
		return usingFreeCamera;
	}

	Camera* getMainCamera()
	{
		return &mainCamera;
	}

	Camera* getFreeCamera()
	{
		return &freeCamera;
	}
}