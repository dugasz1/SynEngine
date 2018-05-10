#include "..\..\include\SynEngine\Renderers\DefaultRenderer.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

SynEngine::DefaultRenderer::DefaultRenderer()
{
	ShaderProgram* sp = Engine::I->shaderProgramManager->LoadShaderProgram("..\\Test\\shaders", "default");

	SynEngine::DefaultRenderer::projectionMatrixId = sp->LocateUniform("projectionMatrix");

	viewMatrixId = sp->LocateUniform("viewMatrix");

	meshMatrixId = sp->LocateUniform("meshMatrix");

	textureSamplerId = sp->LocateUniform("texture_sampler");

	glUseProgram(sp->id);
}

SynEngine::DefaultRenderer::~DefaultRenderer()
{
}

void SynEngine::DefaultRenderer::Init()
{

}

void SynEngine::DefaultRenderer::Draw()
{
	const Window window = Engine::I->GetWindow();
	const Mat4 projectionM = window.GetProjectionMatrix();
	glUniformMatrix4fv(projectionMatrixId, 1, false, glm::value_ptr(projectionM));
	glUniformMatrix4fv(viewMatrixId, 1, false, glm::value_ptr(Engine::I->camera.GetViewMatrix()));

	for (std::vector<Object*>::iterator objIt = objects.begin(); objIt != objects.end(); objIt++)
	{		
		for (std::vector<Mesh*>::iterator it = (*objIt)->begin(); it != (*objIt)->end(); it++)
		{
			glUniformMatrix4fv(meshMatrixId, 1, false, glm::value_ptr((*it)->transformation));
			//printf("%u", (*it)->vao);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, (*it)->material.texture->id);

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
