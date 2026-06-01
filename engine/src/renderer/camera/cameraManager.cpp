#include "cameraManager.h"
#include "camera.h"

namespace CameraManager
{
	Camera mainCamera;
	Camera freeCamera;

	Camera* getMainCamera()
	{
		return &mainCamera;
	}

	Camera* getFreeCamera()
	{
		return &freeCamera;
	}
}