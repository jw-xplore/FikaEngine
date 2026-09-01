#include "systemsHolder.h"
#include "renderer/renderer.h"
#include "physics/physics.h"
#include "renderer/camera/cameraManager.h"
#include "renderer/resources/gResourceManager.h"
#include "core/ecs/ecsmanager.h"

SystemsHolder* SystemsHolder::instance = new SystemsHolder();

SystemsHolder::SystemsHolder()
{
	renderer = std::unique_ptr<Renderer>(new Renderer());
	debugRenderer = std::unique_ptr<Renderer>(new Renderer());
	physicsSolver = std::unique_ptr<PhysicsSolver>(new PhysicsSolver());
	cameraManager = std::unique_ptr<CameraManager>(new CameraManager());
	gResourceManager = std::unique_ptr<GResourceManager>(new GResourceManager());

	ecsManager = std::unique_ptr<FikaECS::ECSManager>(new FikaECS::ECSManager());
	ecsManager->init();
}

SystemsHolder::~SystemsHolder()
{

}