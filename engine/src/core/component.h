#pragma once
#include <iostream>
#include <string>

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


	size_t componentID() const { return typeid(*this).hash_code(); }

	void Serialize();

	void Deserialize(void* data)
	{
		Component* cmpData = reinterpret_cast<Component*>(data);
		//std::cout << "size code check: " << typeid(*cmpData).hash_code() << "\n";
		std::cout << "size: " << sizeof(*cmpData) << "\n";

	}
};