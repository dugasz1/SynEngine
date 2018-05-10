#include "../../include/SynEngine/Core/Window.hpp"
#include "glm/glm.hpp"
#include <glm\gtc\matrix_transform.hpp>

SynEngine::Window::Window()
{
	glfwWindow = glfwCreateWindow(1280, 720, "Teszt", NULL, NULL);

	glfwMakeContextCurrent(glfwWindow);

	projectionMatrix = glm::perspective<float>(glm::radians(90.0f), (1280.0f / 720.0f), 0.1f, 100.f);
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

const SynEngine::Mat4 & SynEngine::Window::GetProjectionMatrix() const
{
	return projectionMatrix;
}
