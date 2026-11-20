#include "character.h"

void Character::init(Entity& owner)
{
    // Setup components
    rbCmp = static_cast<RigidBodyComponent*>(FikaServers::getECSManager().findComponent(owner, RigidBodyComponent::componentId));
    body = rbCmp->getBody();

    meleeCmp = static_cast<MeleeComponent*>(FikaServers::getECSManager().findComponent(owner, MeleeComponent::componentId));
    spritesheetCmp = static_cast<SpritesheetComponent*>(FikaServers::getECSManager().findComponent(owner, SpritesheetComponent::componentId));
    meshCmp = static_cast<MeshComponent*>(FikaServers::getECSManager().findComponent(owner, MeshComponent::componentId));

    healthCmp = static_cast<HealthComponent*>(FikaServers::getECSManager().findComponent(owner, HealthComponent::componentId));
    healthCmp->onDeath.addListener([this](Entity& entity) { onDeath(entity); });
}

void Character::onDeath(Entity& entity)
{
    FikaServers::getECSManager().removeEntity(entity);
}