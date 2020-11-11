#include "Engine/Core/CoreEngine.h"
#include "Game/Game2.h"

int main(int argc, char* argv[]) {
	CoreEngine::GetInstace()->SetGameInterface(new Game2, Renderer::RENDERER_TYPE::VULKAN);

	if (!CoreEngine::GetInstace()->OnCreate("GAME ENGINE 4", 1000, 500)) {
		//std::cout << "Engine failed to be created" << std::endl;
		Debug::FatalError("Engine failed to be created", "main.cpp", __LINE__);
		return 0;
	}

	CoreEngine::GetInstace()->Run();

	return 0;
}
