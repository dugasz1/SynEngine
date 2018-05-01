#include "..\..\include\SynEngine\Managers\ShaderManager.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::experimental::filesystem;

SynEngine::ShaderManager::ShaderManager()
{
}

SynEngine::ShaderManager::~ShaderManager()
{
}

SynEngine::Shader * SynEngine::ShaderManager::LoadShader(std::string filePath, GLenum shaderType)
{
	fs::path fsFile(filePath);
	std::error_code errorCode;
	/*if (fs::exists(fsFile) == false) {
		printf("File not exist: \n");
		return nullptr;
	}*/
	if (fs::is_directory(fsFile) == true) {
		printf("Can't load directory as a shader.\n");
		return nullptr;
	}

	GLuint shaderId = glCreateShader(shaderType);

	std::ifstream shaderStream;
	shaderStream.open(fsFile);
	if (shaderStream.fail()) {
		printf("Can't open file\n");
		return nullptr;
	}

	std::string shaderCode = std::string(std::istreambuf_iterator<char>(shaderStream), std::istreambuf_iterator<char>());
	const GLchar *sources[] = { shaderCode.c_str() };
	const GLint lenght[] =  { shaderCode.length() };
	glShaderSource(shaderId, 1, sources, lenght);

	glCompileShader(shaderId);

	GLint compileSuccess = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileSuccess);
	if (compileSuccess == GL_FALSE) {
		GLint logSize = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);
		GLchar* errorLog = new GLchar[logSize];
		glGetShaderInfoLog(shaderId, logSize, &logSize, errorLog);
		printf("Shader error: %s\n", errorLog);

		delete[] errorLog;
		glDeleteShader(shaderId);
		return nullptr;
	}
	else {
		printf("%s loaded successfully.\n", filePath.c_str());
	}
	Shader * shader = new Shader();
	shader->id = shaderId;

	return shader;
}