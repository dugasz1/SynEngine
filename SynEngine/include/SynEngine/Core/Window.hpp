#pragma once

#include "GLFW\glfw3.h"
#include <iostream>

namespace SynEngine {
	class Window
	{
	public:
		Window();
		~Window();
		
		static bool Init();
		void SwapBuffers();


		void WindowLoop();
		bool GetWindowShouldClose();
		void SetWindowShouldClose(int value);
	private:
		GLFWwindow * glfwWindow;
	};
}