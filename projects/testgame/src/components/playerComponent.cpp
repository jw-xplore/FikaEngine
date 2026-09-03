#include "PlayerComponent.h"
#include "core/systemsHolder.h"
#include "core/ecs/ecsmanager.h"
#include "core/ecs/ecsentity.h"

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void PlayerComponent::start()
{
	//transform = SystemsHolder::getECSManager()->findEntityTransform(*owner);
    RigidBodyComponent* rbCmp = static_cast<RigidBodyComponent*>(SystemsHolder::getECSManager()->findComponent(*owner, RigidBodyComponent::componentId));
    body = rbCmp->getBody();
}

void PlayerComponent::update(float dt)
{
    InputMapping* input = InputMapping::GetInstance();
    float forward = input->getAction("Vertical")->inputAxis();
    float right = input->getAction("Horizontal")->inputAxis();

    if (forward != 0 || right != 0)
        lastDirection = glm::vec3(right, 0, forward);

    glm::vec3 velocity = glm::vec3(right, 0, forward) * speed;
    //transform->translate(velocity * dt);
    body->velocity = velocity * dt;

    // Test raycast
    const float l = 2.0f;

    glm::vec3 pos = body->transform.getLocalPosition();

    glm::vec3 rayColor = glm::vec3(1, 0, 0);
    bool hit = SystemsHolder::getPhysicsSolver()->getCollisionSolver().raycast(pos, lastDirection, l);
    if (hit)
        rayColor = glm::vec3(0, 1, 0);

    SystemsHolder::getDebugRenderer()->addLine(Line(pos, pos + lastDirection * l * glm::length(lastDirection), rayColor));
}


//-------------------------------------------------------
// System
//-------------------------------------------------------

PlayerComponentUpdater::PlayerComponentUpdater()
{
}

void PlayerComponentUpdater::init()
{
	PlayerComponentUpdater* updater = new PlayerComponentUpdater();
	updater->components = new PoolAllocator<PlayerComponent>("Player Components");
	updater->targetComponentId = PlayerComponent::componentId;

	SystemsHolder::getECSManager()->registerUpdaters(updater);
}

void PlayerComponentUpdater::update(float dt)
{
	int size = components->getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		(*components)[i].update(dt);
	}
}

FikaECS::ECSComponent* PlayerComponentUpdater::addComponent()
{
	return components->allocate();
}
