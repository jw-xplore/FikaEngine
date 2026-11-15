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

    // Add test sound
    FikaServers::getAudioManager().loadSound("test", "assets/sfx/tone_c.wav");
    FikaServers::getAudioManager().loadSound("melody", "assets/sfx/short_melody.wav");

    // Play test music
    FikaServers::getAudioManager().loadStreamable("testmusic", "assets/sfx/music.mp3");
    ma_sound* music = FikaServers::getAudioManager().playStreamable("testmusic");
    ma_sound_set_volume(music, 0.05f);
}

float idk = 0;

void PlayerComponent::update(float dt)
{
    idk += dt;
    //FikaServers::getCameraManager().getMainCamera()->rotate(dt, 0);

    float fp = FikaServers::getInputManager().isKeyHeld(Key::W) * -1;
    float fn = FikaServers::getInputManager().isKeyHeld(Key::S);
    float forward = fp + fn;

    float rp = FikaServers::getInputManager().isKeyHeld(Key::D);
    float rn = FikaServers::getInputManager().isKeyHeld(Key::A) * -1;
    float right = rp + rn;

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

    // Play test sound
    if (FikaServers::getInputManager().isKeyPressed(Key::Space))
    {
        ma_sound* sound = FikaServers::getAudioManager().getSound("test");
        //FikaServers::getAudioManager().playSound(*sound);

        FikaServers::getAudioManager().playfromAudioSource(*sound, glm::vec3(0, 0, 0));
    }

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
