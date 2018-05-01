#include "../../include/SynEngine/Core/Window.hpp"

SynEngine::Window::Window()
{
	glfwWindow = glfwCreateWindow(1280, 720, "Teszt", NULL, NULL);

	glfwMakeContextCurrent(glfwWindow);
}

SynEngine::Window::~Window()
{
}

bool SynEngine::Window::Init()
{
	if (!glfwInit()) {
		printf("GLFW failed to initialize!\n");
		return false;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	return true;
}

void SynEngine::Window::SwapBuffers()
{
	glfwSwapBuffers(glfwWindow);
}

void SynEngine::Window::WindowLoop()
{
	glfwPollEvents();
}

bool SynEngine::Window::GetWindowShouldClose()
{
	return glfwWindowShouldClose(glfwWindow);
}

void SynEngine::Window::SetWindowShouldClose(int value)
{
	glfwSetWindowShouldClose(glfwWindow, value);
}