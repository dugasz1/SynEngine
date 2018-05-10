#pragma once

#include "Material.hpp"
#include "glm/glm.hpp"
#include "../Util/CommonDefs.hpp"
#include <vector>
#include <string>

namespace SynEngine {
	struct Face
	{
		unsigned int numberOfIndices;
		unsigned int* indices;
	};

	class Mesh
	{
	public:
		std::string name;

		Vec3* vertices;
		///Number of vertices, not number of faces
		unsigned int verticesCount;
		Vec3* normals;
		unsigned int* indices;
		unsigned int indicesCount;
		Face* faces;
		unsigned int facesCount;
		std::vector<Vec2*> uvMaps;

		Material material;

		Mat4 transformation;

		//temp
		GLuint vao;

		Mesh();
		~Mesh();
	private:

	};
}


