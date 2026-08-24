#pragma once
#include "core/gameobject.h"
#include "core/memorymanagement.h"
#include <vector>
#include <map>

struct Node
{
	glm::mat4 globalTransform = glm::mat4(1.0f);
	GameObject* gameObject = nullptr;
	Node* parent = nullptr;
	std::vector<Node*> children;

	Node(GameObject* go)
	{
		gameObject = go;
	}
};

class SceneGraph
{
private:
	std::map<GameObject*, Node*> nodes;
	//PoolAllocator<Node>* rootNodes;
	//PoolAllocator<Node>* childNodes;

public:
	SceneGraph();

	void update();
	void updateNode(Node& node);

	void setParent(GameObject* go, GameObject* parent);
	void removeParent(GameObject* go);
	void addChild(GameObject* go, GameObject* child);
};