#include "../../include/SynEngine/Managers/ObjectManager.hpp"
#include "../../include/SynEngine/Engine.hpp"
#include "../../include/SynEngine/Util/CommonDefs.hpp"
#include <Windows.h>

SynEngine::ObjectManager::ObjectManager()
{
	printf("Object manager inited\n");
}

SynEngine::ObjectManager::~ObjectManager()
{
}

SynEngine::Object * SynEngine::ObjectManager::LoadObject(std::string path, unsigned int flags)
{
	//Converting char to wchar to resolve relative path, then back for assimp.
	std::wstring wStringPath(path.begin(), path.end());
	const wchar_t* wPath = wStringPath.c_str();
	wchar_t fullPath[MAX_PATH];
	GetFullPathNameW(wPath, MAX_PATH, fullPath, NULL);
	char* fullPathC = new char[MAX_PATH];
	std::wcstombs(fullPathC, fullPath, MAX_PATH);

	printf("Loading object at: %ls\n", fullPath);
	const aiScene* scene = aImporter.ReadFile(fullPathC, flags);
	if (scene == nullptr) {
		SynEngine::Engine::I->log->Error(aImporter.GetErrorString());
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

void SynEngine::ObjectManager::ProcessTransformationMatrix(aiMatrix4x4 * sourceMatrix, Mat4 * targetTransformation)
{
	float* src = (float*)sourceMatrix; //Row major
	float* dst = (float*)targetTransformation; //Column major
	for (size_t i = 0; i < 16; i++)
	{
		size_t rowJmp = i / 4;
		size_t srcI = rowJmp + (i * 4) % 16;
		dst[i] = src[srcI];
	}
}

void SynEngine::ObjectManager::ProcessHierarchy(const aiScene * scene, Object* obj, std::string& path)
{
	if (scene->mRootNode->mNumChildren != 0) {
		Mat4 identityMatrix; //Start with identity
		ProcessHierarchyRecursively(identityMatrix, obj->rootNode, obj, scene->mRootNode, scene, path);
	}
	else {
		printf("Warning %s obj has no children", path.c_str());
	}
}

void SynEngine::ObjectManager::ProcessHierarchyRecursively(Mat4 lastTranformationM, Node<Mesh*>* parentNode, Object* obj, aiNode * node, const aiScene* scene, std::string& path)
{
	Mat4 nodeMatrix;
	ProcessTransformationMatrix(&node->mTransformation, &nodeMatrix);
	Mat4 currMatrix = lastTranformationM * nodeMatrix;
	printf("--Number of meshed is in %s node: %u | Numof nodes: %u \n", node->mName.C_Str(), node->mNumMeshes, node->mNumChildren);

	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		Mesh* synMesh = LoadMesh(scene->mMeshes[node->mMeshes[i]], scene->mMaterials, path);
		synMesh->transformation = currMatrix;
		obj->AddMesh(synMesh);
		parentNode->AddElement(synMesh);
	}

	if (node->mNumChildren > 0) {
		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			Node<Mesh*>* childNode = new Node<Mesh*> ();
			parentNode->children.push_back(childNode);
			ProcessHierarchyRecursively(currMatrix, childNode, obj, node->mChildren[i], scene, path);
		}
	}

}

SynEngine::Mesh * SynEngine::ObjectManager::LoadMesh(aiMesh * mesh, aiMaterial** materials, std::string& filePathString)
{
	printf("UV channels: %u uv compinents: %u\n", mesh->GetNumUVChannels(), mesh->mNumUVComponents[0]);
	
	SynEngine::Engine::I->log->Info(mesh->mName.C_Str());
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

		Texture* texture = Engine::I->textureManager->LoadTexture(texturePath.string().c_str());
		texture->LoadTexture();

		Material material(texture);

		synMesh->material = material;

		printf("Texture name: %s\n", texturePath.c_str());
	}
	else {
		synMesh->material = Material();
	}

}
