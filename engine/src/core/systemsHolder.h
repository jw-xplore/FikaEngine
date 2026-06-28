#pragma once
#include <memory>

class Renderer;
class PhysicsSolver;
class GameObjectManager;
class CameraManager;

class SystemsHolder
{
private:
	static SystemsHolder* instance;

	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Renderer> debugRenderer; // Renders helper meshes
	std::unique_ptr<PhysicsSolver> physicsSolver;
	std::unique_ptr<GameObjectManager> gameObjectManager;
	std::unique_ptr<CameraManager> cameraManager;

public:
	SystemsHolder();
	~SystemsHolder();

	Renderer* getMainRenderer() { return renderer.get(); }
	Renderer* getDebugRenderer() { return debugRenderer.get(); }
	PhysicsSolver* getMainPhysicsSolver() { return physicsSolver.get(); }
	GameObjectManager* getGameObjectManager() { return gameObjectManager.get(); }
	CameraManager* getCameraManager() { return cameraManager.get(); }

	static SystemsHolder* getInstance()
	{
		if (!instance)
			instance = new SystemsHolder();

		return instance;
	}
};