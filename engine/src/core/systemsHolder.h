#pragma once
#include <memory>

class Renderer;
//class PhysicsSolver;
class GameObjectManager;
class CameraManager;
class GResourceManager;

namespace FikaECS
{
	class ECSManager;
}

class SystemsHolder
{
private:
	static SystemsHolder* instance;

	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Renderer> debugRenderer; // Renders helper meshes
	//std::unique_ptr<PhysicsSolver> physicsSolver;
	std::unique_ptr<CameraManager> cameraManager;
	std::unique_ptr<GResourceManager> gResourceManager;

	std::unique_ptr<FikaECS::ECSManager> ecsManager;

public:
	SystemsHolder();
	~SystemsHolder();

	static SystemsHolder* getInstance()
	{
		if (!instance)
			instance = new SystemsHolder();

		return instance;
	}

	static Renderer* getMainRenderer() { return SystemsHolder::getInstance()->renderer.get(); }
	static Renderer* getDebugRenderer() { return SystemsHolder::getInstance()->debugRenderer.get(); }
	static CameraManager* getCameraManager() { return SystemsHolder::getInstance()->cameraManager.get(); }
	static GResourceManager* getGResourceManager() { return SystemsHolder::getInstance()->gResourceManager.get(); }
	//static PhysicsSolver* getPhysicsSolver() { return SystemsHolder::getInstance()->physicsSolver.get(); }
	static FikaECS::ECSManager* getECSManager() { return SystemsHolder::getInstance()->ecsManager.get(); }
};