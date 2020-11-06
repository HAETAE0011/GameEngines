#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include "Renderer.h"

class GameInterface{
public:
	GameInterface() {}
	virtual ~GameInterface() {}

	virtual bool OnCreate() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render() = 0;
	virtual void Draw() = 0;
	virtual void SetRenderer(Renderer::RENDERER_TYPE type_) = 0;
};

#endif