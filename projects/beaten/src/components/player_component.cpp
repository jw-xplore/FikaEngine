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
    FikaServers::getCameraManager().getMainCamera()->rotate(180, -10);

    // Setup components
    rbCmp = static_cast<RigidBodyComponent*>(FikaServers::getECSManager().findComponent(*owner, RigidBodyComponent::componentId));
    body = rbCmp->getBody();

    meleeCmp = static_cast<MeleeComponent*>(FikaServers::getECSManager().findComponent(*owner, MeleeComponent::componentId));
    spritesheetCmp = static_cast<SpritesheetComponent*>(FikaServers::getECSManager().findComponent(*owner, SpritesheetComponent::componentId));
    meshCmp = static_cast<MeshComponent*>(FikaServers::getECSManager().findComponent(*owner, MeshComponent::componentId));
}

void PlayerComponent::update(float dt)
{
    //InputManager& inputMngr = FikaServers::getInputManager();

    movement(dt);
    attack(dt);
    animationHandling(dt);

    glm::vec3 pos = body->transform.getLocalPosition();

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

void PlayerComponent::movement(float dt)
{
    InputManager& inputMngr = FikaServers::getInputManager();
    const float inputTreshold = 0.05f;

    // Keyboard
    float fp = inputMngr.isKeyHeld(Key::W) * -1;
    float fn = inputMngr.isKeyHeld(Key::S);
    float forward = fp + fn;

    float rp = inputMngr.isKeyHeld(Key::D);
    float rn = inputMngr.isKeyHeld(Key::A) * -1;
    float right = rp + rn;

    // Gamepad
    if (forward == 0)
    {
        forward = inputMngr.getGamepadAxis(Gamepad::LS_Vertical);
    }

    if (right == 0)
    {
        right = inputMngr.getGamepadAxis(Gamepad::LS_Horizontal);
    }

    // Apply movement
    if (abs(forward) > inputTreshold || abs(right) > inputTreshold)
    {
        lastDirection = glm::vec3(right, 0, forward);
    }
    else
    {
        forward = 0;
        right = 0;
    }

    glm::vec3 velocity = glm::vec3(right, 0, forward) * speed;
    body->velocity = velocity * dt;

    // Attack direction
    if (right > inputTreshold)
    {
        meleeCmp->setDirection(glm::vec3(1, 0, 0));
        meshCmp->getMeshInstance()->customScale = glm::vec3(1, 1, 1);
    }
    else if (right < -inputTreshold)
    {
        meleeCmp->setDirection(glm::vec3(-1, 0, 0));
        meshCmp->getMeshInstance()->customScale = glm::vec3(-1, 1, 1);
    }
}

void PlayerComponent::attack(float dt)
{
    InputManager& inputMngr = FikaServers::getInputManager();

    // Keyboard
    bool attackInput = inputMngr.isKeyPressed(Key::Space);

    // Gamepad
    if (!attackInput)
    {
        attackInput = inputMngr.isGamepadButtonPressed(Gamepad::A);
    }

    // Start attack
    if (attackInput)
    {
        spritesheetCmp->setAnimationTime(0.0f);
        meleeCmp->startAttack();
    }
}

void PlayerComponent::animationHandling(float dt)
{
    // Attack
    if (meleeCmp->getCurrentAttack() == 0)
    {
        spritesheetCmp->selectAnimation("attack");
        return;
    }
    else if (meleeCmp->getCurrentAttack() == 1)
    {
        spritesheetCmp->selectAnimation("attack1");
        return;
    }

    // Movement
    if (body->velocity != glm::vec3(0.0f))
    {
        spritesheetCmp->selectAnimation("run");
    }
    else
    {
        spritesheetCmp->selectAnimation("idle");
    }
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
