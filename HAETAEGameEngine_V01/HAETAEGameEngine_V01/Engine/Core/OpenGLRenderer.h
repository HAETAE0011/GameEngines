#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "Renderer.h"

class OpenGLRenderer : public Renderer
{
public:
	OpenGLRenderer();
	~OpenGLRenderer();

	virtual SDL_Window* createWindow(std::string name_, int width_, int height_);

	virtual void OnDestroy();

private:
	void SetPreAttributes();
	void SetPostAttributes();
	int width;
	int height;
	SDL_Window* window;
	SDL_GLContext context;
};

#endif