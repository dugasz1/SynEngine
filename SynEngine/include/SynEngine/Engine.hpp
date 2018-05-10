#pragma once
#include <iostream>
#include <chrono>
#include <cstdint>
#include "GL/glew.h"
#include "Managers/ObjectManager.hpp"
#include "Managers/MaterialManager.hpp"
#include "Managers/TextureManager.hpp"
#include "Managers/ShaderManager.hpp"
#include "Managers/ShaderProgramManager.hpp"
#include "Managers/RenderManager.hpp"
#include "Core/Window.hpp"
#include "World/Camera.hpp"

namespace SynEngine {
	class Engine
	{
	public:
		Engine();
		~Engine();
		void Init();

		void MainLoop();

		const Window& GetWindow();
		const std::chrono::microseconds& GetTime();
		const std::uint64_t& GetTick();


		static Engine* I;

		Camera camera;

		ObjectManager* objectManager;
		MaterialManager* materialManager;
		TexutreManager* textureManager;
		ShaderManager* shaderManager;
		ShaderProgramManager* shaderProgramManager;
		class RenderManager* renderManager;
		Log* log;
	private:
		

		std::chrono::microseconds time;
		std::uint64_t tick;
		SynEngine::Window window;
		
	};
}