#include "systemsHolder.h"
#include "renderer/renderer.h"

SystemsHolder* SystemsHolder::instance = new SystemsHolder();

SystemsHolder::SystemsHolder()
{
	mainRenderer = std::unique_ptr<Renderer>(new Renderer());
}

SystemsHolder::~SystemsHolder()
{

}