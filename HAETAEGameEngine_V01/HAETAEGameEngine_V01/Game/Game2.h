#ifndef GAME2_H
#define GAME2_H

#include "../Engine/Core/CoreEngine.h"
#include "Scenes/StartScene.h"
#include "Scenes/GameScene.h"
#include "Scenes/VulkanScene.h"

class Game2 : public GameInterface {
public:
	Game2();
	virtual ~Game2();

	virtual bool OnCreate() override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() override;
	virtual void Draw() override;
	//call for renderer
	virtual void SetRenderer(Renderer::RENDERER_TYPE type_);

private:
	int currentSceneNum;
	Scene* currentScene;
	Renderer::RENDERER_TYPE type;
	void BuildScene();
};

#endif // !GAME2_H