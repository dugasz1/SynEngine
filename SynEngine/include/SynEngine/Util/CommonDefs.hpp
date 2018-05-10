#pragma once

#include <memory>
#include "glm/glm.hpp"
#include <filesystem>

#define interface class

namespace SynEngine{

	namespace fs = std::experimental::filesystem;

	typedef glm::vec3 Vec3;
	typedef glm::vec2 Vec2;
	typedef glm::mat4 Mat4;

	template <class T>
	using sPtr = std::shared_ptr<T>;
	template <class T>
	using wPtr = std::weak_ptr<T>;
	template <class T>
	using uPtr = std::unique_ptr<T>;
}

