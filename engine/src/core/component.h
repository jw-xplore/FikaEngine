#pragma once

class GameObject;

class Component
{
public:
	GameObject* owner;

	Component() {}
	virtual ~Component() {}

	/**
	 * @brief Called when Component is added.
	 */
	virtual void start() {}

	/**
	 * @brief Called each frame.
	 * @param dt 
	 */
	virtual void update(float dt) {}
};