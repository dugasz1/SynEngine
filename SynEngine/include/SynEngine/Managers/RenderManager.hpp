#pragma once

#include <vector>
#include "..\Renderers\IRenderer.hpp"
#include "..\Renderers\DefaultRenderer.hpp"

namespace SynEngine {
	class RenderManager
	{
	public:
		RenderManager();
		~RenderManager();

		class DefaultRenderer* dr;

		void RenderAll();
		void AddRenderer(SynEngine::IRenderer* renderer);
	private:

		std::vector<IRenderer*> renderers;

	};
}