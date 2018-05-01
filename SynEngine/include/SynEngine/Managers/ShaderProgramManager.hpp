#pragma once

#include <string>
#include <map>
#include "..\Core\ShaderProgram.hpp"

namespace SynEngine {
	class ShaderProgramManager
	{
	public:
		ShaderProgramManager();
		~ShaderProgramManager();

		ShaderProgram* LoadShaderProgram(std::string directoryPath, std::string shaderProgramName);
	private:
		static const std::map<GLenum, std::string> shaderTypeExtension;
		static std::map<GLenum, std::string> InitShaderTypeExtensions();

	};
}