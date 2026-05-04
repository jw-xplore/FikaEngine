#pragma once

class GameObject;

class Component
{
public:
	GameObject* owner;

	Component() {}
	virtual ~Component() {}

	virtual void Start() {}
	virtual void Update(float dt) {}
	virtual void Deallocate() {};
};