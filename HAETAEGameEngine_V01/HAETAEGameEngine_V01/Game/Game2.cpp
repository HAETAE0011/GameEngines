#include "Game2.h"

Game2::Game2() : GameInterface() , currentSceneNum(0), currentScene(nullptr)
{
}

Game2::~Game2()
{
	delete currentScene;
	currentScene = nullptr;
}

bool Game2::OnCreate()
{
	if (CoreEngine::GetInstace()->GetCurrentScene() == 0) {
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate();
	}
	Debug::FatalError("Engine's scene is not initialized to 0", "Game2.cpp", __LINE__);
	return false;
}

void Game2::Update(const float deltaTime_)
{
	if (currentSceneNum != CoreEngine::GetInstace()->GetCurrentScene()) {
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void Game2::Render()
{
	if (type == Renderer::RENDERER_TYPE::OPENGL) {
		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		currentScene->Render();
		currentScene->Draw();
		SDL_GL_SwapWindow(CoreEngine::GetInstace()->GetWindow()->GetWindow());
	}
	else if (type == Renderer::RENDERER_TYPE::VULKAN) {
		//do vulkan thing
	}
}

void Game2::Draw()
{
	//now this is a part of Render();
	currentScene->Draw();
}

void Game2::SetRenderer(Renderer::RENDERER_TYPE type_)
{
	type = type_;
}

void Game2::BuildScene()
{
	delete currentScene;
	currentScene = nullptr;
	switch (CoreEngine::GetInstace()->GetCurrentScene())
	{
	case 1: 
		currentScene = new GameScene();
		break;
	default: // case 0:
		currentScene = new StartScene();
		break;
	}

	currentSceneNum = CoreEngine::GetInstace()->GetCurrentScene();
	if (!currentScene->OnCreate()) {
		CoreEngine::GetInstace()->Exit();
	}
}
