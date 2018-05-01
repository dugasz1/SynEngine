#include "../../include/SynEngine/Util/Debug.hpp"
#include "../../include/SynEngine/Engine.hpp"

SynEngine::Debug::Debug()
{
	glDebugMessageCallback(SynEngine::Debug::openGLDebugCallback, nullptr);
}

SynEngine::Debug::~Debug()
{
}
void SynEngine::Debug::openGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam)
{
	SynEngine::Engine::log->Error("-------OPENGL Debug-------");
	SynEngine::Engine::log->Error(std::to_string(id));
	SynEngine::Engine::log->Error(message);
}