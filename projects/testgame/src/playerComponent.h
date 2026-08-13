#include"fikaEngine.h"

class PlayerComponent : public Component
{
private:
	RigidbodyComponent* rb;
	float speed = 4;
	glm::vec3 lastDirection = glm::vec3(-1,0,0);

public:
	void start() override;
	void update(float dt) override;
};