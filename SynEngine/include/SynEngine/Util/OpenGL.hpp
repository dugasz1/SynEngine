#pragma once

#include "..\Core\Object.hpp"

namespace SynEngine {
	class OpenGL
	{
	public:
		bool LoadObject(Object* object);
	private:
		OpenGL();
		~OpenGL();
	};


}