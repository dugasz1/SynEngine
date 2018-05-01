#include "..\..\include\SynEngine\Renderers\DefaultRenderer.hpp"

SynEngine::DefaultRenderer::DefaultRenderer()
{
	//Engine::shaderProgramManager->LoadShaderProgram("B:/", "default");
}

SynEngine::DefaultRenderer::~DefaultRenderer()
{
}

void SynEngine::DefaultRenderer::Draw()
{
	for (std::vector<Object*>::iterator objIt = objects.begin(); objIt != objects.end(); objIt++)
	{		
		for (std::vector<Mesh*>::iterator it = (*objIt)->begin(); it != (*objIt)->end(); it++)
		{
			//printf("%u", (*it)->vao);
			glBindVertexArray((*it)->vao);
			glDrawElements(GL_TRIANGLES, (*it)->indicesCount, GL_UNSIGNED_INT, 0);
		}
	}
}

bool SynEngine::DefaultRenderer::AddObject(Object * object)
{
	for (auto& it : (*object)) {
		//printf("asdasdad %u", it->vao);
		glGenVertexArrays(1, &it->vao);
		glBindVertexArray(it->vao);

		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, it->verticesCount * sizeof(it->vertices[0]), it->vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, it->verticesCount * sizeof(it->uvMaps[0]), it->uvMaps[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		/*glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, it->verticesCount * sizeof(it->normals[0]), it->normals, GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);*/

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, it->indicesCount * sizeof(it->indices[0]), it->indices, GL_STATIC_DRAW);



		glBindVertexArray(0);
	}

	objects.push_back(object);
	return false;
}
