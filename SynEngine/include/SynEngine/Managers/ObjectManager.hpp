#pragma once

#include <string>
#include "../Core/Object.hpp"
#include "../Core/Mesh.hpp"
#include "../Util/Log.hpp"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#define OBJECT_LOAD_DEFAULT aiProcess_Triangulate | aiProcess_JoinIdenticalVertices

namespace SynEngine {
	class ObjectManager
	{
	public:
		ObjectManager();
		~ObjectManager();

	
		SynEngine::Object* LoadObject(std::string path, unsigned int flags = OBJECT_LOAD_DEFAULT);
	private:
		Assimp::Importer aImporter;

		SynEngine::Mesh* LoadMesh(aiMesh* mesh, aiMaterial** materials, std::string& filePathString);

		void ProcessFaces(Mesh* synMesh, aiFace* face, unsigned int facesCount);
		void ProcessUVChannels(Mesh* synMesh, aiVector3D* textureCoords[AI_MAX_NUMBER_OF_TEXTURECOORDS], unsigned int tCoordCount);
		void ProcessMaterials(Mesh* synMesh, aiMesh* mesh, aiMaterial** materials, std::string& filePathString);
	};
}