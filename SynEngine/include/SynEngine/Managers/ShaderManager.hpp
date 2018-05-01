#pragma once

#include <string>
#include "GL\glew.h"
#include "..\Core\Shader.hpp"

namespace SynEngine {
	class ShaderManager
	{
	public:
		ShaderManager();
		~ShaderManager();

		Shader* LoadShader(std::string filePath, GLenum shaderType);
		
	private:

	};
}