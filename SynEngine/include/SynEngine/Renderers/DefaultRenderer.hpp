#pragma once

#include <vector>
#include "IRenderer.hpp"
#include "..\Engine.hpp"

namespace SynEngine {
	class DefaultRenderer : public IRenderer
	{
	public:
		DefaultRenderer();
		~DefaultRenderer();

		void Draw();
		bool AddObject(Object* object);
	private:
		std::vector<Object*> objects;
	};

}