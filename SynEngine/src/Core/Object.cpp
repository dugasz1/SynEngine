#include "../../include/SynEngine/Core/Object.hpp"

SynEngine::Object::Object()
{
}

SynEngine::Object::~Object()
{
}

void SynEngine::Object::AddMesh(SynEngine::Mesh * mesh)
{
	meshes.push_back(mesh);
}

std::vector<SynEngine::Mesh*>::iterator SynEngine::Object::begin()
{
	return meshes.begin();
}

std::vector<SynEngine::Mesh*>::iterator SynEngine::Object::end()
{
	return meshes.end();
}
