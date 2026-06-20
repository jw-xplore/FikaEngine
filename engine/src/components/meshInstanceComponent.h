#include "core/component.h"
#include "renderer/resources/meshInstance.h"

class MeshInstanceComponent : public Component
{
private:
	MeshInstance* instance;

public:
	MeshInstanceComponent() {}

	/**
	 * @brief Adds MeshInstance into rendered on creation.
	 * @param meshRes Mesh reference.
	 * @param shader Shader reference.
	 */
	void setup(MeshResource& meshRes, ShaderResource& shader, TextureResource* texture);

	void setTexture(TextureResource& texture) { instance->setTexture(&texture); }
};