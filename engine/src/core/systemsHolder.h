#pragma once
#include <memory>

class Renderer;
class PhysicsSolver;
class GameObjectManager;
class CameraManager;
class GResourceManager;

class SystemsHolder
{
private:
	static SystemsHolder* instance;

	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Renderer> debugRenderer; // Renders helper meshes
	std::unique_ptr<PhysicsSolver> physicsSolver;
	std::unique_ptr<GameObjectManager> gameObjectManager;
	std::unique_ptr<CameraManager> cameraManager;
	std::unique_ptr<GResourceManager> gResourceManager;

public:
	SystemsHolder();
	~SystemsHolder();

	Renderer* getMainRenderer() { return renderer.get(); }
	PhysicsSolver* getMainPhysicsSolver() { return physicsSolver.get(); }
	GameObjectManager* getGameObjectManager() { return gameObjectManager.get(); }
	CameraManager* getCameraManager() { return cameraManager.get(); }
	GResourceManager* getGResourceManager() { return gResourceManager.get(); }

	static SystemsHolder* getInstance()
	{
		if (!instance)
			instance = new SystemsHolder();

		return instance;
	}

	static Renderer* getDebugRenderer() { return SystemsHolder::getInstance()->debugRenderer.get();  }
};