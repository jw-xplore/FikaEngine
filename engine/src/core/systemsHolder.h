#pragma once
#include <memory>

class Renderer;
class PhysicsSolver;

class SystemsHolder
{
private:
	static SystemsHolder* instance;
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<PhysicsSolver> physicsSolver;

public:
	SystemsHolder();
	~SystemsHolder();

	Renderer* getMainRenderer() { return renderer.get(); }
	PhysicsSolver* getMainPhysicsSolver() { return physicsSolver.get(); }

	static SystemsHolder* getInstance()
	{
		if (!instance)
			instance = new SystemsHolder();

		return instance;
	}
};