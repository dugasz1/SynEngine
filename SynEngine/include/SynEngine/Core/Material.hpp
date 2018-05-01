#pragma once

#include "Texture.hpp"

namespace SynEngine {
	class Material
	{
	public:
		Material();
		Material(Texture* texture);
		~Material();

		Texture* texture;
	private:

	};
}