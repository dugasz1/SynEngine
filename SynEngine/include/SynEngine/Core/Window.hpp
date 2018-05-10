#pragma once

#include <iostream>
#include "GLFW/glfw3.h"
#include "../Util/CommonDefs.hpp"

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
		const Mat4& GetProjectionMatrix() const;
	private:
		GLFWwindow * glfwWindow;
		Mat4 projectionMatrix;
	};
}