#include"fikaEngine.h"

class PlayerComponent : public Component
{
private:
	Input::Keyboard* keyboard;
	MeshInstance* meshInstance;
	float speed = 10;

public:
	void start() override;
	void update(float dt) override;
};