#include "scenegraph.h"
/*
SceneGraph::SceneGraph()
{
	rootNodes = new PoolAllocator<Node>("Scene root", 256);
	childNodes = new PoolAllocator<Node>("Scene child", 256);
}

void SceneGraph::update()
{
	// TODO
	for (size_t i = 0; i < rootNodes->getUsedAmount(); i++)
	{
		Node& node = (*rootNodes)[i];
		updateNode(node);
	}
}

void SceneGraph::updateNode(Node& node)
{
	GameObject* go = node.gameObject;

	for (auto& child : node.children)
	{
		updateNode(*child);
	}
}

void SceneGraph::setParent(GameObject* go, GameObject* parent)
{
	// Remove parent case
	if (!parent)
	{
		removeParent(go);
		return;
	}

	Node* parentNode;

	// Parent node exists?
	if (nodes.find(parent) == nodes.end())
	{
		// Add missing parent
		parentNode = rootNodes->allocate();
		nodes.insert(std::pair(parent, parentNode));
	}
	else
	{
		parentNode = nodes[parent];
	}
	
	Node* node;

	// Target node exists?
	if (nodes.find(go) == nodes.end())
	{
		node = childNodes->allocate();
		nodes.insert(std::pair(parent, node));
	}
	else
	{
		node = nodes[go];
	}

	// Link node
	node->parent = parentNode;
	parentNode->children.push_back(node);
}

void SceneGraph::removeParent(GameObject* go)
{
	if (nodes.find(go) == nodes.end())
		return;

	Node* node = nodes[go];
	if (!node->parent)
		return;


	// Has children?
	if (!node->children.empty())
	{
		// Move to root nodes
		nodes[go] = rootNodes->allocate();
		nodes[go]->children = node->children;
		childNodes->remove(node);
		return;
	}

	// Else - remove from scene graph
	nodes[go] = nullptr;
}

void SceneGraph::addChild(GameObject* go, GameObject* child)
{
	setParent(child, go);
}
*/