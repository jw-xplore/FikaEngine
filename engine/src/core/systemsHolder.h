#pragma once
#include <memory>

class Renderer;

class SystemsHolder
{
private:
	static SystemsHolder* instance;
	std::unique_ptr<Renderer> mainRenderer;

public:
	SystemsHolder();
	~SystemsHolder();

	Renderer* getMainRenderer() { return mainRenderer.get(); }

	static SystemsHolder* getInstance()
	{
		if (!instance)
			instance = new SystemsHolder();

		return instance;
	}
};