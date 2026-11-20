#include <fika_engine.h>
#include "../components/player_component.h"
#include "../components/enemy_component.h"
#include "../components/health_component.h"

class Character
{
private:
	Body* body;
	RigidBodyComponent* rbCmp;
	float speed = 500;
	glm::vec3 lastDirection = glm::vec3(-1, 0, 0);
	glm::vec3 cameraOffset = glm::vec3(0, 2, 10);

	// Components
	MeshComponent* meshCmp = nullptr;
	MeleeComponent* meleeCmp = nullptr;
	SpritesheetComponent* spritesheetCmp = nullptr;
	HealthComponent* healthCmp = nullptr;

	void onDeath(Entity& entity);

public:
	void init(Entity& owner);
};