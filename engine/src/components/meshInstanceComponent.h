#include "../core/component.h"
#include "../renderer/resources/meshInstance.h"

class MeshInstanceComponent : public Component
{
private:
	MeshInstance* instance;

public:
	MeshInstanceComponent() {}
	MeshInstanceComponent(MeshResource& meshRes, ShaderResource& shader);
	void setup(MeshResource& meshRes, ShaderResource& shader);
	void start() override;
	void update(float dt) override;
};