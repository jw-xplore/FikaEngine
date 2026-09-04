#include "RigidBodyComponent.h"
#include "core/systemsHolder.h"
#include "core/ecs/ecsmanager.h"
#include "core/ecs/ecsentity.h"
#include "physics/physics.h"
#include "physics/collisions.h"
#include "core/transform.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void RigidBodyComponent::start()
{
	PhysicsSolver* physics = SystemsHolder::getPhysicsSolver();
	body = &physics->addBody();

	/*
	// Callbacks
	body->onEnter = std::bind(&RigidbodyComponent::onEnter, this, std::placeholders::_1);
	body->onExit = std::bind(&RigidbodyComponent::onExit, this, std::placeholders::_1);
	*/
}

void RigidBodyComponent::update(float dt)
{

}

nlohmann::json RigidBodyComponent::serialize()
{
	nlohmann::json js = nlohmann::json::object();
	js["id"] = componentId;
	js["transform"] = body->transform.serialize();

	return js;
}

void RigidBodyComponent::deserialize(nlohmann::json js)
{
	nlohmann::json jsonPos = js["position"];
	glm::vec3 pos = glm::vec3(0);
	pos.x = jsonPos["x"];
	pos.y = jsonPos["y"];
	pos.z = jsonPos["z"];

	body->transform.setLocalPosition(pos);
}

Transform* RigidBodyComponent::getTransform()
{
	return &body->transform;
}

void RigidBodyComponent::setSphereCollider(float radius)
{
	SystemsHolder::getPhysicsSolver()->getCollisionSolver().addSphereCollider(*body, radius);
	//SystemsHolder::getPhysicsSolver()->getCollisionSolver().addBoxCollider(*body, glm::vec3(radius * 2));
	//SystemsHolder::getPhysicsSolver()->getCollisionSolver().addCapsuleCollider(*body, 0.5, 1);
}

void RigidBodyComponent::setType(EBodyType type)
{
	body->type = type;
}

//-------------------------------------------------------
// System
//-------------------------------------------------------

RigidBodyComponentUpdater::RigidBodyComponentUpdater()
{
}

void RigidBodyComponentUpdater::init()
{
	RigidBodyComponentUpdater* updater = new RigidBodyComponentUpdater();
	updater->components = new PoolAllocator<RigidBodyComponent>("RigidBody Components");
	updater->targetComponentId = RigidBodyComponent::componentId;

	SystemsHolder::getECSManager()->registerUpdaters(updater);
}

void RigidBodyComponentUpdater::update(float dt)
{
	int size = components->getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		(*components)[i].update(dt);
	}
}

FikaECS::ECSComponent* RigidBodyComponentUpdater::addComponent()
{
	return components->allocate();
}
