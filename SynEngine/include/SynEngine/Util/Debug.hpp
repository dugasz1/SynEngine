#pragma once

#include "Log.hpp"
#include "GL\glew.h"

#ifdef _MSC_VER
#include <intrin.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#endif // !_MSC_VER

#define GLDebugCall(x) GLClearErrors();x;GLLogErrors(#x, __FILE__, __LINE__);

#define DebugLog(x) SynEngine::Engine::log->Stream() << x

namespace SynEngine {
	class Debug
	{
	public:
		Debug();
		~Debug();

	private:
		static void openGLDebugCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam);
	};

}