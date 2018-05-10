#pragma once

#include <filesystem>
#include <vector>
#include "Mesh.hpp"
#include "Node.hpp"
#include "../Util/CommonDefs.hpp"
#include "glm/glm.hpp"

namespace SynEngine {
	class Object
	{
	public:
		Object();
		~Object();

		fs::path file;
		Node<Mesh*>* rootNode;

		void AddMesh(Mesh * mesh);
		std::vector<Mesh*>::iterator begin();
		std::vector<Mesh*>::iterator end();

		//Function will get it from root node
		void SetTransformation();
		void GetTransformation();
	private:
		
		std::vector<Mesh*> meshes;

	};
}


