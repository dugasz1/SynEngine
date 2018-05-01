#include "SynEngine\Engine.hpp"
#include "SynEngine\Util\Debug.hpp"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <thread>

int main() {
	
	//SynEngine::Engine::Init();
	SynEngine::Engine engine;

	SynEngine::Debug debuger;

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	SynEngine::Object* o = SynEngine::Engine::objectManager->LoadObject("B:/Szakdoga/models/threecube/threecube.dae");

	SynEngine::Engine::renderManager->dr->AddObject(o);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, (*o->begin())->material.texture->id);
	
	SynEngine::ShaderProgram* sp = SynEngine::Engine::shaderProgramManager->LoadShaderProgram("B:/", "default");
	

	GLint vm = sp->LocateUniform("viewMatrix");

	GLint pm = sp->LocateUniform("projectionMatrix");

	GLint ts = sp->LocateUniform("texture_sampler");

	GLint mm = sp->LocateUniform("modelMatrix");

	glUseProgram(sp->id);
	glm::fvec3 pos(0.0f, 0.0f, -9.0f);

	float i = 0.0f;
	std::cout << "Starting main loop..." << std::endl;
	while (true)
	{
		glm::fmat4 viewmatrix(1.0f);
		//pos.z -= 0.1f;
		viewmatrix = glm::translate(viewmatrix, pos);
		viewmatrix = glm::rotate(viewmatrix, i, glm::vec3(0.0f, 1.0f, 0.0f));
		//viewmatrix = glm::rotate(viewmatrix, 20.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		i += 0.01f;
		glUniformMatrix4fv(vm, 1, false, glm::value_ptr(viewmatrix));

		glm::mat4 projectionMatrix = glm::perspective<float>(glm::radians(90.0f), (1280.0f/ 720.0f), 0.1f, 100.f);
		glUniformMatrix4fv(pm, 1, false, glm::value_ptr(projectionMatrix));

		glUniform1i(ts, 0);
		engine.MainLoop();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}