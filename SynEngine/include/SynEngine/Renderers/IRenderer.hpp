#pragma once

#include "..\Core\Object.hpp"
#include "..\Util\CommonDefs.hpp"

namespace SynEngine {
	interface IRenderer {
	public:
		virtual void Draw() = 0;
		virtual bool AddObject(Object* object) = 0;
	private:

	};
}
