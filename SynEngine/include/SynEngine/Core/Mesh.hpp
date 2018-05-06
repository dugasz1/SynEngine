#pragma once

#include "Material.hpp"
#include "glm\glm.hpp"
#include <vector>
#include <string>

namespace SynEngine {
	struct Face
	{
		unsigned int numberOfIndices;
		unsigned int* indices;
	};

	typedef glm::vec3 Vec3;
	typedef glm::vec2 Vec2;

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

		//temp
		GLuint vao;

		Mesh();
		~Mesh();
	private:

	};
}


