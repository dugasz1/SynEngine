#include "../../include/SynEngine/Managers/ObjectManager.hpp"
#include "../../include/SynEngine/Engine.hpp"

SynEngine::ObjectManager::ObjectManager()
{
	printf("Object manager inited\n");
}

SynEngine::ObjectManager::~ObjectManager()
{
}

SynEngine::Object * SynEngine::ObjectManager::LoadObject(std::string path, unsigned int flags)
{
	const aiScene* scene = aImporter.ReadFile(path, flags);
	if (scene == nullptr) {
		SynEngine::Engine::log->Error(aImporter.GetErrorString());
		return nullptr;
	}

	Object* obj = new Object();
	obj->file = path;

	printf("Number of meshes: %u\n", scene->mNumMeshes);
	printf("Number of materials: %u\n", scene->mNumMaterials);
	printf("Hierarchy count: %u\n", scene->mRootNode->mNumChildren);
	std::cout << scene->mRootNode->mTransformation.IsIdentity() << std::endl;
	
	ProcessHierarchy(scene, obj, path);

	return obj;
}

void SynEngine::ObjectManager::ProcessHierarchy(const aiScene * scene, Object* obj, std::string& path)
{
	if (scene->mRootNode->mNumChildren != 0) {
		ProcessHierarchyRecursively(obj->rootNode, obj, scene->mRootNode, scene, path);
	}
	else {
		printf("Warning %s obj has no children", path.c_str());
	}
}

void SynEngine::ObjectManager::ProcessHierarchyRecursively(Node<Mesh*>* parentNode, Object* obj, aiNode * node, const aiScene* scene, std::string& path)
{
	
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		Mesh* synMesh = LoadMesh(scene->mMeshes[node->mMeshes[i]], scene->mMaterials, path);
		obj->AddMesh(synMesh);
		parentNode->AddElement(synMesh);
	}

	if (node->mNumChildren > 0) {
		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			Node<Mesh*>* childNode = new Node<Mesh*> ();
			parentNode->children.push_back(childNode);
			ProcessHierarchyRecursively(childNode, obj, node->mChildren[i], scene, path);
		}
	}

}

SynEngine::Mesh * SynEngine::ObjectManager::LoadMesh(aiMesh * mesh, aiMaterial** materials, std::string& filePathString)
{
	printf("UV channels: %u uv compinents: %u\n", mesh->GetNumUVChannels(), mesh->mNumUVComponents[0]);
	
	SynEngine::Engine::log->Info(mesh->mName.C_Str());
	printf("Vertices count: %u\n", mesh->mNumVertices);

	SynEngine::Mesh* synMesh = new SynEngine::Mesh();
	synMesh->verticesCount = mesh->mNumVertices;

	synMesh->vertices = new SynEngine::Vec3[mesh->mNumVertices];
	std::memcpy(synMesh->vertices, mesh->mVertices, sizeof(SynEngine::Vec3)*mesh->mNumVertices);

	synMesh->normals = new SynEngine::Vec3[mesh->mNumVertices];
	std::memcpy(synMesh->normals, mesh->mNormals, sizeof(SynEngine::Vec3)*mesh->mNumVertices);

	ProcessFaces(synMesh, mesh->mFaces, mesh->mNumFaces);
	
	synMesh->uvMaps.reserve(mesh->GetNumUVChannels());
	ProcessUVChannels(synMesh, mesh->mTextureCoords, mesh->mNumVertices);

	ProcessMaterials(synMesh, mesh, materials, filePathString);


	printf("Mat index: %u\n", mesh->mMaterialIndex);
	printf("Faces: %u\n", mesh->mNumFaces);
	printf("Faces size: %u\n", mesh->mFaces[0].mNumIndices);
	printf("Indices test: %u\n", mesh->mFaces[0].mIndices[2]);

	return synMesh;
}

void SynEngine::ObjectManager::ProcessFaces(Mesh* synMesh, aiFace * faces, unsigned int facesCount)
{
	SynEngine::Face* synFaces = new SynEngine::Face[facesCount];

	unsigned int numberOfIndices = 0;
	for (int i = 0; i < facesCount; i++) {
		//Counting indices
		numberOfIndices += faces[i].mNumIndices;
	}
	printf("Number of indices: %u\n", numberOfIndices);
	synMesh->indicesCount = numberOfIndices;
	synMesh->indices = new unsigned int[numberOfIndices];

	unsigned int offset = 0;
	for (int i = 0; i < facesCount; i++) {
		std::memcpy(synMesh->indices + offset, faces[i].mIndices, sizeof(unsigned int) * faces[i].mNumIndices);
		synFaces[i].indices = synMesh->indices + offset;
		synFaces[i].numberOfIndices = faces[i].mNumIndices;
		offset += faces[i].mNumIndices;
	}

	synMesh->faces = synFaces;
}

void SynEngine::ObjectManager::ProcessUVChannels(Mesh * synMesh, aiVector3D * textureCoords[AI_MAX_NUMBER_OF_TEXTURECOORDS], unsigned int tCoordCount)
{
	
	for (size_t i = 0; i < AI_MAX_NUMBER_OF_TEXTURECOORDS; i++)
	{
		aiVector3D* textureCoord = textureCoords[i];
		Vec2* uvMap = new Vec2[tCoordCount];
		if (textureCoord != nullptr) {
			for (size_t j = 0; j < tCoordCount; j++)
			{
				uvMap[j].x = textureCoord[j].x;
				uvMap[j].y = textureCoord[j].y;
			}
			synMesh->uvMaps.push_back(uvMap);
		}
		else {
			break;
		}
	}
}

void SynEngine::ObjectManager::ProcessMaterials(Mesh* synMesh, aiMesh* mesh, aiMaterial** materials, std::string& filePathString) {

	if (materials[mesh->mMaterialIndex]->GetTextureCount(aiTextureType::aiTextureType_DIFFUSE)>0) {
		//Texture file absolute path
		aiString texturePathString;
		materials[mesh->mMaterialIndex]->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0, &texturePathString);
		fs::path filePath(filePathString);
		fs::path texturePath = filePath.parent_path();
		fs::path textureRelativePath(texturePathString.C_Str());
		texturePath /= textureRelativePath;

		Texture* texture = Engine::textureManager->LoadTexture(texturePath.string().c_str());
		texture->LoadTexture();

		Material material(texture);

		synMesh->material = material;

		printf("Texture name: %s\n", texturePath.c_str());
	}
	else {
		synMesh->material = Material();
	}

}
