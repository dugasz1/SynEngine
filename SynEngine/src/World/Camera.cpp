#include "..\..\include\SynEngine\World\Camera.hpp"

SynEngine::Camera::Camera()
{
}

SynEngine::Camera::~Camera()
{
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
