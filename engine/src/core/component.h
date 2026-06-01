#pragma once

class GameObject;

class Component
{
public:
	GameObject* owner;

	Component() {}
	virtual ~Component() {}

	virtual void start() {}
	virtual void update(float dt) {}
	virtual void deallocate() {};
};