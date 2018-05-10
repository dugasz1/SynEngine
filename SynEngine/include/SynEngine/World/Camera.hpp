#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../Util/CommonDefs.hpp"

namespace SynEngine {
	class Camera
	{
	public:
		Camera();
		~Camera();

		void TestRotate(float& i);
		void Rotate(glm::vec3& rotation);
		void SetPosition(glm::vec3 position);
		void SetRotation(glm::quat rotation);
		const Mat4& GetViewMatrix();
	private:
		Mat4 transformation;

		glm::quat rotation;
		glm::vec3 position;
		glm::vec3 scale;

		void CalculateTransformation();
	};

}