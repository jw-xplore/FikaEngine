#include"fikaEngine.h"

class PlayerComponent : public Component
{
private:
	RigidbodyComponent* rb;
	float speed = 4;

public:
	void start() override;
	void update(float dt) override;
};