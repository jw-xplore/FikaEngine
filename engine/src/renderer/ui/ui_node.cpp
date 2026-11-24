#include "ui_node.h"
#include "../../core/fika_servers.h"

namespace FikaEngine
{
	UINode::UINode()
	{

	}

	UINode::UINode(glm::vec2 position, glm::vec2 size, float rotation):
		position(position),
		size(size),
		rotation(rotation)
	{

	}

	UINode::~UINode()
	{

	}

	void UINode::createMesh()
	{
		//mesh.setMesh(FikaServers::getGPUResourceManager().getMesh("quad"));
	}
}