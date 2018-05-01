#pragma once

#include <cstring>
#include "..\Core\Texture.hpp"
#include "IL\il.h"
#include "IL\ilu.h"

namespace SynEngine {
	class TexutreManager
	{
	public:
		TexutreManager();
		~TexutreManager();

		Texture* LoadTexture(const char* path);
	private:

	};
}