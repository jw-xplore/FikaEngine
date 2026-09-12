#include "rigidbody_component.h"
#include "core/fika_servers.h"
#include "core/ecs/ecs_manager.h"
#include "core/ecs/entity.h"
#include "physics/physics.h"
#include "physics/collisions.h"
#include "core/transform.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void RigidBodyComponent::start()
{
	PhysicsSolver& physics = FikaServers::getPhysicsSolver();
	body = &physics.addBody();

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
	js["type"] = body->type;
	js["shape"] = body->shape->serialize();
	js["tag"] = body->tag;
	js["layers"] = body->layers;
	js["interactiveLayers"] = body->interactiveLayers;

	return js;
}

void RigidBodyComponent::deserialize(nlohmann::json js)
{
	body->type = js["type"];
	body->transform.deserialize(js["transform"]);
	body->tag = js["tag"];
	body->layers = js["layers"];
	body->interactiveLayers = js["interactiveLayers"];

	int shapeType = js["shape"]["type"];
	nlohmann::json shapeJson = js["shape"];

	CollisionSolver& collisions = FikaServers::getPhysicsSolver().getCollisionSolver();

	switch (shapeType)
	{
	case EColliderShapes::ColliderShapeSphere: collisions.addSphereCollider(*body, shapeJson["radius"]); break;
	case EColliderShapes::ColliderShapeBox: collisions.addBoxCollider(*body, glm::vec3(shapeJson["x"], shapeJson["y"], shapeJson["z"])); break;
	case EColliderShapes::ColliderShapeCapsule: collisions.addCapsuleCollider(*body, shapeJson["radius"], shapeJson["height"]); break;
	}
}

Transform* RigidBodyComponent::getTransform()
{
	return &body->transform;
}

void RigidBodyComponent::setSphereCollider(float radius)
{
	FikaServers::getPhysicsSolver().getCollisionSolver().addSphereCollider(*body, radius);
	//FikaServers::getPhysicsSolver().getCollisionSolver().addBoxCollider(*body, glm::vec3(radius * 2));
	//FikaServers::getPhysicsSolver().getCollisionSolver().addCapsuleCollider(*body, 0.5, 1);
}

void RigidBodyComponent::setBoxCollider(glm::vec3 volume)
{
	FikaServers::getPhysicsSolver().getCollisionSolver().addBoxCollider(*body, volume);
}

void RigidBodyComponent::setCapsuleCollider(float radius, float height)
{
	FikaServers::getPhysicsSolver().getCollisionSolver().addCapsuleCollider(*body, radius, height);
}

void RigidBodyComponent::setType(EBodyType type)
{
	body->type = type;
}

void RigidBodyComponent::setLayers(unsigned int layers)
{
	body->layers = layers;
}

void RigidBodyComponent::setInteractiveLayers(unsigned int layers)
{
	body->interactiveLayers = layers;
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

	FikaServers::getECSManager().registerUpdaters(updater);
}

void RigidBodyComponentUpdater::update(float dt)
{
	int size = components->getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		(*components)[i].update(dt);
	}
}

ECSComponent* RigidBodyComponentUpdater::addComponent()
{
	return components->allocate();
}
