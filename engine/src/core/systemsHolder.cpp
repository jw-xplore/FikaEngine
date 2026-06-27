#include "systemsHolder.h"
#include "renderer/renderer.h"
#include "physics/physics.h"
#include "core/gameobjectmanager.h"

SystemsHolder* SystemsHolder::instance = new SystemsHolder();

SystemsHolder::SystemsHolder()
{
	renderer = std::unique_ptr<Renderer>(new Renderer());
	debugRenderer = std::unique_ptr<Renderer>(new Renderer());
	physicsSolver = std::unique_ptr<PhysicsSolver>(new PhysicsSolver());
	gameObjectManager = std::unique_ptr<GameObjectManager>(new GameObjectManager());
}

SystemsHolder::~SystemsHolder()
{

}