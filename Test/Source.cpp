#include "SynEngine\Engine.hpp"
#include "SynEngine\Util\Debug.hpp"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <thread>

int main() {
	SynEngine::Engine::I->Init();

	SynEngine::Debug debuger;

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	SynEngine::Object* o = SynEngine::Engine::I->objectManager->LoadObject("..\\Test\\models\\gun\\M1911_assembled.dae");

	SynEngine::Engine::I->renderManager->dr->AddObject(o);

	glm::vec3 r(0.0f, 0.0f, 0.0f);
	float i = 0.0f;
	std::cout << "Starting main loop..." << std::endl;
	while (true)
	{
		SynEngine::Engine::I->camera.Rotate(r);
		i += 0.1f;
		r.y = i;
		SynEngine::Engine::I->MainLoop();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}