#include "player_component.h"
#include "core/fika_servers.h"
#include "core/ecs/ecs_manager.h"
#include "core/ecs/entity.h"

const unsigned int PlayerComponent::componentId;

//-------------------------------------------------------
// Component
//-------------------------------------------------------

void PlayerComponent::start()
{
	//transform = FikaServers::getECSManager().findEntityTransform(*owner);
    rbCmp = static_cast<RigidBodyComponent*>(FikaServers::getECSManager().findComponent(*owner, RigidBodyComponent::componentId));
    body = rbCmp->getBody();

    FikaServers::getCameraManager().getMainCamera()->rotate(180, -10);
}

void PlayerComponent::update(float dt)
{
    InputManager& inputMngr = FikaServers::getInputManager();

    // Keyboard movemnet
    float fp = inputMngr.isKeyHeld(Key::W) * -1;
    float fn = inputMngr.isKeyHeld(Key::S);
    float forward = fp + fn;

    float rp = inputMngr.isKeyHeld(Key::D);
    float rn = inputMngr.isKeyHeld(Key::A) * -1;
    float right = rp + rn;

    // Gamepad movement
    if (forward == 0)
    {
        forward = inputMngr.getGamepadAxis(Gamepad::LS_Vertical);
    }

    if (right == 0)
    {
        right = inputMngr.getGamepadAxis(Gamepad::LS_Horizontal);
    }

    if (forward != 0 || right != 0)
        lastDirection = glm::vec3(right, 0, forward);

    glm::vec3 velocity = glm::vec3(right, 0, forward) * speed;
    body->velocity = velocity * dt;

    // Test raycast
    const float l = 2.0f;

    glm::vec3 pos = body->transform.getLocalPosition();

    glm::vec3 rayColor = glm::vec3(1, 0, 0);
    bool hit = FikaServers::getPhysicsSolver().getCollisionSolver().raycast(pos, lastDirection, l);
    if (hit)
        rayColor = glm::vec3(0, 1, 0);

    FikaServers::getDebugRenderer().addLine(Line(pos, pos + lastDirection * l * glm::length(lastDirection), rayColor));

    // Cam move
    FikaServers::getCameraManager().getMainCamera()->setPosition(pos + cameraOffset);

    // Update sound listener
    FikaServers::getAudioManager().setListenerPosition(pos);
}

nlohmann::json PlayerComponent::serialize()
{
    nlohmann::json js = nlohmann::json::object();
    js["id"] = componentId;

    return js;
}

void PlayerComponent::deserialize(nlohmann::json js)
{

}

//-------------------------------------------------------
// System
//-------------------------------------------------------

PlayerComponentUpdater::PlayerComponentUpdater()
{
}

void PlayerComponentUpdater::init(size_t poolSize)
{
	PlayerComponentUpdater* updater = new PlayerComponentUpdater();
    updater->components.init("Player Components", poolSize);
	updater->targetComponentId = PlayerComponent::componentId;

	FikaServers::getECSManager().registerUpdaters(updater);
}

void PlayerComponentUpdater::update(float dt)
{
	int size = components.getUsedAmount();

	for (size_t i = 0; i < size; i++)
	{
		components[i].update(dt);
	}
}

ECSComponent* PlayerComponentUpdater::addComponent()
{
	return components.allocate();
}

void PlayerComponentUpdater::removeComponent(ECSComponent& component)
{
    PlayerComponent* casted = static_cast<PlayerComponent*>(&component);
    assert(casted != nullptr);
    components.remove(casted);
}
