#include "..\..\include\SynEngine\Core\ShaderProgram.hpp"

SynEngine::ShaderProgram::ShaderProgram()
{
}

SynEngine::ShaderProgram::~ShaderProgram()
{
}

GLint SynEngine::ShaderProgram::LocateUniform(std::string uniformName)
{
	GLint uniformId = glGetUniformLocation(this->id, uniformName.c_str());
	if (uniformId < 0) {
		printf("ERROR: Can't find unifrom: %s\n", uniformName.c_str());
		return false;
	}
	printf("Uniform founded: %d | %s\n", uniformId, uniformName.c_str());
	return uniformId;
}
