#ifndef GAME2_H
#define GAME2_H

#include "../Engine/Core/CoreEngine.h"
#include "Scenes/StartScene.h"
#include "Scenes/GameScene.h"

class Game2 : public GameInterface {
public:
	Game2();
	virtual ~Game2();

	virtual bool OnCreate() override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() override;
private:
	int currentSceneNum;
	Scene* currentScene;
	void BuildScene();
};

#endif // !GAME2_H