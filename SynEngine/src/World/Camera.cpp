#include "../../include/SynEngine/World/Camera.hpp"
#include "glm/glm.hpp"

SynEngine::Camera::Camera()
{
	transformation = Mat4(1.0f);

	transformation = glm::translate(transformation, glm::vec3(0.0f, 0.0f, -7.0f));
}

SynEngine::Camera::~Camera()
{
	
}

void SynEngine::Camera::TestRotate(float & i)
{
	/*glm::fmat4 viewmatrix(1.0f);
	pos.z -= 0.1f;
	viewmatrix = glm::translate(viewmatrix, pos);
	viewmatrix = glm::rotate(viewmatrix, i, glm::vec3(0.0f, 1.0f, 0.0f));
	viewmatrix = glm::rotate(viewmatrix, 20.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	i += 0.01f;*/
}

void SynEngine::Camera::Rotate(glm::vec3 & rotation)
{
	glm::fmat4 viewmatrix(1.0f);
	viewmatrix = glm::translate(viewmatrix, glm::vec3(0.0f, 0.0f, -7.0f));
	//viewmatrix = glm::rotate(viewmatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	viewmatrix = glm::rotate(viewmatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	//viewmatrix = glm::rotate(viewmatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	transformation = viewmatrix;
}

const SynEngine::Mat4 & SynEngine::Camera::GetViewMatrix()
{
	return transformation;
}

void SynEngine::Camera::CalculateTransformation()
{
	transformation = glm::mat4(1.0f);

	//Scale
	glm::scale(transformation, scale);

	//Rotate
	glm::mat4 rotationMatrix = glm::toMat4(rotation);
	transformation = transformation * rotationMatrix;

	//Transform
	glm::translate(transformation, position);
}
