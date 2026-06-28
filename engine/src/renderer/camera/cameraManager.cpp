#include "cameraManager.h"
#include "platform/window.h";

CameraManager::CameraManager()
{

}

CameraManager::~CameraManager()
{

}

void CameraManager::init(Window& window)
{
	mainCamera = Camera(window);
	freeCamera = Camera(window);
	useFreeCamera(false);
}

Camera* CameraManager::getActiveCamera()
{
	return activeCamera;
}

void CameraManager::useFreeCamera(bool use)
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

bool CameraManager::isUsingFreeCamera()
{
	return usingFreeCamera;
}

Camera* CameraManager::getMainCamera()
{
	return &mainCamera;
}

Camera* CameraManager::getFreeCamera()
{
	return &freeCamera;
}