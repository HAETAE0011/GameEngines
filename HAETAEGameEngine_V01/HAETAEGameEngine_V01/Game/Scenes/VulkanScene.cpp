#include "VulkanScene.h"

VulkanScene::VulkanScene()
{
}

VulkanScene::~VulkanScene()
{
}

bool VulkanScene::OnCreate()
{
	Debug::Info("Creating Start Scene", "StartScene.cpp", __LINE__);
	
	//CoreEngine::GetInstace()->GetRenderer()->createWindow("Triangle", CoreEngine::GetInstace()->GetWindowSize().x, CoreEngine::GetInstace()->GetWindowSize().y);

	return true;
}

void VulkanScene::Update(const float deltaTime_)
{
}

void VulkanScene::Render()
{
	
}

void VulkanScene::Draw()
{
}
