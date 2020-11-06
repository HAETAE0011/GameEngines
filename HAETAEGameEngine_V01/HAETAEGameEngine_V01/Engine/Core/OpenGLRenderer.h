#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "Renderer.h"

class OpenGLRenderer : public Renderer
{
public:
	virtual SDL_Window* createWindow(std::string name_, int width_, int height_);


private:

};

#endif