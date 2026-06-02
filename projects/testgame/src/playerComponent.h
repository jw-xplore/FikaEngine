#include"fikaEngine.h"

class PlayerComponent : public Component
{
private:
	MeshInstance* meshInstance;
	float speed = 4;

public:
	void start() override;
	void update(float dt) override;
};