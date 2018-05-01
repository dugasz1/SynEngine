#include "..\..\include\SynEngine\Managers\RenderManager.hpp"

SynEngine::RenderManager::RenderManager()
{
	dr = new DefaultRenderer();
	AddRenderer(dr);
}

SynEngine::RenderManager::~RenderManager()
{
}

void SynEngine::RenderManager::RenderAll()
{
	for (std::vector<IRenderer*>::iterator it = renderers.begin();
		it != renderers.end(); it++) {
		(*it)->Draw();
	}
}

void SynEngine::RenderManager::AddRenderer(SynEngine::IRenderer * renderer)
{
	renderers.push_back(renderer);
}
