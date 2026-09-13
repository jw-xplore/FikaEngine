#include "fika_servers.h"

FikaServers* FikaServers::instance = new FikaServers();

FikaServers::FikaServers()
{

}

FikaServers::~FikaServers()
{

}

FikaServers* FikaServers::getInstance()
{
	if (!instance)
		instance = new FikaServers();

	return instance;
}

void FikaServers::init()
{
	ecsManager.init();
	gameResourceManager.init();
}