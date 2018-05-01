#include "../../include/SynEngine/Util/Log.hpp"

SynEngine::Log::Log()
{
}

SynEngine::Log::~Log()
{
}

void SynEngine::Log::Error(std::string msg)
{
	std::cout << msg << std::endl;
}


void SynEngine::Log::Warn(std::string msg)
{
	std::cout << msg << std::endl;
}

void SynEngine::Log::Info(std::string msg)
{
	std::cout << msg << std::endl;
}

