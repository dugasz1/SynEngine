#pragma once

#include <memory>

#define interface class

namespace SynEngine{

	namespace fs = std::experimental::filesystem;

	template <class T>
	using sPtr = std::shared_ptr<T>;
	template <class T>
	using wPtr = std::weak_ptr<T>;
	template <class T>
	using uPtr = std::unique_ptr<T>;
}

