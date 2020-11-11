#ifndef VULKANSCENE_H
#define VULKANSCENE_H

#include "../../Engine/Core/CoreEngine.h"
#include <glm/gtx/string_cast.hpp>


class VulkanScene : public Scene
{
public:
	VulkanScene();
	virtual ~VulkanScene();

	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();
	virtual void Draw();

private:
	GameObject* shape;
};

#endif