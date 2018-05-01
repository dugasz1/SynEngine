#pragma once

#include <string>
#include "GL\glew.h"

namespace SynEngine {
	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

		GLint LocateUniform(std::string uniformName);
		GLuint id;
	private:
		
		

	};
}