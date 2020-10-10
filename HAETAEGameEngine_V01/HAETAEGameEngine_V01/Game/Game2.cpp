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
	currentScene->Render();

}

void Game2::Draw()
{
	currentScene->Draw();
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
