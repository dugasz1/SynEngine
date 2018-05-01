#pragma once

#include "glm\glm.hpp"
#include "glm\gtx\quaternion.hpp"
#include "glm\gtc\matrix_transform.hpp"

namespace SynEngine {
	class Camera
	{
	public:
		Camera();
		~Camera();

		void SetPosition(glm::vec3 position);
		void SetRotation(glm::quat rotation);

	private:
		glm::fmat4 transformation;

		glm::quat rotation;
		glm::vec3 position;
		glm::vec3 scale;

		void CalculateTransformation();
	};

}