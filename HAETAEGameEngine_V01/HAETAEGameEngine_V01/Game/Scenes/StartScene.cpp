#include "StartScene.h"

StartScene::StartScene() : Scene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	
	Debug::Info("Creating Start Scene", "StartScene.cpp", __LINE__);
	CoreEngine::GetInstace()->SetCurrentScene(2);
	return true;
}

void StartScene::Update(const float deltaTime_)
{
}

void StartScene::Render()
{
}

void StartScene::Draw()
{
}
