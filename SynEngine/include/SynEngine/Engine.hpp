#pragma once
#include <iostream>
#include <chrono>
#include <cstdint>
#include "GL\glew.h"
#include "Managers\ObjectManager.hpp"
#include "Managers\MaterialManager.hpp"
#include "Managers\TextureManager.hpp"
#include "Managers\ShaderManager.hpp"
#include "Managers\ShaderProgramManager.hpp"
#include "Managers\RenderManager.hpp"
#include "Core\Window.hpp"

namespace SynEngine {
	class Engine
	{
	public:
		Engine();
		~Engine();

		void MainLoop();

		const std::chrono::microseconds& GetTime();
		const std::uint64_t& GetTick();

		static bool Init();

		static ObjectManager* objectManager;
		static MaterialManager* materialManager;
		static TexutreManager* textureManager;
		static ShaderManager* shaderManager;
		static ShaderProgramManager* shaderProgramManager;
		static class RenderManager* renderManager;
		static Log* log;
	private:
		
		std::chrono::microseconds time;
		std::uint64_t tick;
		SynEngine::Window window;
	};
}