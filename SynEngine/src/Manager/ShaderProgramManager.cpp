#include "..\..\include\SynEngine\Managers\ShaderProgramManager.hpp"
#include "..\..\include\SynEngine\Engine.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::experimental::filesystem;

SynEngine::ShaderProgramManager::ShaderProgramManager()
{
}

SynEngine::ShaderProgramManager::~ShaderProgramManager()
{
}

SynEngine::ShaderProgram * SynEngine::ShaderProgramManager::LoadShaderProgram(std::string directoryPath, std::string shaderProgramName)
{
	std::vector<Shader*> shaders;
	for (auto & p : fs::directory_iterator(directoryPath)) {
		if (fs::is_directory(p.path()) == false) {
			for (std::map<GLenum, std::string>::const_iterator it = shaderTypeExtension.begin();
				it != shaderTypeExtension.end(); it++)
			{
				std::string shaderName = shaderProgramName;
				shaderName.append(it->second);
				if (shaderName.compare(p.path().filename().string()) == 0) {
					Shader* shader = Engine::shaderManager->LoadShader(p.path().string(), it->first);
					shaders.push_back(shader);
				}
			}

		}
		
	}

	GLuint programId = glCreateProgram();
	if (programId == 0) {
		printf("ERROR: glCreateProgram returned with 0");
		return nullptr;
	}

	for (auto& it : shaders)
	{
		glAttachShader(programId, it->id);
	}

	glLinkProgram(programId);

	GLint isLinked = 0;
	glGetProgramiv(programId, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		GLchar* errorLog = new GLchar[maxLength];
		glGetProgramInfoLog(programId, maxLength, &maxLength, errorLog);

		printf("ERROR: %s\n", errorLog);

		// We don't need the program anymore.
		glDeleteProgram(programId);

		return nullptr;
	}
	else {
		printf("%s linked successfully.\n", shaderProgramName.c_str());
	}

	ShaderProgram* shaderProgram = new ShaderProgram();
	shaderProgram->id = programId;

	return shaderProgram;
}


std::map<GLenum, std::string> SynEngine::ShaderProgramManager::InitShaderTypeExtensions()
{
	std::map<GLenum, std::string> m = {
		{GL_VERTEX_SHADER, ".vs"},
		{GL_FRAGMENT_SHADER, ".fs"},
		{GL_GEOMETRY_SHADER, ".gs"},
		{GL_TESS_CONTROL_SHADER, ".tcs"},
		{GL_TESS_EVALUATION_SHADER, ".tes"},
		{GL_COMPUTE_SHADER, ".cs"}
	};
	return m;
}

const std::map<GLenum, std::string> SynEngine::ShaderProgramManager::shaderTypeExtension =
	SynEngine::ShaderProgramManager::InitShaderTypeExtensions();
