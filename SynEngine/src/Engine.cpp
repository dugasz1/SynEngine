#include "..\include\SynEngine\Engine.hpp"

SynEngine::Engine::Engine()
{
	time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	tick = 0;


	SynEngine::Window::Init();
	window = SynEngine::Window();

	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		printf("ERROR: %s\n", glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*SynEngine::Camera SynEngine::Engine::camera;*/


}

SynEngine::Engine::~Engine()
{
}

void SynEngine::Engine::MainLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderManager->RenderAll();

	window.SwapBuffers();
	window.WindowLoop();


	time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	tick++;
}

const SynEngine::Window & SynEngine::Engine::GetWindow()
{
	return window;
}

const std::chrono::microseconds & SynEngine::Engine::GetTime()
{
	// TODO: insert return statement here
	return time;
}

const std::uint64_t& SynEngine::Engine::GetTick()
{
	return tick;
}

void SynEngine::Engine::Init()
{
	objectManager = new SynEngine::ObjectManager();
	materialManager = new SynEngine::MaterialManager();
	textureManager = new SynEngine::TexutreManager();
	shaderManager = new SynEngine::ShaderManager();
	shaderProgramManager = new SynEngine::ShaderProgramManager();
	renderManager = new SynEngine::RenderManager();
	log = new SynEngine::Log();

	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
}


SynEngine::Engine* SynEngine::Engine::I = new SynEngine::Engine();

//SynEngine::Camera SynEngine::Engine::camera;
//
//SynEngine::ObjectManager* SynEngine::Engine::objectManager = new SynEngine::ObjectManager();
//SynEngine::MaterialManager* SynEngine::Engine::materialManager = new SynEngine::MaterialManager();
//SynEngine::TexutreManager* SynEngine::Engine::textureManager = new SynEngine::TexutreManager();
//SynEngine::ShaderManager* SynEngine::Engine::shaderManager = new SynEngine::ShaderManager();
//SynEngine::ShaderProgramManager* SynEngine::Engine::shaderProgramManager = new SynEngine::ShaderProgramManager();
//SynEngine::RenderManager* SynEngine::Engine::renderManager = new SynEngine::RenderManager();
//SynEngine::Log* SynEngine::Engine::log = new SynEngine::Log();