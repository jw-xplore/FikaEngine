#include "fika_servers.h"

FikaServers* FikaServers::instance = new FikaServers();

FikaServers::FikaServers()
{

}

FikaServers::~FikaServers()
{

}

void FikaServers::init()
{
	ecsManager.init();
	gameResourceManager.init();
}